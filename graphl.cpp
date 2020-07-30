// ---------------------------------Program 3(depth-first search)-----------------------------------------
// Jay Brar CSS343, Sec. C
// 2/9/2020
// 2/15/2020
//--------------------------------------------------------------------------------------------------------
// Purpose - This program contains a the implementation fo depth-first search
//--------------------------------------------------------------------------------------------------------
// Code should be able to read a data file consisting of many lines
// -------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "graphl.h"

// ------------------------------------Constructor--------------------------------------------
GraphL::GraphL()
{
    for (int i = 1; i < L_MAXNODES; i++)
    {
        gNodes[i].edgeHead = NULL;
        gNodes[i].data = NULL;
        gNodes[i].visited = false;
    }
}

// ------------------------------------Destructor---------------------------------------------
GraphL::~GraphL()
{
    makeEmpty();
}

// ------------------------------------buildGraph---------------------------------------------
// Description
// buildGraph: builds up graph node information and adjacency list of edges between each node
// reading from a data file
// preconditions: There must be a file to read from
// postconditions: Linked list with information of paths between nodes
// -------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& file)
{
    file >> size;
    
    // Ending the line so that we can read the next strings
    string description = "";
    getline(file, description);
    
    // Setting node data for each vertex
    for (int i = 1; i <= size; i++)
    {
        getline(file, description);
        NodeData* name = new NodeData(description);
        gNodes[i].data = name;
    }
    
    int start, end;
    
    // While loop that adds to the linked list
    while (file >> start)
    {
        file >> end;
        
        // Stop if we reach the end of the graph
        if (start == 0 && end == 0)
        {
            break;
        }
        
        // If trying to insert the first node at the give index (start)
        if (gNodes[start].edgeHead == NULL)
        {
            // Creating the first node and giving it the end value
            EdgeNode* first = new EdgeNode;
            first->adjGraphNode = end;
            
            // Adding to the linked list
            gNodes[start].edgeHead = first;
            (gNodes[start].edgeHead)->nextEdge = NULL;
        }
        // Adding to the list
        else
        {
            // Creating the new node and giving it the end value
            EdgeNode* next = new EdgeNode;
            next->adjGraphNode = end;
            
            // Adding to the linked list
            next->nextEdge = gNodes[start].edgeHead;
            gNodes[start].edgeHead = next;
        }
    }
}

// -----------------------------------displayGraph--------------------------------------------
// Description
// displayGraph: displays each node information and edge in the graph
// preconditions: Must be information in the linked list 
// postconditions: Outputs node and edge information
// -------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;
    
    if (size == 0)
    {
        return;
    }

    // Going through each node in the list
    for (int i = 1; i <= size; ++i)
    {
        // Outputting the node and number
        cout << "Node" << i << "        " << *(gNodes[i].data) << endl;
        cout << endl;
        
        // Storing the starting node for the current index
        EdgeNode* node = gNodes[i].edgeHead;
        
        // Output until reach end of adjacent nodes
        while (node != NULL)
        {
            // Printing path information for the current node
            cout << setw(7) << "edge" << setw(3) << i << setw(3) << node->adjGraphNode << endl;
            
            node = node->nextEdge; // Setting node to the next node for the while loop
        }
    }
    cout << endl;
}

// ----------------------------------depthFirstSearch-----------------------------------------
// Description
// depthFirstSearch: Makes a depth-first search and displays each node in depth-first order
// preconditions: Must be information of the node connection in the linked list
// postconditions: Print the DFS order for the current graph
// -------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:  ";
    
    // Calling the recursive helper for each node in the list
    for (int i = 1; i <= size; i++)
    {
        DFSHelper(i);
    }
    cout << endl;
    
    // Resetting to false in case DFS will be called again
    for (int i = 1; i <= size; i++)
    {
        gNodes[i].visited = false;
    }
}

// ----------------------------------------DFSHelper------------------------------------------
// Description
// DFSHelper: Recursive helper that prints the DFS order for the graph
// preconditions: index form depthFirstSearch
// postconditions: Print the DFS order for the current graph
// -------------------------------------------------------------------------------------------
void GraphL::DFSHelper(int index)
{
    // Print value and set as visited if current index isn't visited
    if (!gNodes[index].visited)
    {
        cout << index << "  ";
        gNodes[index].visited = true;
    }
    
    // If index has edges
    if (gNodes[index].edgeHead != NULL)
    {
        EdgeNode* current = gNodes[index].edgeHead;
        
        // If edge is univisited do the recursive call
        if (!gNodes[current->adjGraphNode].visited)
        {
            DFSHelper(current->adjGraphNode);
        }
        
        // Keep going thorugh edges if there are some
        while (current->nextEdge != NULL)
        {
            current = current->nextEdge;
            
            // Call recursive helper for other univisited edges
            if (!gNodes[current->adjGraphNode].visited)
            {
                DFSHelper(current->adjGraphNode);
            }
        }
    }
}

// -------------------------------------makeEmpty---------------------------------------------
// Description
// makeEmpty: Dellaocates all the data from the current instance of the object
// preconditions: None
// postconditions: Memory dellocated in the current instance of the object
// -------------------------------------------------------------------------------------------
void GraphL::makeEmpty()
{
    // Going through each node in the list
    for (int i = 1; i <= size; i++)
    {
        // Continue loop if node is empty
        if (gNodes[i].edgeHead == NULL)
        {
            continue;
        }
        // Call recursive helper to delete adjacent nodes
        EmptyHelper(gNodes[i].edgeHead);
    }
    size = 0;
}

// -------------------------------------EmptyHelper-------------------------------------------
// Description
// EmptyHelper: Recursive helper that dellocates all the data in the linked list
// preconditions: EdgeNode pointer for the current node
// postconditions: Memory deallocated for the current node
// -------------------------------------------------------------------------------------------
void GraphL::EmptyHelper(EdgeNode* current)
{
    // Delete if current node has information
    if (current != NULL)
    {
        // Go to adjacent nodes
        EmptyHelper(current->nextEdge);
        delete current;
        current = NULL;
    }
}
