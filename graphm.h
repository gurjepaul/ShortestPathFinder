// ----------------------------Program 3(Dijkstra's shortest path algorithm)------------------------------
// Jay Brar CSS343, Sec. C
// 2/9/2020
// 2/15/2020
//--------------------------------------------------------------------------------------------------------
// Purpose - This program contains a the implementation fo Dijkstra's shortest path algorithm
//--------------------------------------------------------------------------------------------------------
// Code should be able to read a data file consisting of many lines
// -------------------------------------------------------------------------------------------------------

#ifndef graphm_h
#define graphm_h
#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <iomanip>
#include "nodedata.h"
using namespace std;

int const H_MAXNODES = 101;

class GraphM
{
public:
    GraphM();
    void buildGraph(ifstream& file); // WORKS
    bool insertEdge(int start, int end, int distance);
    bool removeEdge(int start, int end);
    void findShortestPath();
    void displayAll() const;
    void display(int start, int end) const;
    
private:
    struct TableType
    {
       bool visited;          // whether node has been visited
       int dist;              // shortest distance from source known so far
       int path;              // previous node in path of min dist
    };
    
    NodeData data[H_MAXNODES];              // data for graph nodes
    int C[H_MAXNODES][H_MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[H_MAXNODES][H_MAXNODES];      // stores visited, distance, path
    
    void PrintPath(int start, int end) const;
    void PrintPathNames(int start, int end) const;
    void ClearGraph();
};

#endif /* graphm_h */
