#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

//klasa na krawedzie (wierzcholek docelowy oraz waga)
class Edge{
    private:
    int vertice_from;
    int vertice_to;
    int weight;
    
    public:
    Edge(){
        vertice_from = 0;
        vertice_to = 0;
        weight = 0;
    }
    Edge (int vertice1, int vertice2, int weight_in){
        vertice_from = vertice1;
        vertice_to = vertice2;
        weight = weight_in;
    }

    ~Edge(){
        vertice_from = 0;
        vertice_to = 0;
        weight = 0;
    }

    int GetWeight(){ return weight;}
    int GetVertice1(){ return vertice_from;}
    int GetVertice2(){ return vertice_to;}

    friend ostream& operator << (ostream& os, const Edge& e){
        return os << e.vertice_from << " " << e.vertice_to << " " << e.weight << endl;
    }
};

//klasa na wierzcholek fromowy i jego krawedzie incydentne
class Vertice{
    public:
    int vertice;
    vector <Edge> edges;

    public:
    Vertice(){ vertice = -1;}
    ~Vertice(){ vertice = 0;}

    int GetVertice(){ return vertice;}
    void SetVertice (int vertice_in){ vertice = vertice_in;}

    friend void AddVertice (int vertice1, int vertice2, int weight_in, vector <Vertice> &vertices);
    friend void Print (vector <Vertice> vertices);
};

void AddVertice (int vertice1, int vertice2, int weight_in, vector <Vertice> &vertices_in){
    if (vertices_in [vertice1].GetVertice() == -1){
        vertices_in [vertice1].SetVertice (vertice1);
        vertices_in [vertice1].edges.push_back (Edge (vertice1, vertice2, weight_in));
    }
    else if (vertices_in [vertice1].GetVertice() == vertice1){
        vertices_in [vertice1].edges.push_back (Edge (vertice1, vertice2, weight_in));
    }

    if (vertices_in [vertice2].GetVertice() == -1){
        vertices_in [vertice2].SetVertice (vertice2);
        vertices_in [vertice2].edges.push_back (Edge (vertice2, vertice1, weight_in));
    }
    else if (vertices_in [vertice2].GetVertice() == vertice2){
        vertices_in [vertice2].edges.push_back (Edge (vertice2, vertice1, weight_in));
    }
}

void Print (vector <Vertice> vertices){
    for (int i = 1; i < vertices.size(); i++){
        cout << "Vertice: " << i <<endl;
        for (Edge e: vertices [i].edges){ cout << e;}
    }
}

void Print (vector <Edge> edges){
    for (Edge e: edges){ cout << e;}
}

bool CompareWeights (Edge e1, Edge e2){
    return (e1.GetWeight() > e2.GetWeight());
}

bool CompareVertices (Edge e1, Edge e2){
    return ((e1.GetVertice1() < e2.GetVertice1()) || (e1.GetVertice2() < e2.GetVertice2()));
}

vector <Edge> MaxST (vector <Vertice> vertices_in, int from_in, int cities){
    vector <Edge> list; //lista ze znalezionymi krawedziami MaxST
    vector <Edge> temp_list; //tymczasowa lista z krawedziami potrzebnymi w algorytmie Prima
    vector <int> used_vertices; //wierzcholki uzyte w drzewie
    int current = from_in; //obecnie badany wierzcholek w algorytmie prima (jego krawedzie)

    for (int c = 0; c < cities-1; c++){
        //dodanie wszystkich krawedzi obecnego wierzcholka do listy
        for (Edge e: vertices_in [current].edges){ temp_list.push_back (e);}
        used_vertices.push_back (current);

        Edge edge;
        bool IsFound = false;
        sort (temp_list.begin(), temp_list.end(), CompareWeights);
        //sprawdzenie czy krawedz jest incydentna do wierzcholka, ktory juz jest w 
        //(zaczynajac od tej o najwiekszej wadze) oraz ustawia nastepny wierzcholek do zbadania
        for (int z = 0; z < temp_list.size() && !IsFound; z++){
            edge = temp_list [z];

            for (int i = 0; i < used_vertices.size(); i++){
                if (edge.GetVertice2() == used_vertices [i]) break;

                if (i == used_vertices.size() - 1){
                    IsFound = true; 
                    current = edge.GetVertice2();
                    list.push_back (edge);
                    vector <Edge>::iterator it2;
                    it2 = temp_list.begin()+z;
                    temp_list.erase (it2);
                }
            }
        }
        /*Pomocnicze
        cout<<"c: "<<c<<endl;
        Print (temp_list);
        cout<<"current: "<<current<<endl<<endl;
        */
    }
    sort (list.begin(), list.end(), CompareVertices);
    return list;
}

vector <Edge> CoursePath (vector <Edge> &edges, int from, int to) {
    unordered_map <int, vector <pair <int, int>> > neighborsList;
    int maxVertex = 0;
    for (Edge e : edges) {
        int u = e.GetVertice1();
        int v = e.GetVertice2();
        int weight = e.GetWeight();
        neighborsList[u].push_back(make_pair(v, weight));
        maxVertex = max(maxVertex, max(u, v));
    }

    vector<int> length(maxVertex + 1, INT_MAX);
    vector<int> parent(maxVertex + 1, -1);
    length[from] = 0;

    priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>> > queue;
    queue.push (make_pair (0, from));

    while (!queue.empty()) {
        int u = queue.top().second;
        queue.pop();

        for (auto neighbor : neighborsList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (length[u] != INT_MAX && length[v] > length[u] + weight) {
                length[v] = length[u] + weight;
                parent[v] = u;
                queue.push (make_pair (length[v], v));
            }
        }
    }

    vector <Edge> path;
    int currentVertex = to;
    while (currentVertex != from) {
        int previousVertex = parent[currentVertex];
        path.push_back (Edge (previousVertex, currentVertex, length[currentVertex] - length[previousVertex]));
        currentVertex = previousVertex;
    }

    //reverse (path.begin(), path.end());
    return path;
}

int CoursesCount (vector <Edge> &list, int passengers){
    int smallest;
    smallest = list[0].GetWeight();
    for (int i = 1; i < list.size(); i++){
        if (list [i].GetWeight() < smallest) smallest = list [i].GetWeight();
    }

    int courses = 0;
    smallest--;
    while (passengers > 0){
        courses++;
        passengers -= smallest;
    }

    return courses;
}
int main(){
    int cities; //ilosc miast
    int paths; //ilosc drog

    cin >> cities;
    cin >> paths;
    
    vector <Vertice> vertices;
    vertices.resize (cities + 1); //elementy beda przechowywane zaczynajac od 1

    int vertice1, vertice2, weight_in;
    for (int i = 0; i < paths; i++){
        cin >> vertice1;
        cin >> vertice2;
        cin >> weight_in;
        AddVertice (vertice1, vertice2, weight_in, vertices);
    }

    int next;
    cin >> next;
    vector <Edge> maxList = MaxST (vertices, 1, cities);
    do{
        vector <Edge> path;
        int from = next;
        int to;
        int passengers;

        cin >> to;
        cin >> passengers;

        path = CoursePath (maxList, from, to);
        cout << CoursesCount (path, passengers) << endl;
        cin >> next;
    }
    while (next);
    return 0;
}