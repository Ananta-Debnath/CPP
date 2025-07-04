#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"


class AdjacencyListGraph : public GraphADT
{
private:
    class Node
    {
    public:
        int value;
        ArrayList<int> adjList;

        Node(int val = 0)
        {
            value = val;
            // std::cout << value << " - Constructed" << std::endl;
        }

        Node(const Node& node)
        {
            value = node.value;
            for (int x : node.adjList) adjList.add(x);
            // std::cout << value << " - Copied" << std::endl;
        }

        Node& operator=(const Node& node)
        {
            if (this == &node) return *this;
            adjList.clear();
            value = node.value;
            for (int x : node.adjList) adjList.add(x);
            // std::cout << value << " - Assigned" << std::endl;
            return *this;
        }

        bool operator==(const Node& node)
        {
            return value == node.value;
        }
    };
    // TODO: Take necessary private members
    ArrayList<Node> nodes;

    // private methods
    void checkDist(int v, int* dist)
    {
        int idx = nodes.indexOf(v);
        for (int x : nodes.getAt(idx).adjList)
        {
            if(dist[nodes.indexOf(x)] > dist[idx] + 1)
            {
                dist[nodes.indexOf(x)] = dist[idx] + 1;
                checkDist(x, dist);
            }
        }
    }

public:
    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if (!nodes.contains(v)) nodes.add(v);
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);

        if (!CheckEdge(u, v))
        {
            nodes.getAt(nodes.indexOf(u)).adjList.add(v);
            nodes.getAt(nodes.indexOf(v)).adjList.add(u);
        }
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        return nodes.contains(u) && nodes.contains(v) && nodes.getAt(nodes.indexOf(u)).adjList.contains(v);
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        if (nodes.contains(v))
        {
            auto arr = nodes.getAt(nodes.indexOf(v)).adjList;
            for (int x : arr) nodes.getAt(nodes.indexOf(x)).adjList.remove(v);
            nodes.remove(v);
        }
        else std::cout << "Node doesn't exists" << std::endl;
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if (CheckEdge(u, v))
        {
            nodes.getAt(nodes.indexOf(u)).adjList.remove(v);
            nodes.getAt(nodes.indexOf(v)).adjList.remove(u);
        }
        else std::cout << "Edge doesn't exists" << std::endl;
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        return FindShortestPathLength(u, v) != -1;
    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        if (nodes.contains(u) && nodes.contains(v))
        {
            int l = nodes.size();
            int* dist = new int[l];
            int* par = new int[l];
            for (int i = 0; i < l; i++) dist[i] = l;
            dist[nodes.indexOf(v)] = 0;

            ArrayList<int> queue;
            queue.add(v);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                queue.removeAt(0);

                for (int x : nodes.getAt(nodes.indexOf(n)).adjList)
                {
                    if(dist[nodes.indexOf(x)] > dist[nodes.indexOf(n)] + 1)
                    {
                        dist[nodes.indexOf(x)] = dist[nodes.indexOf(n)] + 1;
                        par[nodes.indexOf(x)] = n;
                        queue.add(x);
                    }
                }
            }

            if (dist[nodes.indexOf(u)] < l)
            {
                std::cout << "Shortest path: ";
                for (int n = u; n != v; n = par[nodes.indexOf(n)]) std::cout << n << " ";
                std::cout << v << " " << std::endl;
            }
            else std::cout << "No path exists" << std::endl;

            delete[] dist;
            delete[] par;
        }
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if (nodes.contains(u) && nodes.contains(v))
        {
            int l = nodes.size();
            int* dist = new int[l];
            for (int i = 0; i < l; i++) dist[i] = l;
            dist[nodes.indexOf(u)] = 0;

            ArrayList<int> queue;
            queue.add(u);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                queue.removeAt(0);

                for (int x : nodes.getAt(nodes.indexOf(n)).adjList)
                {
                    if(dist[nodes.indexOf(x)] > dist[nodes.indexOf(n)] + 1)
                    {
                        dist[nodes.indexOf(x)] = dist[nodes.indexOf(n)] + 1;
                        queue.add(x);
                    }
                }
            }

            if (dist[nodes.indexOf(v)] < l) l = dist[nodes.indexOf(v)];

            else l = -1;

            delete[] dist;
            return l;
        }
        else return -1;
        
    }

    ArrayList<int> GetNeighbors(int u) const override
    {
        //TODO: Return the list of neighbors.
        ArrayList<int> neighbors;
        if (nodes.contains(u))
        {
            neighbors = nodes.getAt(nodes.indexOf(u)).adjList;
        }
        return neighbors;
    }

};

#endif // ADJACENCY_LIST_GRAPH_H
