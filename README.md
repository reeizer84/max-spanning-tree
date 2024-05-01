# Max-spanning-tree
About
Returns a minimal number of courses from a city to another city, given a graph of cities with roads connecting them (each path can have other capacity for people transported during a single ride).
### How to run
Firstly, compile the maxst.cpp file. An input can be entered directly into the terminal after running .exe file or by redirecting .txt file with everything needed.
### Input
A first line of the input consists two numbers separated by a space. The first number represents an amount of cities, a second number (let's call it n) - an amount of roads. Next n lines describe every road. Each line contains three numbers (also seperated by spaces): *a b m*  
a - a road from city a  
b - a road to city b 
m - maximum capacity for a one ride.  
The end of an input is signalized by two separated zeros.  
The example input included (input.txt).
<br/>
![graph](https://github.com/reeizer84/max-spanning-tree/assets/166179773/c7c03a81-4e37-4a32-877d-f19833ccf8f9)

### About
This program uses the Prim's algorithm for finding a maximum spanning tree. Then with help of the Dijkstra's algorithm, searches for a path between two cities.
