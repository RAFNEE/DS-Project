#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex);     
bool DFS(Graph* graph, char option,  int vertex);     
bool KWANGWOON(Graph* graph, int vertex);  
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, char option, int vertex);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex); //Bellman - Ford
bool FLOYD(Graph* graph, char option);   //FLoyd

class DisjointSet {
private:
    std::vector<int> parent;        // store parent
    std::vector<int> rank;      // store rank

public:
    // initialize DisjointSet
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // return the number of the root of the tree to which u belongs
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);        // path compression
        }
        return parent[u];
    }

    // merge two sets that contain u and v
    void union_set(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (rank[u] > rank[v]) {
                parent[v] = u;
            } else if (rank[u] < rank[v]) {
                parent[u] = v;
            } else {
                parent[v] = u;
                rank[u]++;
            }
        }
    }
};


#endif
