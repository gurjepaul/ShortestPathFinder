// ----------------------------Program 3(Dijkstra's shortest path algorithm)------------------------------
// Jay Brar CSS343, Sec. C
// 2/9/2020
// 2/15/2020
//--------------------------------------------------------------------------------------------------------
// Purpose - This program contains a the implementation fo Dijkstra's shortest path algorithm
//--------------------------------------------------------------------------------------------------------
// Code should be able to read a data file consisting of many lines
// -------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "graphm.h"

// ------------------------------------Constructor--------------------------------------------
GraphM::GraphM()
{
    size = 0;
    for (int row = 1; row < H_MAXNODES; row++)
    {
        for (int column = 1; column < H_MAXNODES; column++)
        {
            C[row][column] = INT_MAX;
            T[row][column].visited = false;
            T[row][column].dist = INT_MAX;
            T[row][column].path = 0;
        }
    }
}

// ------------------------------------buildGraph---------------------------------------------
// Description
// buildGraph: builds up graph node information and adjacency matrix of edges between each
// node reading from a data file.
// preconditions: There must be a file to read from
// postconditions: C[][] adjacency matrix filled out with weights between nodes
// -------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& file)
{
    file >> size; // Reading the number of nodes
    
    if (size <= 0)
    {
        return;
    }
    
    ClearGraph();
    
    // Ending the line so that we can read the next strings
    string endLine = "";
    getline(file, endLine);

    // For loop that sets all the location names
    for (int i = 1; i <= size; i++)
    {
        data[i].setData(file);
    }
    
    int start, end, distance;
    
    // While loop that creates the adjacency matrix
    while (file >> start)
    {
        file >> end >> distance;

        // Stopping when the node is 0 to designate EOF
        if (start == 0)
        {
            // This is where it is messing up
            break;
        }
        
        C[start][end] = distance;
    }
}

// ------------------------------------insertEdge---------------------------------------------
// Description
// insertEdge: insert an edge into graph between two given nodes
// preconditions: Takes in a start and end node. C[][] must be filled
// postconditions: Adds the edge in the C[][] adjacency matrix
// -------------------------------------------------------------------------------------------
bool GraphM::insertEdge(int start, int end, int distance)
{
    // Don't insert if the start and end aren't in the appropriate range
    if ((start < 1 || start > size) || (end < 1 || end > size))
    {
        return false;
    }
    // Don't insert a negative distance
    if (distance < 0)
    {
        return false;
    }
    // Don't insert for special cases with start/end being the same and having distance 0
    if ((start == end && distance != 0) || (start != end && distance == 0))
    {
        return false;
    }
    
    // Checking if the graph is undirected to start
    if ((C[start][end] == C[end][start]) && C[start][end] < INT_MAX)
    {
        // Change the endpoint to the distance if it is undirected
        C[end][start] = distance;
    }
    
    // Inserting the new edge and updating the shortest paths
    C[start][end] = distance;
    ClearGraph();
    findShortestPath();
    
    return true;
}

// ------------------------------------removeEdge---------------------------------------------
// Description
// removeEdge: remove an edge between two given nodes
// preconditions: Takes in a start and end node. C[][] must be filled
// postconditions: Removes the edge in the C[][] adjacency matrix
// -------------------------------------------------------------------------------------------
bool GraphM::removeEdge(int start, int end)
{
    // Don't remove if start and end are outside the appropriate range
    if ((start < 1 || start > size) || (end < 1 || end > size))
    {
        return false;
    }
    
    // Removing the edge and updating the shortest paths
    C[start][end] = INT_MAX;
    C[end][start] = INT_MAX;
    
    ClearGraph();
    findShortestPath();
    
    return true;
}

// ---------------------------------findShortestPath------------------------------------------
// Description
// findShortestPath: finds the shortest path between every node to every other node in the
// graph, i.e., TableType T is updated with shortest path information
// preconditions: C[][] adjacency needs to be filled out
// postconditions: T[][] is filled with information regarding shortest paths between every
// node to every other node
// -------------------------------------------------------------------------------------------
void GraphM::findShortestPath()
{
    for (int source = 1; source <= size; source++)
    {
        // Setting the self edge to distance 0
        T[source][source].dist = 0;
        
        // finds the shortest distance from source to all other nodes
        for (int i = 1; i <= size; i++)
        {
            //find v not visited, shortest distance at this point
            int minimum = INT_MAX;
            int v = 0;
            
            for (int j = 1; j <= size; j++)
            {
                // Storing the minimum value and setting v
                if (!T[source][j].visited && (C[source][j] < minimum || T[source][j].dist < minimum))
                {
                    // If the dist in TableType T is shorter than the weight in the adjacency matrix
                    if (T[source][j].dist < C[source][j])
                    {
                        minimum = T[source][j].dist;
                    }
                    // Store the weight from the adjacency matrix
                    else
                    {
                        minimum = C[source][j];
                    }
                    v = j;
                }
            }
            
            // If there is v
            if (v > 0)
            {
                // Set the node as visited so we don't search it again later
                T[source][v].visited = true;
                
                // For each w adjacent to v
                for (int w = 1; w <= size; w++)
                {
                    // Potential for distance to be shorter if it isn't visited and the weight is not MAX
                    if (!T[source][w].visited && C[v][w] != INT_MAX)
                    {
                        int temp = T[source][w].dist;
                        
                        // Updating T to hold the lesser path
                        T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);
                        
                        // If temp is changed than update the path
                        if (temp != T[source][w].dist)
                        {
                            T[source][w].path = v;
                        }
                    }
                }
            }
        }
    }
    
    // Nested for loop that sets each vertex to not visited
    for (int row = 1; row < H_MAXNODES; row++)
    {
        for (int column = 1; column < H_MAXNODES; column++)
        {
            T[row][column].visited = false;
        }
    }
}

// ------------------------------------displayAll---------------------------------------------
// Description
// displayAll: uses couts to demonstrate that the algorithm works properly
// preconditions: Takes in a start and end. T[][] needs to be filled out
// postconditions: Outputs the shoertest distance with path info between all the nodes
// to every other node
// -------------------------------------------------------------------------------------------
void GraphM::displayAll() const
{
    // Outputting the header
    cout << "Description" << setw(18) << "From node" << setw(10) << "To node" << setw(13) << "Dijkstra's" << setw(9) << "Path" << endl;
    
    // Starting node
    for (int i = 1; i <= size; i++)
    {
        // Outputting node data
        cout << data[i] << endl;
        cout << endl;
        
        // End node
        for (int j = 1; j <= size; j++)
        {
            // Don't output info for self edge
            if (T[i][j].dist != 0)
            {
                // Starting and end node
                cout << setw(25) << i << setw(10) << j;
                
                // If there is no path then output a line
                if (T[i][j].dist == INT_MAX)
                {
                    cout << setw(10) << "----" << endl;
                }
                // Outputting Dijkstra and path
                else
                {
                    cout << setw(10) << T[i][j].dist << setw(13);
                    PrintPath(i, j); // Outputs the path
                    cout << endl;
                }
            }
        }
        cout << endl;
    }
}

// -------------------------------------display-----------------------------------------------
// Description
// display: uses couts to display the shortest distance with path info between the fromNode
// to toNode
// preconditions: Takes in a start and end. T[][] needs to be filled out
// postconditions: Outputs the shoertest distance with path info between the two nodes
// -------------------------------------------------------------------------------------------
void GraphM::display(int start, int end) const
{
    // Invalid arguments
    if ((start < 1 || start > size) || (end < 1 || end > size))
    {
        cout << setw(5) << start << setw(10) << end << setw(10) << "----" << endl;
        return;
    }
    
    // Outputting the start and end values
    cout << setw(5) << start << setw(10) << end;
    
    // If there is a path between
    if (T[start][end].dist != INT_MAX)
    {
        cout << setw(10) << T[start][end].dist<< setw(13);
        PrintPath(start, end); // Outputs the path
        cout << endl;
        PrintPathNames(start, end); // Outputs the path names
        cout << endl;
    }
    // If there is no path between the two
    else
    {
        cout << setw(10) << "----" << endl;
    }
}

// -------------------------------------PrintPath---------------------------------------------
// Description
// PrintPath: Recursive method that searches through the previous paths to find and print the
// shortest one
// preconditions: Takes in a start and end. T[][] needs to be filled out
// postconditions: Output of the nodes in order of shortest path
// -------------------------------------------------------------------------------------------
void GraphM::PrintPath(int start, int end) const
{
    // Keep searching if we aren't at the target node
    if (start != end && T[start][end].path > 0)
    {
        PrintPath(start, T[start][end].path);
    }
    // Outputs the path
    cout << end << " ";
}

// -----------------------------------PrintPathNames------------------------------------------
// Description
// PrintPathNames: Recursive method that searches through the previous paths to find and print
// the names of the paths in order of shortest path
// preconditions: Takes in a start and end. T[][] needs to be filled out
// postconditions: Output of the nodes in order of shortest path
// -------------------------------------------------------------------------------------------
void GraphM::PrintPathNames(int start, int end) const
{
    // Keep searching if we aren't at the target node
    if (start != end && T[start][end].path > 0)
    {
        PrintPathNames(start, T[start][end].path);
    }
    // Outputs the node name
    cout << " " << data[end] << endl;
}

// -------------------------------------ClearGraph--------------------------------------------
// Description
// ClearGraph: Sets all the information in T[][] to the default
// preconditions: Takes in a start and end. T[][] needs to be filled out
// postconditions: Output of the nodes in order of shortest path
// -------------------------------------------------------------------------------------------
void GraphM::ClearGraph()
{
    for (int row = 1; row < H_MAXNODES; row++)
    {
        for (int column = 1; column < H_MAXNODES; column++)
        {
            T[row][column].visited = false;
            T[row][column].dist = INT_MAX;
            T[row][column].path = 0;
        }
    }
}
