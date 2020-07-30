////
////  driver.cpp
////  Program3
////
////  Created by Gurjepaul Brar on 2/9/20.
////  Copyright © 2020 Gurjepaul Brar. All rights reserved.
////
//
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include "graphl.h"
//#include "graphm.h"
//using namespace std;
//
//int main()
//{
//    ifstream inputFile1("data1.txt");
//
//    if (!inputFile1)
//    {
//        cerr << "ERROR: Invalid input file" << endl;
//    }
//    else
//    {
//        GraphM test1;
//
//        // Testing build and Djikstras
//        test1.buildGraph(inputFile1);
//        test1.findShortestPath();
//
//        // Outputting valid and invalid calls
//        test1.displayAll();
//        test1.display(1, 3);
//        test1.display(4, 3);
//        test1.display(0, 4);
//
//        // Removing a valid edge
//        cout << "Passed: " << test1.removeEdge(2, 4) << endl;
//
//        // Removing with invalid arguments
//        cout << "Failed: " << test1.removeEdge(0, 4) << endl;
//        cout << "Failed: " << test1.removeEdge(1, 9) << endl;
//
//        test1.displayAll();
//
//        // Inserting a valid edge
//        cout <<  "Passed: " << test1.insertEdge(1, 5, 1) << endl;
//
//        // Inserting with invalid arguments
//        cout <<  "Failed: " << test1.insertEdge(0, 4, 30) << endl;
//        cout <<  "Failed: " << test1.insertEdge(1, 8, 30) << endl;
//        cout <<  "Failed: " << test1.insertEdge(1, 1, 30) << endl;
//
//        test1.displayAll();
//    }
//    
//    cout << endl;
//    cout << endl;
//    
//    ifstream inputFile2("data2.txt");
//    
//    if (!inputFile2)
//    {
//        cerr << "ERROR: Invalid input file" << endl;
//    }
//    else
//    {
//        // Testing build
//        GraphL test2;
//        test2.buildGraph(inputFile2);
//        
//        // Testing display graph
//        test2.displayGraph();
//        
//        // Testing DFS method
//        test2.depthFirstSearch(); // 1  2  3  6  9  5  4  7  8
//    }
//
//}
