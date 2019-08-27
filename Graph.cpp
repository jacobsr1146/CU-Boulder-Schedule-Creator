#include <iostream>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addVertex(string cityName){
  vertex *nv = new vertex;
  nv->name = cityName;
  nv->visited = false;
  nv->shortestDistance = 10000;
  vertices.push_back(*nv);
}

void Graph::addEdge(string city1, string city2, int distance){
  Edge *ne = new Edge;
  ne->distance = distance;
  ne->v = findVertex(city2);
  findVertex(city1)->Edges.push_back(*ne);
}

void Graph::displayEdges(){
  for(int x=0; x!=vertices.size(); x++){
    cout << vertices[x].name << "-->";
    for(int y=0; y!=vertices[x].Edges.size(); y++){
      cout << vertices[x].Edges[y].v->name << " (" << vertices[x].Edges[y].distance << " miles)";
      if(y!=(vertices[x].Edges.size()-1)){
        cout << "***";
      }
    }
    cout << endl;
  }
}

void Graph::setAllVerticesUnvisited(){
  for(int x=0; x!=vertices.size(); x++){
    vertices[x].visited = false;
  }
}

vertex* Graph::findVertex(string name){
  for(int x=0; x!=vertices.size(); x++){
    if(vertices[x].name == name){
      return &vertices[x];
    }
  }
  return NULL;
}


class Compare
{
public:
    bool operator() (vertex* v1, vertex* v2)
    {
        return v1->shortestDistance>v2->shortestDistance;
    }
};

int Graph::shortestDistance(string name1, string name2){
    //Create a priority queue
    priority_queue<vertex*, vector<vertex*>, Compare> pq;

    //Set the initial distance and visited
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name==name1){
            vertices[i].shortestDistance=0;
            pq.push(&vertices[i]);
        }else{
            vertices[i].shortestDistance=100000;
        }
        vertices[i].visited=false;

    }

    //Till my queue is not empty
    while(pq.size() >0){
        //Get the first element (As this is a priority queue the top will be the next closed element, wait, why is that?)
        vertex* current= pq.top();
        //Mark it as visited or done as this is the next closest element!
        current->visited=true;
        //Remove from the queue
        pq.pop();
        //For all the edges
        for(int i=0;i<current->Edges.size();i++){
            //If they are not already solved
            if(current->Edges[i].v->visited==false){
                //If the new distance I found to the node is actually smaller than the old distance I had
                if(current->Edges[i].v->shortestDistance > current->shortestDistance+ current->Edges[i].distance){
                    //Update it
                    current->Edges[i].v->shortestDistance = current->shortestDistance+ current->Edges[i].distance;
                }
                //Enqueue the vertex
                pq.push(current->Edges[i].v);

            }
        }
    }
    //Lets print everything
    for(int i=0;i<vertices.size();i++){
      if(vertices[i].name == name2){
        return vertices[i].shortestDistance;
      }
    }
}
