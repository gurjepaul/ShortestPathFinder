// ---------------------------------Program 3(depth-first search)-----------------------------------------
// Jay Brar CSS343, Sec. C
// 2/9/2020
// 2/15/2020
//--------------------------------------------------------------------------------------------------------
// Purpose - This program contains a the implementation fo depth-first search
//--------------------------------------------------------------------------------------------------------
// Code should be able to read a data file consisting of many lines
// -------------------------------------------------------------------------------------------------------

#ifndef graphl_h
#define graphl_h
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "nodedata.h"
using namespace std;

int const L_MAXNODES = 101;

class GraphL
{
public:
    GraphL();
    ~GraphL();
    
    void buildGraph(ifstream& file);
    void displayGraph();
    void depthFirstSearch();
    void makeEmpty();
    
private:
    struct EdgeNode;        // forward reference for the compiler
    struct GraphNode
    {                       // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };
    
    struct EdgeNode
    {
        int adjGraphNode;   // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };
    int size;
    GraphNode gNodes[L_MAXNODES];
    void EmptyHelper(EdgeNode* current);
    void DFSHelper(int index);
};

#endif /* graphl_h */
