//-funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer -faggressive-loop-optimizations
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Include time.h for benchmarking
#include <stdbool.h>  // For using boolean types

#define MAX_NODES 1000

// Define the graph structure using adjacency matrix (pure C style)
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

// BFS traversal function (using queue)
void bfs(struct CGraph *g) {
    bool visited[g->num_nodes];  // Array to track visited nodes
    for (int i = 0; i < g->num_nodes; i++) {
        visited[i] = false;  // Mark all nodes as unvisited
    }

    int queue[g->num_nodes];  // Queue for BFS
    int front = 0, rear = 0;  // Front and rear pointers for queue

    visited[0] = true;  // Start from node 0
    queue[rear++] = 0;  // Add the starting node to the queue

    while (front < rear) {
        int node = queue[front++];  // Dequeue
        // printf("%d ", node);  // Uncomment for printing nodes (avoid during benchmarking)

        // Explore all neighbors of the current node
        for (int i = 0; i < g->num_nodes; i++) {
            if (g->adj[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;  // Enqueue unvisited neighbors
            }
        }
    }
}

int c() {
    struct CGraph g;
    initGraph(&g, 1000);  // Initialize graph with 1000 nodes

    // Adding edges (simple linear chain for benchmarking)
    for (int i = 0; i < 999; i++) {
        addEdge(&g, i, i + 1);
    }

    clock_t start = clock();  // Start timer
    bfs(&g);  // Perform BFS traversal (no printing of nodes)
    clock_t end = clock();    // End timer

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for BFS in C (no printing): %f seconds\n", time_taken);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>  // For using std::queue
#include <chrono> // For benchmarking
#include <iomanip>  // For fixed and setprecision
using namespace std;
using namespace chrono;

class CPPGraph {
public:
    int num_nodes;
    vector<vector<int>> adj;  // Adjacency list representation

    CPPGraph(int nodes) {
        num_nodes = nodes;
        adj.resize(nodes);  // Resize adjacency list
    }

    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);  // For undirected graph
    }

    void bfs() {
        vector<bool> visited(num_nodes, false);  // Track visited nodes
        queue<int> q;

        visited[0] = true;  // Start from node 0
        q.push(0);  // Add the starting node to the queue

        while (!q.empty()) {
            int node = q.front();  // Dequeue
            q.pop();
            // cout << node << " ";  // Uncomment for printing nodes (avoid during benchmarking)

            // Explore all neighbors of the current node
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);  // Enqueue unvisited neighbors
                }
            }
        }
    }
};

int cpp() {
    CPPGraph g(1000);  // Graph with 1000 nodes

    // Adding edges (simple linear chain for benchmarking)
    for (int i = 0; i < 999; i++) {
        g.addEdge(i, i + 1);
    }

    auto start = high_resolution_clock::now();  // Start timer
    g.bfs();  // Perform BFS traversal (no printing of nodes)
    auto end = high_resolution_clock::now();    // End timer

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for BFS in C++ (no printing): " << fixed<<duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}
int main(){
    c();  // Call C BFS function
    cpp();  // Call C++ BFS function
    return 0;
}