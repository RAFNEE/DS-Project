#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<bool> visited(numVertices, false);       // visited array
    queue<int> q;       // queue for BFS

    q.push(vertex);     // push start vertex
    visited[vertex] = true;     // mark start vertex as visited

    string result = "";

    while (!q.empty()) {
        int current = q.front();        // current vertex
        q.pop();        // pop current vertex

        result += to_string(current) + " -> ";      // add current vertex to result

        map<int, int> adjEdges;     // adjacent edges
        if (option == 'Y') {
            graph->getAdjacentEdgesDirect(current, &adjEdges);
        }
        else if (option == 'N') {
            graph->getAdjacentEdges(current, &adjEdges);
        }

        // push adjacent vertices to queue
        for (auto iter = adjEdges.begin(); iter != adjEdges.end(); iter++) {
            int adjVertex = iter->first;
            if (!visited[adjVertex]) {
                q.push(adjVertex);
                visited[adjVertex] = true;
            }
        }
    }

    if (!result.empty()) {
        result = result.substr(0, result.length() - 4);
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "================ BFS ================" << endl;
    if (option == 'Y')
        fout << "Directed Graph BFS result" << endl;
    else if (option == 'N')
        fout << "Undirected Graph BFS result" << endl;
    fout << "startvertex: " << vertex << endl;
    fout << result << endl;
    fout << "=====================================" << endl << endl;
    fout.close();
    return true;
}

bool DFS(Graph* graph, char option, int vertex)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<bool> visited(numVertices, false);       // visited array
    stack<int> s;       // stack for DFS

    s.push(vertex);     // push start vertex

    string result = "";

    while (!s.empty()) {
        int current = s.top();      // current vertex

        // visit current vertex
        if (!visited[current]) {
            visited[current] = true;
            result += to_string(current) + " -> ";
        }

        map<int, int> adjEdges;     // adjacent edges
        if (option == 'Y') {
            graph->getAdjacentEdgesDirect(current, &adjEdges);
        }
        else if (option == 'N') {
            graph->getAdjacentEdges(current, &adjEdges);
        }
        
        // push adjacent vertices to stack
        if (adjEdges.empty()) {
            s.pop();
            continue;
        }
        else {
            // check if all adjacent vertices are visited
            for (auto iter = adjEdges.begin(); iter != adjEdges.end(); iter++) {
                int adjVertex = iter->first;
                auto iter2 = iter;
                iter2++;
                if (!visited[adjVertex]) {
                    s.push(adjVertex);
                    break;
                }
                else if (visited[adjVertex] && iter2 != adjEdges.end()) {
                    continue;
                }
                else {
                    s.pop();
                }
            }
        }
    }

    if (!result.empty()) {
        result = result.substr(0, result.length() - 4);
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "================ DFS ================" << endl;
    if (option == 'Y')
        fout << "Directed Graph DFS result" << endl;
    else if (option == 'N')
        fout << "Undirected Graph DFS result" << endl;
    fout << "Start vertex: " << vertex << endl;
    fout << result << endl;
    fout << "=====================================" << endl << endl;
    fout.close();
    return true;
}

// hybrid sort for Kruskal agraphorithm with insertion sort and quick sort
void HybridSort(vector<pair<pair<int, int>, int>>& edges, int low, int high)
{
    if (low < high) {
        // quick sort
        if (high - low + 1 >= 7) {
            int pivot = edges[high].second;     // pivot
            int i = low - 1;        // index of smaller element
            for (int j = low; j < high; j++) {
                // if current element is smaller than or equal to pivot
                if (edges[j].second < pivot) {
                    i++;
                    swap(edges[i], edges[j]);       // swap elements
                }
            }
            // swap pivot and i + 1
            swap(edges[i + 1], edges[high]);
            int pi = i + 1;     // index of pivot

            HybridSort(edges, low, pi - 1);     // quick sort left partition
            HybridSort(edges, pi + 1, high);        // quick sort right partition
        }
        else { // insertion sort
            for (int i = low + 1; i <= high; i++) {
                auto key = edges[i];        // key
                int j = i - 1;      // index of previous element
                while (j >= low && edges[j].second > key.second) {
                    edges[j + 1] = edges[j];        // move elements
                    j--;
                }
                edges[j + 1] = key;     // insert key
            }
        }
    }
}

bool Kruskal(Graph* graph)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<pair<pair<int, int>, int>> edges;        // edges

    // extract edges
    for (int i = 0; i < numVertices; i++) {
        map<int, int> adjEdges;     // adjacent edges
        graph->getAdjacentEdges(i + 1, &adjEdges);      // get adjacent edges

        // add edges to vector
        for (auto& p : adjEdges) {
            int current = i;        // start vertex
            int v = p.first;        // end vertex
            if (current < v) {      // add edge only once
                edges.push_back(make_pair(make_pair(current, v - 1), p.second));
            }
        }
    }

    // sort edges
    HybridSort(edges, 0, edges.size() - 1);

    DisjointSet ds(numVertices);        // disjoint set
    vector<pair<int, int>> mst;     // minimum spanning tree
    int totalWeight = 0;        // total weight of minimum spanning tree

    for (auto& e : edges) {
        int current = e.first.first;        // start vertex
        int v = e.first.second;     // end vertex
        // if current edge does not form a cycle
        if (ds.find(current) != ds.find(v)) {
            ds.union_set(current, v);       // merge two sets
            mst.push_back(make_pair(current, v));       // add edge to minimum spanning tree
            totalWeight += e.second;        // add weight to total weight
        }
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "============== Kruskal ==============" << endl;
    vector<vector<pair<int, int>>> adjList(numVertices);

    // convert minimum spanning tree to adjacency list
    for (auto& m : mst) {
        int current = m.first;   // start vertex
        int v = m.second;  // end vertex
        int weight = 0;
        
        // find weight of edge
        for (auto& edge : edges) {
            if (edge.first.first == current && edge.first.second == v) {
                weight = edge.second;
                break;
            }
        }

        adjList[current].push_back(make_pair(v + 1, weight));       // add edge to adjacency list
        adjList[v].push_back(make_pair(current + 1, weight));       // add edge to adjacency list because graph is undirected
    }

    // write adjacency list
    for (int i = 0; i < numVertices; i++) {
        fout << "[" << i + 1 << "] ";
        sort(adjList[i].begin(), adjList[i].end());     // sort adjacency list

        for (auto& p : adjList[i]) {
            fout << p.first << "(" << p.second << ")";
        }
        fout << endl;
    }
    fout << "cost: " << totalWeight << endl;
    fout << "=====================================" << endl << endl;

    fout.close();
    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<int> dist(numVertices, numeric_limits<int>::max());      // distance array
    vector<int> prev(numVertices, -1);      // previous vertex array
    vector<bool> visited(numVertices, false);       // visited array
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;     // priority queue for Dijkstra

    dist[vertex - 1] = 0;       // set distance of start vertex to 0
    pq.push(make_pair(0, vertex - 1));      // push start vertex to priority queue

    while (!pq.empty()) {
        int current = pq.top().second;      // current vertex
        int distance = pq.top().first;      // distance of current vertex
        pq.pop();       // pop current vertex

        map<int, int> adjEdges;     // adjacent edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(current + 1, &adjEdges);
        else
            graph->getAdjacentEdges(current + 1, &adjEdges);

        // check if current vertex is visited
        for (auto& p : adjEdges) {
            int v = p.first - 1;        // adjacent vertex
            int weight = p.second;      // weight of edge
            if (weight < 0) {
                return false;
            }

            // compare distance
            if (dist[v] > dist[current] + weight) {     // if distance is larger than distance of current vertex + weight of edge
                dist[v] = dist[current] + weight;       // update distance
                prev[v] = current;      // update previous vertex
                pq.push(make_pair(dist[v], v));     // push adjacent vertex to priority queue
            }
        }
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "============== Dijkstra ==============" << endl;
    if (option == 'Y')
        fout << "Directed Graph Dijkstra result" << endl;
    else if (option == 'N')
        fout << "Undirected Graph Dijkstra result" << endl;
    fout << "Start vertex: " << vertex << endl;

    for (int i = 0; i < numVertices; i++) {
        if (i + 1 != vertex)
            fout << "[" << i + 1 << "] ";
        if (dist[i] == numeric_limits<int>::max()) {
            fout << "x" << endl;
            continue;
        }

        // reverse path
        vector<int> path;
        for (int at = i; at != -1; at = prev[at]) {
            path.push_back(at + 1);
        }
        reverse(path.begin(), path.end());

        string result;
        if (i + 1 != vertex) {
            for (int p : path) {
                result += to_string(p) + " -> ";
            }
            result = result.substr(0, result.length() - 3);
            fout << result;
        }

        if (i + 1 != vertex)
            fout << "(" << dist[i] << ")" << endl;
    }
    fout << "======================================" << endl << endl;
    fout.close();
    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<int> dist(numVertices, numeric_limits<int>::max());      // distance array
    vector<int> prev(numVertices, -1);      // previous vertex array
    dist[s_vertex - 1] = 0;     // set distance of start vertex to 0

    vector<tuple<int, int, int>> edges;     // edges
    for (int i = 0; i < numVertices; i++) {
        map<int, int> adjEdges;     // adjacent edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(i + 1, &adjEdges);
        else
            graph->getAdjacentEdges(i + 1, &adjEdges);

        for (auto& p : adjEdges) {
            edges.emplace_back(i, p.first - 1, p.second);       // add edge to vector
        }
    }
    
    for (int i = 0; i < numVertices - 1; i++) {
        for (auto& e : edges) {
            int current = get<0>(e), v = get<1>(e), weight = get<2>(e);     // start vertex, end vertex, weight of edge
            // compare distance
            if (dist[current] != numeric_limits<int>::max() && dist[v] > dist[current] + weight) {      // if distance is larger than distance of current vertex + weight of edge
                dist[v] = dist[current] + weight;       // update distance
                prev[v] = current;      // update previous vertex
            }
        }
    }

    // check if there is negative cycle
    for (auto& e : edges) {
        int current = get<0>(e), v = get<1>(e), weight = get<2>(e);     // start vertex, end vertex, weight of edge
        if (dist[current] != numeric_limits<int>::max() && dist[v] > dist[current] + weight) {      // if distance is larger than distance of current vertex + weight of edge
            return false;       // negative cycle exists
        }
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "============ Bellman-Ford ============" << endl;
        if (option == 'Y')
            fout << "Directed Graph Bellman-Ford result" << endl;
        else if (option == 'N')
            fout << "Undirected Graph Bellman-Ford result" << endl;
    if (dist[e_vertex - 1] == numeric_limits<int>::max()) {
        fout << "x" << endl;
    }
    else {
        // reverse path
        vector<int> path;
        for (int at = e_vertex - 1; at != -1; at = prev[at]) {
            path.push_back(at + 1);
        }
        reverse(path.begin(), path.end());
        string result;
            for (int p : path) {
                result += to_string(p) + " -> ";
            }
            result = result.substr(0, result.length() - 4);
            fout << result << endl;
        fout << "cost: " << dist[e_vertex - 1] << endl;
    }
    fout << "======================================" << endl << endl;
    fout.close();

    return true;
}

bool FLOYD(Graph* graph, char option)
{
    int numVertices = graph->getSize();     // number of vertices
    vector<vector<int>> dist(numVertices, vector<int>(numVertices, numeric_limits<int>::max()));        // distance array

    // initialize graph
    for (int i = 0; i < numVertices; i++) {
        dist[i][i] = 0;     // initialize distance of vertex to itself
        map<int, int> adjEdges;     // adjacent edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(i + 1, &adjEdges);
        else
            graph->getAdjacentEdges(i + 1, &adjEdges);

        for (auto& p : adjEdges) {
            dist[i][p.first - 1] = p.second;        // add edge to distance array
        }
    }

    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                // if distance of vertex i to vertex k and distance of vertex k to vertex j is smaller than distance of vertex i to vertex j
                if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max() && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];       // update distance
                }
            }
        }
    }

    // check if there is negative cycle
    for (int i = 0; i < numVertices; i++) {
        if (dist[i][i] < 0) {
            return false;       // negative cycle exists
        }
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;
    
    fout << "=============== FLOYD ===============" << endl;
        if (option == 'Y')
            fout << "Directed Graph FLOYD result" << endl;
        else if (option == 'N')
            fout << "Undirected Graph FLOYD result" << endl;
    for (int i = 0; i < numVertices; i++) {
        fout << "[" << i + 1 << "] ";
        for (int j = 0; j < numVertices; j++) {
            if (dist[i][j] == numeric_limits<int>::max())
                fout << "x ";
            else
                fout << dist[i][j] << " ";
        }
        fout << endl;
    }
    fout << "=====================================" << endl << endl;
    fout.close();

    return true;
}

bool KWANGWOON(Graph* graph, int vertex)
{
    if (graph->getType() == true) {     // if graph is matrix, return false
        return false;
    }

    int numVertices = graph->getSize();     // number of vertices
    if (vertex < 0 || vertex >= numVertices) {        // if vertex is out of range, return false
        return false;
    }

    vector<bool> visited(numVertices, false);       // visited array
    int current = vertex - 1;       // current vertex
    string result = "";

    while (!visited[current]) {
        visited[current] = true;        // mark current vertex as visited
        result += to_string(current + 1) + " -> ";

        map<int, int> neighbors;        // adjacent edges
        graph->getAdjacentEdges(current + 1, &neighbors);       // get adjacent edges

        int edgeCount = neighbors.size();       // number of edges
        for (auto& neighbor : neighbors) {        // check if adjacent vertices are visited
            if (visited[neighbor.first - 1]) {
                edgeCount--;
            }
        }
        int nextVertex = -1;        // next vertex

        if (edgeCount % 2 == 0) {       // if number of edges is even
            for (auto& neighbor : neighbors) {
                if (!visited[neighbor.first - 1] && (nextVertex == -1 || neighbor.first < nextVertex)) {
                    nextVertex = neighbor.first - 1;        // set next vertex to smaller adjacent vertex
                }
            }
        }
        else {      // if number of edges is odd
            for (auto& neighbor : neighbors) {
                if (!visited[neighbor.first - 1] && neighbor.first - 1 > nextVertex) {
                    nextVertex = neighbor.first - 1;        // set next vertex to larger adjacent vertex
                }
            }
        }

        if (nextVertex == -1) {     // if there is no next vertex, break
            break;
        }
        current = nextVertex;       // set current vertex to next vertex
    }

    if (!result.empty()) {
        result = result.substr(0, result.length() - 4);     // remove last " -> "
    }

    // write result
    ofstream fout("log.txt", ios::app);
    if (!fout.is_open())
        return false;

    fout << "============= KWANGWOON =============" << endl;
    fout << "Start vertex: " << vertex << endl;
    fout << result << endl;
    fout << "=====================================" << endl << endl;
    fout.close();
    return true;
}
