#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */

struct Edge
{
    vertex *v;
    int distance;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    std::string name;
    bool visited;
    int shortestDistance;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addVertex(std::string cityName);
    void addEdge(std::string city1, std::string city2, int distance);
    void displayEdges();
    void setAllVerticesUnvisited();
    int shortestDistance(std::string name1, std::string name2);

  private:
    std::vector<vertex> vertices; //stores vertices

    vertex *findVertex(std::string name);

};

#endif // GRAPH_HPP
