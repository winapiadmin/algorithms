//-funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer -faggressive-loop-optimizations
//C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Include time.h for benchmarking

#define MAX_NODES 1000

// Define the graph structure using arrays (pure C style)
struct CGraph {
    int num_nodes;
    int adj[MAX_NODES][MAX_NODES];  // Adjacency matrix representation
};

// Initialize the graph with a specified number of nodes
void initGraph(struct CGraph *g, int nodes) {
    g->num_nodes = nodes;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g->adj[i][j] = 0;  // No edges initially
        }
    }
}

// Add an edge between two nodes (undirected for simplicity)
void addEdge(struct CGraph *g, int src, int dest) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1;  // For undirected graph
}

// DFS utility function (recursive)
void dfsUtil(struct CGraph *g, int node, int visited[]) {
    visited[node] = 1;
    //printf("%d ", node);  // Print the node

    // Explore all the neighbors
    for (int i = 0; i < g->num_nodes; i++) {
        if (g->adj[node][i] == 1 && !visited[i]) {
            dfsUtil(g, i, visited);  // Recursive call
        }
    }
}

// DFS traversal function
void dfs(struct CGraph *g) {
    int visited[g->num_nodes];  // Array to track visited nodes
    for (int i = 0; i < g->num_nodes; i++) {
        visited[i] = 0;  // Mark all nodes as unvisited
    }
    dfsUtil(g, 0, visited);  // Start DFS from node 0
}

int c() {
    struct CGraph g;
    initGraph(&g, 1000);  // Initialize graph with 1000 nodes

    // Adding edges (simple linear chain for benchmarking)
    for (int i = 0; i < 999; i++) {
        addEdge(&g, i, i + 1);
    }

    clock_t start = clock();  // Start timer
    dfs(&g);  // Perform DFS traversal
    clock_t end = clock();    // End timer

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken for DFS in C: %f seconds\n", time_taken);

    return 0;
}
//C++
#include <iostream>
#include <vector>
#include <chrono>  // For benchmarking
#include <stack>  // For stack implementation
#include <iomanip>  // For fixed and setprecision
using namespace std;
using namespace chrono;

class CPPGraph {
public:
    int num_nodes;
    vector<vector<int>> adj;

    CPPGraph(int nodes) {
        num_nodes = nodes;
        adj.resize(nodes);  // Resize adjacency list
    }

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);  // For undirected graph
    }

    void dfs() {
        vector<bool> visited(num_nodes, false);
        stack<int> s;

        s.push(0);  // Start DFS from node 0
        visited[0] = true;
        cout << "DFS traversal: ";

        while (!s.empty()) {
            int node = s.top();
            s.pop();
            //cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
        //cout << endl;
    }
};

int cpp() {
    CPPGraph g(1000);  // Graph with 1000 nodes
    
    // Adding edges (simple linear chain for benchmarking)
    for (int i = 0; i < 999; i++) {
        g.addEdge(i, i + 1);
    }

    auto start = high_resolution_clock::now();  // Start timer
    g.dfs();  // Perform DFS traversal
    auto end = high_resolution_clock::now();    // End timer

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for DFS in C++: " << fixed<<duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}
int main(){
    c();
    cpp();
    return 0;
}