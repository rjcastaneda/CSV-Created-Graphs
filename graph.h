/*
 * RJCastaneda
 * File Name: graph.h
 *
 * Programmer Notes:
 * header file that contains the prototyped graph class.
 *
 */

#ifndef CS310_LAB_3_1_GRAPH_H
#define CS310_LAB_3_1_GRAPH_H

using namespace std;

#include <sstream>
#include <fstream>
#include <vector>

class graph
{
private:

    int totalEdges;
    int totalVertices;

protected:
    struct node
    {
        string title;
        int weight;
        node *next;
    };

    //We will make a list representation of a graph.
    //This is the "graph" itself.
    vector<node*> listGraph;

public:

    //Member Functions
    graph();
    bool addEdge(string source, string dest, int cost);
    bool removeEdges(string source, string destination);
    bool addVertex(string name);
    bool removeVertex(string name);
    bool contains(string name);
    bool contains(string source, string dest);
    int getVertices();
    int getEdges();
    vector<string> getMostWeight();
    vector<string> getNoOutboundEdge();
    vector<string> getNoInboundEdge();
    vector<string> getSelfEdges();
};

#endif //CS310_LAB_3_1_GRAPH_H
