# Max-spanning-tree
Returns a minimal number of courses from a city to another city, given a graph of cities with roads connecting them (each one can have other capacity for transporting people).
### How to run
Firstly, compile a maxst.cpp file. Now having a .exe file, you can run it your terminal. Input can be entered directly into the terminal or via .txt file redirected as input for .exe file.
### Input
A first line of the input consists two numbers separated by a space. First number represents amount of cities, second number (let's call it n) - amount of roads. Next n lines describe every road. Each line has three numbers (also seperated by spaces): *a b m*  
a - road from city a  
b - road to city b  
m - maximum capacity for a one ride.  
End of input is signalized by two separated zeros.  
Example input included.
### About
This program uses the Prim's algorithm for finding a maximum spanning tree. Then with help of the Dijkstra's algorithm, searches for a path between two cities.
