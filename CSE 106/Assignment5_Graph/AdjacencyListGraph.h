#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"


class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members

public:
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.

    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v

    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v

    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.

    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge

    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false

    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.

    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.

    }

    YourListType GetNeighbors(int u) const override
    {
        //TODO: Return the list of neighbors.

    }

};

#endif // ADJACENCY_LIST_GRAPH_H
