#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "ArrayList.h"


class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    ArrayList* adjacencyLists;
    int* nodes;
    int capacity;
    int nodeCount;

    //helper functions 

    int NodeIndex(int v) const {
        for(int i=0;i<nodeCount;i++){
            if(nodes[i]==v) 
            return i;
        }

        return -1;
    }

    

    void resizeList(int newCapacity){

            ArrayList* new_AdjacencyLists=new ArrayList[newCapacity];
            int* new_Nodes=new int[newCapacity];

            for(int i=0;i<nodeCount;i++){
                new_AdjacencyLists[i]=adjacencyLists[i];
                new_Nodes[i]=nodes[i];
            }

            delete[] adjacencyLists;
            delete[] nodes;

            adjacencyLists=new_AdjacencyLists;
            nodes=new_Nodes;

            capacity=newCapacity;
    }

    void BFSTraversal(int StartNode, bool* visited , int* parent, int* distance)const{

        int startIndex=NodeIndex(StartNode);

        if(startIndex==-1)
        return;

        for(int i=0;i<nodeCount;i++){
            visited[i]=0;
            parent[i]=-1;
            distance[i]=-1;
        }

        //custom queue for BFS traversal 

        int* queue =new int[nodeCount];
        int front=0;
        int rear=0;

        //pushing node in the queue
        queue[rear++]=startIndex;
        visited[startIndex]=1;
        distance[startIndex]=0;

        //popping from queue into traversal and checking unvisited neighbours

        while(front<rear){

            int currentIndex=queue[front++];

            for(int i=0;i<adjacencyLists[currentIndex].getSize();i++){

                int neighbour=adjacencyLists[currentIndex][i];
                int neighbour_Index=NodeIndex(neighbour);

                 
                if(!visited[neighbour_Index]){

                   visited[neighbour_Index]=1;
                   parent[neighbour_Index]=currentIndex;
                   distance[neighbour_Index]=distance[currentIndex]+1;
                   queue[rear++]=neighbour_Index;
                }
            }
        }

        delete[] queue;
    }

public:

    AdjacencyListGraph(){

        capacity=2;
        nodeCount=0;
        adjacencyLists=new ArrayList[capacity];
        nodes=new int[capacity];

    }

    ~AdjacencyListGraph(){
        delete[] adjacencyLists;
        delete[] nodes;
    }

    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.

        if(NodeIndex(v)!=-1) return;

        if(nodeCount>=capacity/2){
            resizeList(capacity*2);
        }

        nodes[nodeCount]=v;
        nodeCount++;

    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v

        AddNode(u);
        AddNode(v);

        int index1=NodeIndex(u);
        int index2=NodeIndex(v);

        // if(index1==-1 || index2==-1){

        //     std::cout<<"Node missing"<<std::endl;
        //     return;
        // }

        if(!adjacencyLists[index1].isAvailable(v)){
            adjacencyLists[index1].append(v);
        }

        if(!adjacencyLists[index2].isAvailable(u)){
            adjacencyLists[index2].append(u);
        }

    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v

        int index1=NodeIndex(u);
        int index2=NodeIndex(v);

        if(index1==-1 || index2 ==-1){

            std::cout<<"Node missing"<<std::endl;
            return false;
        }

        bool uv=adjacencyLists[index1].isAvailable(v);
        bool vu=adjacencyLists[index2].isAvailable(u);

        return uv && vu;

    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.

        int index=NodeIndex(v);

        if(index==-1) return;

        for(int i=0;i< adjacencyLists[index].getSize();i++){

            int neighbour=adjacencyLists[index][i];

            int neighbourIndex=NodeIndex(neighbour);

            adjacencyLists[neighbourIndex].remove(v);
        }

        for(int i=index; i<nodeCount-1;i++){
            nodes[i]=nodes[i+1];
            adjacencyLists[i]=adjacencyLists[i+1];
        }

        nodeCount--;

         if (nodeCount > 0) {
        adjacencyLists[nodeCount].clear();  
        }
        
        if(nodeCount< capacity/4 && capacity>2){
            resizeList(capacity/2);
        }

    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge

        int index1=NodeIndex(u);
        int index2=NodeIndex(v);

        if(index1==-1 || index2==-1){

            std::cout<<"Node missing"<<std::endl;
            return;
        }

        adjacencyLists[index1].remove(v);
        adjacencyLists[index2].remove(u);

    }

    bool CheckPath(int u, int v) const override
    {
                //TODO: Return true if there is a path between nodes u and v. Otherwise return false

                if(u==v) return true;

                bool* visited = new bool[nodeCount];

                for(int i = 0; i < nodeCount; i++) {
                    
                    visited[i] = 0;

                }

                int* parent=new int[nodeCount];
                int* distance =new int[nodeCount];

                BFSTraversal(u,visited,parent,distance);

                int index2=NodeIndex(v);

                if(index2==-1) return false;

                bool ans=visited[index2];

                delete[] visited;
                delete[] parent;
                delete[] distance;

                return ans;

    }

    void FindShortestPath(int u, int v) const override
    {
                //TODO: Find the shortest path between the nodes u and v and print it.

                int uIndex=NodeIndex(u);
                int vIndex=NodeIndex(v);


            if(uIndex==-1 || vIndex==-1){

                std::cout<<"No path exists between "<<u<<" and "<<v<<std::endl;
                return;
            }

            bool* visited = new bool[nodeCount];

             for(int i = 0; i < nodeCount; i++) {
                    
                    visited[i] = 0;

            }

                int* parent=new int[nodeCount];
                int* distance =new int[nodeCount];

            BFSTraversal(u,visited,parent,distance);
            
            if(!visited[vIndex]){
                std::cout<<"No path exists between "<<u<<" and "<<v<<std::endl;

            }else{
                
                int path[nodeCount];
                int current= vIndex;
                int length=0;

                while(current!=-1){
                    path[length++]=nodes[current];
                    current=parent[current];
                }

                for(int i=length-1;i>=0;i--){
                    std::cout<<path[i]<<" ";
                }
                 std::cout << std::endl;
            }

            delete[] visited;
            delete[] parent;
            delete[] distance;

    }

    int FindShortestPathLength(int u, int v) const override
    {
                //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.

                if(u==v) return 0;

                bool* visited =new bool[nodeCount];

                for(int i=0;i<nodeCount;i++){

                    visited[i]=0;
                }

                int* parent = new int[nodeCount];
                int* distance =new int[nodeCount];

            BFSTraversal(u,visited,parent,distance);

            int vIndex=NodeIndex(v);
            int shortestLength;

            if(vIndex!=-1 && visited[vIndex]){
                shortestLength=distance[vIndex];
            }else{
                shortestLength=-1;
            }

            delete[] visited;
            delete[] parent;
            delete[] distance;

            return shortestLength;

    }

    ArrayList GetNeighbors(int u) const override
    {
                //TODO: Return the list of neighbors.

                ArrayList neighbours;

                int uIndex=NodeIndex(u);

                if(uIndex==-1) return neighbours;

            for(int i=0;i<adjacencyLists[uIndex].getSize();i++){
                neighbours.append(adjacencyLists[uIndex][i]);
            }

            return neighbours;

    }

};

#endif // ADJACENCY_LIST_GRAPH_H
