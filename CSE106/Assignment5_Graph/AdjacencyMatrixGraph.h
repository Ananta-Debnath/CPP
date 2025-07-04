#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"


class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    int** matrix;
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

            for (int i = 0; i <= length; i++)
            {
                for (int j = 0; j <= length; j++) newMatrix[i][j] = matrix[i][j];
            }

            for (int i = 0; i < capacity; i++) delete[] matrix[i];
            delete[] matrix;

            capacity = new_capacity;
            matrix = newMatrix;
        }
    }

    int indexOf(int v) const
    {
        for (int i = 1; i <= length; i++)
        {
            if (matrix[i][0] == v) return i;
        }
        return -1;
    }

public:
    // Constructor
    AdjacencyMatrixGraph(int capacity = 2)
    {
        if (capacity < 1) throw std::runtime_error("Invalid Capacity");

        this->capacity = capacity;
        length = 0;
        matrix = new int*[capacity];
        for (int i = 0; i < capacity; i++) matrix[i] = new int[capacity]();
    }

    ~AdjacencyMatrixGraph()
    {
        for (int i = 0; i < capacity; i++) delete[] matrix[i];
        delete[] matrix;
    }

    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if (indexOf(v) == -1)
        {
            matrix[++length][0] = v;
            matrix[0][length] = v;
            resizeMatrix();
        }
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);

        matrix[indexOf(u)][indexOf(v)] = 1;
        matrix[indexOf(v)][indexOf(u)] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        return indexOf(u) != -1 && indexOf(v) != -1 && matrix[indexOf(u)][indexOf(v)] == 1;
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        int idx = indexOf(v);
        if (idx != -1)
        {
            delete[] matrix[idx];
            for (int i = idx; i < length; i++) matrix[i] = matrix[i+1];
            matrix[length] = new int[capacity];

            for (int i = 1; i < length; i++)
            {
                for (int j = idx; j < length; j++) matrix[i][j] = matrix[i][j+1];
            }
            length--;
            resizeMatrix();
        }
        else std::cout << "Node doesn't exists" << std::endl;
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if (CheckEdge(u, v))
        {
            matrix[indexOf(u)][indexOf(v)] = 0;
            matrix[indexOf(v)][indexOf(u)] = 0;
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
        if (indexOf(u) != -1 && indexOf(v) != -1)
        {
            int* dist = new int[length+1];
            int* par = new int[length+1];
            for (int i = 0; i <= length; i++) dist[i] = length;
            dist[indexOf(v)] = 0;

            ArrayList<int> queue;
            queue.add(v);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                int idx = indexOf(n);
                queue.remove(n);

                for (int i = 1; i <= length; i++)
                {
                    if(matrix[idx][i] == 1 && dist[i] > dist[idx] + 1)
                    {
                        dist[i] = dist[idx] + 1;
                        par[i] = n;
                        queue.add(matrix[i][0]);
                    }
                }
            }

            std::cout << "Shortest path: ";
            for (int n = u; n != v; n = par[indexOf(n)]) std::cout << n << " ";
            std::cout << v << " " << std::endl;

            delete[] dist;
            delete[] par;
        }
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if (indexOf(u) != -1 && indexOf(v) != -1)
        {
            int* dist = new int[length+1];
            for (int i = 0; i <= length; i++) dist[i] = length;
            dist[indexOf(u)] = 0;

            ArrayList<int> queue;
            queue.add(u);
            while (queue.size() != 0)
            {
                int n = queue.getAt(0);
                int idx = indexOf(n);
                queue.remove(n);

                for (int i = 1; i <= length; i++)
                {
                    if(matrix[idx][i] == 1 && dist[i] > dist[idx] + 1)
                    {
                        dist[i] = dist[idx] + 1;
                        queue.add(matrix[i][0]);
                    }
                }
            }

            int n = -1;
            if (dist[indexOf(v)] < length) n = dist[indexOf(v)];

            delete[] dist;
            return n;
        }
        else return -1;
    }
    ArrayList<int> GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        int idx = indexOf(u);
        ArrayList<int> neighbors;
        if (idx != -1)
        {
            for (int i = 1; i <= length; i++)
            {
                if (matrix[idx][i] == 1) neighbors.add(matrix[i][0]);
            }
        }
        return neighbors;
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
