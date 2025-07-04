#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"


class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    ArrayList<int> nodes;
    int** ajMat;
    int length;
    int capacity;

    void resizeMatrix()
    {
        //TODO: you need to resize your matrix when you will less data or more data
        int new_capacity = capacity;

        if (length >= capacity - 1) new_capacity = capacity * 2;

        else if (length * 4 < capacity && capacity > 3) new_capacity = capacity / 2;

        if (new_capacity != capacity)
        {
            int** newMatrix = new int*[new_capacity];

            for (int i = 0; i < new_capacity; i++) newMatrix[i] = new int[new_capacity]();

            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < length; j++) newMatrix[i][j] = ajMat[i][j];
            }

            for (int i = 0; i < capacity; i++) delete[] ajMat[i];
            delete[] ajMat;

            capacity = new_capacity;
            ajMat = newMatrix;
        }
    }

public:
    // Constructor
    AdjacencyMatrixGraph(int capacity = 2)
    {
        if (capacity < 1) throw std::runtime_error("Invalid Capacity");

        this->capacity = capacity;
        length = 0;
        ajMat = new int*[capacity];
        for (int i = 0; i < capacity; i++) ajMat[i] = new int[capacity]();
    }

    ~AdjacencyMatrixGraph()
    {
        for (int i = 0; i < capacity; i++) delete[] ajMat[i];
        delete[] ajMat;
    }

    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the ajMat if your current ajMat is almost going to be full.
        if (nodes.indexOf(v) == -1)
        {
            nodes.add(v);
            length++; 
            resizeMatrix();
        }
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);

        ajMat[nodes.indexOf(u)][nodes.indexOf(v)] = 1;
        ajMat[nodes.indexOf(v)][nodes.indexOf(u)] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        return nodes.indexOf(u) != -1 && nodes.indexOf(v) != -1 && ajMat[nodes.indexOf(u)][nodes.indexOf(v)] == 1;
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        int idx = nodes.indexOf(v);
        if (idx != -1)
        {
            nodes.remove(v);

            delete[] ajMat[idx];
            length--;
            for (int i = idx; i < length; i++) ajMat[i] = ajMat[i+1];
            ajMat[length] = new int[capacity];

            for (int i = 0; i < length; i++)
            {
                for (int j = idx; j < length; j++) ajMat[i][j] = ajMat[i][j+1];
            }
            resizeMatrix();
        }
        else std::cout << "Node doesn't exists" << std::endl;
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if (CheckEdge(u, v))
        {
            ajMat[nodes.indexOf(u)][nodes.indexOf(v)] = 0;
            ajMat[nodes.indexOf(v)][nodes.indexOf(u)] = 0;
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
        if (nodes.indexOf(u) != -1 && nodes.indexOf(v) != -1)
        {
            int* dist = new int[length];
            int* par = new int[length];
            for (int i = 0; i < length; i++) dist[i] = length;
            dist[nodes.indexOf(v)] = 0;

            ArrayList<int> queue;
            queue.add(v);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                int idx = nodes.indexOf(n);
                queue.removeAt(0);

                for (int i = 0; i < length; i++)
                {
                    if(ajMat[idx][i] == 1 && dist[i] > dist[idx] + 1)
                    {
                        dist[i] = dist[idx] + 1;
                        par[i] = n;
                        queue.add(nodes.getAt(i));
                    }
                }
            }

            std::cout << "Shortest path: ";
            for (int n = u; n != v; n = par[nodes.indexOf(n)]) std::cout << n << " ";
            std::cout << v << " " << std::endl;

            delete[] dist;
            delete[] par;
        }
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if (nodes.indexOf(u) != -1 && nodes.indexOf(v) != -1)
        {
            int* dist = new int[length];
            for (int i = 0; i < length; i++) dist[i] = length;
            dist[nodes.indexOf(u)] = 0;

            ArrayList<int> queue;
            queue.add(u);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                int idx = nodes.indexOf(n);
                queue.removeAt(0);

                for (int i = 0; i < length; i++)
                {
                    if(ajMat[idx][i] == 1 && dist[i] > dist[idx] + 1)
                    {
                        dist[i] = dist[idx] + 1;
                        queue.add(nodes.getAt(i));
                    }
                }
            }

            int n = -1;
            if (dist[nodes.indexOf(v)] < length) n = dist[nodes.indexOf(v)];

            delete[] dist;
            return n;
        }
        else return -1;
    }
    ArrayList<int> GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        int idx = nodes.indexOf(u);
        ArrayList<int> neighbors;
        if (idx != -1)
        {
            for (int i = 0; i < length; i++)
            {
                if (ajMat[idx][i] == 1) neighbors.add(nodes.getAt(i));
            }
        }
        return neighbors;
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
