/*
 * Roswell James Castaneda
 * File Name: main.cpp
 *
 * Programmer Notes:
 * The graph uses a vector list of nodes to keep track of outbound and inbound
 * data.
 *
 * Visual Representation:
 *
 *                          Edges
 *
 *                A : B,2 -> C,2 -> A,1
 *  Vertex        B : A,3 -> C,2
 *                C : B,3 -> A,2 -> C,0
 *
 *  So vertex A has an outbound edge to B with a cost of 2. Vertex A also has
 *  an outbound edge to C with a cost of 2. And Vertex A also has a self edge
 *  with a cost of 1. A has an inbound edge from B with a cost of 3.
 *  And A has an inbound edge from c with a cost of 2.
 *
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "graph.h"

using namespace std;

//Loads and stores data as a 2D list
vector<vector<string>> loadData()
{
    //2D array list
    vector<vector<string>> sdata;
    string word, wordTwo, line;
    fstream thefile;

    thefile.open ("vietnam.csv", ios::in);
    if (thefile.fail())
    {
        cout << "File failed to Open. ";
        cout << "Make sure file name is vietnam.csv" << endl;
        thefile.close();
        return sdata;
    }

    if (thefile.is_open())
    {
        int x = 0;
        //grabs all CSV data as a string.
        while(getline(thefile, line))
        {
            stringstream s(line);
            sdata.push_back(vector<string>());
            while (getline(s, word, ','))
            {
                sdata[x].push_back(word);
            }
            x++;
        }
    }

    thefile.close();
    return sdata;
}

graph createGraph(vector<vector<string>> gdata)
{
    graph viet;
    int weight;
    string temp;
    //Numerical Constants
    int EDGE = 3, VERTEX_ONLY = 1, SRC = 0, DEST = 1, COST = 2;

    int x = 0;
    while( x < gdata.size())
    {
        if(gdata[x].size() == EDGE)
        {
            if(!viet.contains(gdata[x][SRC]))
            {
                viet.addVertex(gdata[x][SRC]);
            }

            if(!viet.contains(gdata[x][DEST]))
            {
                viet.addVertex(gdata[x][DEST]);
            }

            temp = gdata[x][COST];
            weight = stoi(temp);
            viet.addEdge(gdata[x][SRC],gdata[x][DEST],weight);

        }
        else if (gdata[x].size() == VERTEX_ONLY)
        {
            viet.addVertex(gdata[x][SRC]);
        }
        else
        {
            x++;
            continue;
        }

        x++;
    }

    return viet;
}


void output(graph out)
{
    std::ofstream myFile;
    vector<string> dataOut;

    myFile.open ("output.txt", ofstream::out | ofstream::trunc);

    //Outputting number of vertices and edges.
    myFile << "The Graph has " << out.getVertices();
    myFile << " vertices, and " << out.getEdges();
    myFile << " edges." << endl << endl;

    //Outputting vertices with zero inbound edges
    myFile << "Vertices with zero inbound edges: " << endl << endl;
    int x  = 0;
    dataOut = out.getNoInboundEdge();
    while( x < dataOut.size())
    {
        myFile << dataOut[x] << endl;
        x++;
    }
    myFile << endl;

    //Outputting vertices with self edges.
    myFile << "Vertices with self edges: " << endl << endl;
    x  = 0;
    dataOut = out.getSelfEdges();
    while( x < dataOut.size())
    {
        myFile << dataOut[x] << endl;
        x++;
    }
    myFile << endl;

    //Outputting vertices with zero outbound edges.
    myFile << "Vertices with zero outbound edges: " << endl << endl;
    x  = 0;
    dataOut = out.getNoOutboundEdge();
    while( x < dataOut.size())
    {
        myFile << dataOut[x] << endl;
        x++;
    }
    myFile << endl;

    //Outputting edges with heaviest weight.
    dataOut = out.getMostWeight();
    int lastE = dataOut.size()-1;
    //The value of greatest weight is stored at the end of list.
    int greatestWeight = stoi(dataOut[lastE]);
    myFile << "The greatest cost to travel is " << greatestWeight;
    myFile << endl << "The edges with the greatest cost are: " << endl;
    myFile << endl;

    x=0;
    while(x < lastE)
    {
        myFile << dataOut[x] << ", ";
        x++;
        myFile << dataOut[x] << endl;
        x++;
    }

    myFile.close();
    return;
}

int main()
{
    vector<vector<string>> data = loadData();
    output(createGraph(data));
    return 0;
}