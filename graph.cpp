/*
 * RJCastaneda
 * File Name: graph.cpp
 *
 * Programmer Notes:
 * Definitions of member functions in graph.h
 *
 */

using namespace std;

#include "graph.h"
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

//constructor
graph::graph()
{
    totalEdges = 0;
    totalVertices = 0;
}

bool graph::addEdge(string source, string dest, int cost)
{
    node* current = new node;
    current = listGraph[0];

    //Checks to see if vertices exist.
    if(!contains(source) || !contains(dest))
    {
        return 0;
    }

    //Linear search of source.
    int n = 0;
    while(current->title.compare(source) != 0)
    {
        current = listGraph[n++];
    }

    //Linear traversal to end of list
    n = 0;
    while(current->next != nullptr)
    {
        current = current->next;
    }

    //Create a new node and link it to list.
    node *newNode = new node;
    newNode->weight = cost;
    newNode->title = dest;
    newNode->next = nullptr;
    current->next = newNode;

    totalEdges++;
    return 1;
}

bool graph::removeEdges(string source, string destination)
{
    node* current = new node;
    node* previous = new node;

    //If there is no edge to remove, return false
    if(!contains(source, destination))
    {
        return 0;
    }

    //search for vertex
    for (int x = 0; x < listGraph.size(); x++)
    {
        current = listGraph[x];
        if(current->title.compare(source) == 0)
        {
            break;
        }
    }

    //search for the edge to delete
    while(current->title.compare(destination) != 0)
    {
        if(current->title.compare(destination) == 0)
        {
            previous->next = current->next;
            free(current);
            break;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    totalEdges--;
    return 1;
}

bool graph::addVertex(string name)
{
    //Checks to see if vertex already exists.
    if(contains(name))
    {
        return false;
    }

    //Create a new vertex and add it to end of list.
    node* newNode = new node;
    newNode->title = name;
    newNode->next = nullptr;
    listGraph.push_back(newNode);
    totalVertices++;
    return true;
}

bool graph::removeVertex(string name)
{
    node* current = new node;
    node* previous = new node;
    string currentName;
    int temp = 0;

    //Checks to see if vertex exists.
    if(!contains(name))
    {
        return false;
    }

    //Linear search to remove every reference of vertex
    for (int x = 0; x < listGraph.size(); x++)
    {
        current = listGraph[x];
        string currentTitle = current->title;

        //if no edge exists with the soon to be deleted vertex, continue.
        if(!contains(currentTitle,name))
        {
            continue;
        }
        //Remove that reference.
        removeEdges(currentTitle,name);
    }

    //Traversing to Vertex
    for (int x = 0; x < listGraph.size(); x++)
    {
        current = listGraph[x];
        if(current->title.compare(name) == 0)
        {
            temp = x;
            break;
        }
    }

    //Remove the edges within the vertex to be deleted.
    while(current->next != nullptr)
    {
        previous = current;
        current = current->next;
        currentName = current->title;
        removeEdges(name, currentName);
    }


    //Erase function in vector library only takes iterators.
    listGraph.erase(listGraph.begin()+temp);

    totalVertices--;
    return true;
}

//checks if graph contains a vertex of such name
bool graph::contains(string name)
{
    //linear search to see if vertex of such name exists already
    node* current = new node;
    for (int x = 0; x < listGraph.size(); x++)
    {
        current = listGraph[x];
        if(current->title == name)
        {
            return true;
        }
    }
    return false;
}

//checks if graph contains an edge with such src and dest.
bool graph::contains(string source, string dest)
{
    node* current = new node;
    //search for vertex.
    for (int x = 0; x < listGraph.size(); x++)
    {
        current = listGraph[x];
        if(current->title == source)
        {
            break;
        }
    }

    //search for edge.
    while(current->title!= dest)
    {
        if(current->title == dest)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }
    return false;
}

int graph::getVertices()
{
    return totalVertices;
}

int graph::getEdges()
{
    return totalEdges;
}

//returns a list of the highest weighted edges
vector<string> graph::getMostWeight()
{
    vector<string> temp;
    node* crntVert = new node;
    node* crntEdge = new node;
    int greatestWeight = 0, crntCost = 0;

    //Traverses graph to find largest weight first.
    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntEdge = crntVert->next;

        //If just a vertex, skip it.
        if (crntVert->next == nullptr)
        {
            continue;
        }

        while(crntEdge != nullptr)
        {
            crntCost = crntEdge->weight;

            if(crntCost > greatestWeight)
            {
                greatestWeight = crntCost;
            }

            crntEdge = crntEdge->next;
        }
    }

    //Traverses graph to find edges with greatest cost.
    //Puts it into list to return.
    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntEdge = crntVert->next;

        //If just a vertex, skip it.
        if (crntVert->next == nullptr)
        {
            continue;
        }

        while(crntEdge != nullptr)
        {
            crntCost = crntEdge->weight;

            if(crntCost == greatestWeight)
            {
                temp.push_back(crntVert->title);
                temp.push_back(crntEdge->title);
            }

            crntEdge = crntEdge->next;
        }
    }

    temp.push_back(to_string(greatestWeight));
    return temp;
}

//returns a list of vertices with no inbound edges.
vector<string> graph::getNoInboundEdge()
{
    vector<string> tempOne;
    vector<string> tempTwo;
    node* crntVert = new node;
    node* crntEdge = new node;
    bool found = false;
    string crntName;

    //Load all vertices in tempOne;
    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntName = crntVert->title;
        tempOne.push_back(crntName);
    }

    //List all outbound edges.
    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntEdge = crntVert->next;


        //Lists all the destination vertices in temp two.
        while(crntEdge != nullptr)
        {
            //TempTwo is a list of vertices with inbound edges.
            //This loop is to see if a vertex already is within the list of
            //inbound vertices.
            for(int y = 0; y < tempTwo.size(); y++)
            {
                if(crntEdge->title == tempTwo[y])
                {
                    crntEdge = crntEdge->next;
                    found = true;
                    break;
                }
                else
                {
                    found = false;
                }
            }

            if(!found)
            {
                tempTwo.push_back(crntEdge->title);
                crntEdge = crntEdge->next;
            }
        }
    }

    //Comparing TempOne and TempTwo to get no inbound vertexes.
    for (int x = 0; x < tempOne.size(); x++)
    {
        for(int y = 0; y < tempTwo.size(); y++)
        {
            if(tempOne[x] == tempTwo[y])
            {
                //erase the inbound vertex from tempOne.
                //Also erase from tempTwo because match found.
                //This means tempOne only has non-inbound vertexes.
                tempOne.erase(tempOne.begin()+x);
                tempTwo.erase(tempTwo.begin()+y);

                //Reset the loop for tempOne because its size changed.
                x=-1;
                break;
            }
        }

    }

    return tempOne;
}

//returns a list of vertices with no outbound edges.
vector<string> graph::getNoOutboundEdge()
{
    vector<string> temp;
    node* crntVert = new node;
    string crntName;

    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntName = crntVert->title;
        if (crntVert->next == nullptr)
        {
            temp.push_back(crntName);
        }
    }
    return temp;
}

//returns a list of vertices with edges to themselves.
vector<string> graph::getSelfEdges()
{
    node* crntVert = new node;
    node* crntEdge = new node;
    string crntETitle, crntName;
    vector<string> temp;;

    for(int x = 0; x < listGraph.size(); x++)
    {
        crntVert = listGraph[x];
        crntEdge = crntVert->next;
        crntName = crntVert->title;

        //If only a vertex, with no edges, skip it.
        if (crntVert->next == nullptr)
        {
            continue;
        }

        while(crntEdge != nullptr)
        {
            crntETitle = crntEdge->title;
            if(crntETitle == crntName)
            {
                temp.push_back(crntName);
                break;
            }
                crntEdge = crntEdge->next;

        }
    }

    return temp;
}

