#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GraphADT.h"
#include "AdjacencyListGraph.h"
// #include "AdjacencyMatrixGraph.h"

// Toggle between implementations
#define USE_ADJACENCY_LIST
//#define USE_ADJACENCY_MATRIX

int main()
{
#ifdef USE_ADJACENCY_LIST
    std::cout << "Using Adjacency List Implementation\n";
    GraphADT* graph = new AdjacencyListGraph();
#elif defined(USE_ADJACENCY_MATRIX)
    std::cout << "Using Adjacency Matrix Implementation\n";
    GraphADT* graph = new AdjacencyMatrixGraph();
#else
    std::cerr << "Please define a graph implementation macro.\n";
    return 1;
#endif
    
    std::ifstream infile("input.txt");
   
    freopen("output2.txt", "w", stdout);
    if (!infile.is_open())
    {
        std::cerr << "Failed to open input.txt\n";
        delete graph;
        return 1;
    }

    int u, v;
    while (infile >> u >> v)
    {
        graph->AddEdge(u, v);
    }
    std::cout << "Graph loaded from file.\n\n";

    // Test shortest paths and their lengths
    int testPairs[][2] = {{1, 10}, {3, 15}, {5, 14}, {2, 8}, {7, 12},{1,12},{2, 11},{6,13}};
    for (auto& pair : testPairs)
    {
        std::cout << "Shortest path from " << pair[0] << " to " << pair[1] << ":\n";
        graph->FindShortestPath(pair[0], pair[1]);
        std::cout << "Length: " << graph->FindShortestPathLength(pair[0], pair[1]) << "\n\n";
    }

    // Test CheckEdge and RemoveEdge
    std::cout << "Edge (5,6) exists? " << graph->CheckEdge(5, 6) << "\n";
    graph->RemoveEdge(5, 6);
    std::cout << "Edge (5,6) exists after removal? " << graph->CheckEdge(5, 6) << "\n\n";

    // Test CheckPath (connectivity)
    int pathTests[][2] = {{1, 15}, {10, 5}, {8, 14}, {1, 100}};
    for (auto& pair : pathTests)
    {
        std::cout << "Path exists from " << pair[0] << " to " << pair[1] << "? ";
        std::cout << (graph->CheckPath(pair[0], pair[1]) ? "Yes" : "No") << "\n";
    }
    std::cout << "\n";

    // Test RemoveNode
    std::cout << "Removing node 7...\n";
    graph->RemoveNode(7);
    std::cout << "Path exists from 1 to 7? " << (graph->CheckPath(1, 7) ? "Yes" : "No") << "\n";
    std::cout << "Edge (6,7) exists? " << graph->CheckEdge(6, 7) << "\n\n";

    // Add some edges/nodes dynamically
    std::cout << "Adding edge (7, 20)...\n";
    graph->AddEdge(7, 20);
    std::cout << "Path exists from 7 to 20? " << (graph->CheckPath(7, 20) ? "Yes" : "No") << "\n";

    // Shortest path after addition
    graph->FindShortestPath(7, 20);
    std::cout << "Length: " << graph->FindShortestPathLength(7, 20) << "\n";

    std::cout << "Neighbors of node 3: ";

   ArrayList neighbors = graph->GetNeighbors(3);


    for(int i=0;i<neighbors.getSize();i++){

        std::cout<< neighbors[i]<<" ";
    }   
   
    
    std::cout << "\n";

    std::cerr << "-------------" << std::endl;
    delete graph;
    return 0;
}

/*
Using Adjacency List Implementation
New: 0x19d7405bef0
New: 0x19d7405f3d0
New: 0x19d7405f410
New: 0x19d7405f430
New: 0x19d740674c0
New: 0x19d740674e0
New: 0x19d7405f410
Delete: 0x19d7405f3d0
Delete: 0x19d7405bef0
New: 0x19d74066960
New: 0x19d7405bef0
New: 0x19d7405f3d0
New: 0x19d7405f3f0
New: 0x19d74083640
New: 0x19d74083720
New: 0x19d74083760
New: 0x19d740835c0
New: 0x19d74083630
New: 0x19d74083650
Delete: 0x19d740674e0
Delete: 0x19d740674c0
Delete: 0x19d7405f430
Delete: 0x19d7405f410
New: 0x19d74083630
New: 0x19d74067a70
New: 0x19d74083660
New: 0x19d74083690
New: 0x19d74083610
New: 0x19d74083670
New: 0x19d74083750
New: 0x19d740836d0
New: 0x19d740836a0
New: 0x19d740836b0
New: 0x19d74083620
New: 0x19d740836c0
New: 0x19d74083730
New: 0x19d740835d0
New: 0x19d740836e0
New: 0x19d740835e0
New: 0x19d740835f0
New: 0x19d74083680
New: 0x19d74069900
New: 0x19d74083600
New: 0x19d740836f0
New: 0x19d74083740
Delete: 0x19d740835c0
Delete: 0x19d74083760
Delete: 0x19d74083720
Delete: 0x19d74083640
Delete: 0x19d7405f3f0
Delete: 0x19d7405f3d0
Delete: 0x19d74083650
Delete: 0x19d74069ba0
New: 0x19d74083600
New: 0x19d740678f0
New: 0x19d74083760
New: 0x19d740835c0
New: 0x19d74083700
New: 0x19d74083630
New: 0x19d74083640
New: 0x19d74083710
New: 0x19d74083600
New: 0x19d74083610
New: 0x19d74083720
New: 0x19d74083650
New: 0x19d74083690
New: 0x19d74083660
New: 0x19d74083670
New: 0x19d74083a10
New: 0x19d74083d70
New: 0x19d74083ae0
New: 0x19d74083a60
New: 0x19d74083c90
New: 0x19d74083bc0
New: 0x19d74083c80
New: 0x19d74083a50
New: 0x19d74083af0
New: 0x19d74083cc0
New: 0x19d74083ab0
New: 0x19d74083c70
New: 0x19d74083a00
New: 0x19d74083cd0
New: 0x19d74083bb0
New: 0x19d74083d80
New: 0x19d74083b60
New: 0x19d74083bf0
New: 0x19d74083ac0
New: 0x19d74069b40
New: 0x19d74069630
New: 0x19d74083b80
New: 0x19d74083ad0
New: 0x19d74083d30
New: 0x19d74083bd0
New: 0x19d74083ba0
New: 0x19d74083b20
Delete: 0x19d74083680
Delete: 0x19d740835f0
Delete: 0x19d740835e0
Delete: 0x19d740836e0
Delete: 0x19d740835d0
Delete: 0x19d74083730
Delete: 0x19d740836c0
Delete: 0x19d74083620
Delete: 0x19d740836b0
Delete: 0x19d740836a0
Delete: 0x19d740836d0
Delete: 0x19d74083750
Delete: 0x19d74083740
Delete: 0x19d740836f0
Delete: 0x19d74069510
Delete: 0x19d74069900
New: 0x19d74083b80
New: 0x19d74067a70
New: 0x19d74083ad0
New: 0x19d74067bf0
New: 0x19d74083d30
New: 0x19d74067bf0
New: 0x19d74083bd0
New: 0x19d74067a70
New: 0x19d74083ba0
New: 0x19d74067a70
New: 0x19d74083b20
New: 0x19d74067a70
New: 0x19d74083720
New: 0x19d74067a70
New: 0x19d74083650
New: 0x19d74067bf0
New: 0x19d74083690
New: 0x19d74067bf0
New: 0x19d74083660
New: 0x19d74067a70
New: 0x19d74083670
New: 0x19d74067bf0
New: 0x19d74083a10
New: 0x19d74067a70
New: 0x19d74083d70
New: 0x19d74067a70
New: 0x19d74069b40
New: 0x19d74069630
New: 0x19d740698d0
New: 0x19d74069840
New: 0x19d74069600
New: 0x19d74069a80
New: 0x19d740699c0
New: 0x19d74069570
New: 0x19d74069870
New: 0x19d74069b70
New: 0x19d740695d0
New: 0x19d74069690
New: 0x19d7405eda0
New: 0x19d740699c0
New: 0x19d74084110
New: 0x19d74084c50
New: 0x19d74083df0
New: 0x19d74083f30
New: 0x19d74084660
New: 0x19d74069ba0
New: 0x19d74084020
New: 0x19d74083b80
New: 0x19d74083b00
New: 0x19d74083b00
New: 0x19d74067bf0
New: 0x19d740699f0
-------------
Delete: 0x19d74083ac0
Delete: 0x19d74083bf0
Delete: 0x19d74083b60
Delete: 0x19d74083d80
Delete: 0x19d74083bb0
Delete: 0x19d74083cd0
Delete: 0x19d74083a00
Delete: 0x19d74083c70
Delete: 0x19d74083ab0
Delete: 0x19d74083cc0
Delete: 0x19d74083af0
Delete: 0x19d74083a50
Delete: 0x19d74083c80
Delete: 0x19d74083bc0
Delete: 0x19d74083c90
Delete: 0x19d74083a60
Delete: 0x19d74083ae0
Delete: 0x19d74083b80
Delete: 0x19d74084020
Delete: 0x19d74069ba0
*/
