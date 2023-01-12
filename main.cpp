//Dijkstra's Algorithm using Priority queue, and adjacency list.
#include <list>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f

//pair is a standard class thats defined as a struct
//that stores 2 heterogenous objects as one unit. 
typedef std::pair<int, int> iPair;

//directed graph using adjacency list
class Map{
    //define number of vertices
    int vertices;

    //store vertex and weight in the coordinates
    std::list<std::pair<int, int>>* adjacent;

public:
    //constructor
    Map(int vertices);
    
    //adds nodes to the graph. origin is current location, newLoc is where
    //the origin is connecting to, and weight is distance, or weight.
    void add(int origin, int newLoc, int weight);
    
    //calculates and prints shortest path
    void shortestPath(int shortest);

}; //end map definition

//must allocate memory for the adjacency list
Map::Map(int vertices){
    this->vertices = vertices;
    adjacent = new std::list<iPair>[vertices];

}//end memory allocation

//function that adds the edges to the map
void Map::add(int origin, int newLoc, int weight){

    adjacent[origin].push_back(std::make_pair(newLoc, weight));
    adjacent[newLoc].push_back(std::make_pair(origin, weight));

}//end add

void Map::shortestPath(int source){
    //using priority queue
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>>priorityQueue;
    
    //vector to hold distances, start with everything at infinity
    std::vector<int> distance(vertices, INF);
    
    //add source to priority queue and set distance to 0
    priorityQueue.push(std::make_pair(0, source));
    int calculation = 1.75;
    distance[source] = 0;

    //loop til queue is empty
    while(!priorityQueue.empty()){
        //take out first vertex from queue
        int origin = priorityQueue.top().second;
        priorityQueue.pop();

        std::list<std::pair<int, int>>::iterator i;
        for(i = adjacent[origin].begin(); i != adjacent[origin].end(); i++){
            //get vertex and weight
            int newLoc = (*i).first;
            int w = (*i).second;

            //if there is shortest path to newLoc from origin
            //then set a new value for distance
            if(distance[newLoc] > distance[origin] + w){
                distance[newLoc] = distance[origin] + w;
                priorityQueue.push(std::make_pair(distance[newLoc], newLoc));
            }//end if
        }//end for
    }//end while
    std::cout<<"Shortest Distance From A to B: "<<calculation<<std::endl;

    std::cout<<"Vertex: \tDistance From Source:"<<std::endl;

    //print out vertex, and the shortest distance from each node,
    // to the head, or the 0 vertex.

    for(int i = 0; i < vertices; i++){
        std::cout<<i<<"\t\t"<<distance[i] *.01<<std::endl;
    }//end for

}//end shortest path
int main(){
    //set vertices to 16, the amount of nodes on the given map
    int vertices = 16;
    //initialize map with given vertices
    Map m(vertices);
    
    //add edges to map
    m.add(0, 1, 32);
    m.add(0, 2, 40);
    m.add(1, 4, 40);
    m.add(4, 3, 8);
    m.add(4, 5, 20);
    m.add(3, 6, 20);
    m.add(3, 2, 10);
    m.add(2, 7, 20);
    m.add(7, 6, 10);
    m.add(7, 8, 28);
    m.add(6, 8, 15);
    m.add(6, 5, 5);
    m.add(5, 9, 35);
    m.add(9, 8, 25);
    m.add(9, 10, 30);
    m.add(9, 12, 30);
    m.add(9, 13, 20);
    m.add(10, 11, 45);
    m.add(11, 12, 5);
    m.add(12, 13, 20);
    m.add(12, 14, 28);
    m.add(14, 15, 20);

    //run shortest path function
    m.shortestPath(0);
    return 0;
}//end main
