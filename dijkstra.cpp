#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MAX
#include <stdbool.h>  // For boolean types
#include <time.h>  // For benchmarking

#define MAX_NODES 1000

// Define the graph structure using an adjacency matrix (pure C style)
struct CGraph {
    int num_nodes;
    int adj[MAX_NODES][MAX_NODES];  // Adjacency matrix representation
    int weight[MAX_NODES][MAX_NODES];  // Matrix to store edge weights
};

// Initialize the graph with a specified number of nodes
void initCGraph(struct CGraph *g, int nodes) {
    g->num_nodes = nodes;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g->adj[i][j] = 0;  // No edges initially
            g->weight[i][j] = INT_MAX;  // No weights initially (INF for no connection)
        }
    }
}

// Add an edge between two nodes (with weight)
void addEdgeToCGraph(struct CGraph *g, int src, int dest, int w) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1;  // For undirected graph
    g->weight[src][dest] = w;
    g->weight[dest][src] = w;  // For undirected graph
}

// Dijkstra's algorithm using a simple array-based priority queue
void dijkstraCGraph(struct CGraph *g, int start) {
    int dist[g->num_nodes];  // Store the shortest distances from the start node
    bool visited[g->num_nodes];  // Track visited nodes

    // Initialize all distances to INF (INT_MAX) and visited to false
    for (int i = 0; i < g->num_nodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[start] = 0;  // Distance to the source is 0

    // Run the algorithm to find the shortest paths
    for (int i = 0; i < g->num_nodes; i++) {
        // Find the unvisited node with the smallest distance
        int u = -1;
        for (int j = 0; j < g->num_nodes; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break;  // No more reachable nodes

        visited[u] = true;  // Mark the node as visited

        // Update the distances of the neighbors of the selected node
        for (int v = 0; v < g->num_nodes; v++) {
            if (g->adj[u][v] && !visited[v] && dist[u] != INT_MAX && dist[u] + g->weight[u][v] < dist[v]) {
                dist[v] = dist[u] + g->weight[u][v];
            }
        }
    }
    /*
    // Print the result (distances from the start node)
    printf("Dijkstra's Shortest Path from node %d:\n", start);
    for (int i = 0; i < g->num_nodes; i++) {
        if (dist[i] == INT_MAX) {
            printf("Node %d is unreachable\n", i);
        } else {
            printf("Distance to node %d: %d\n", i, dist[i]);
        }
    }
    */
}

int c() {
    struct CGraph g;
    initCGraph(&g, 6);  // Initialize graph with 6 nodes

    // Adding edges (undirected with weights)
    addEdgeToCGraph(&g, 0, 1, 7);
    addEdgeToCGraph(&g, 0, 2, 9);
    addEdgeToCGraph(&g, 0, 3, 14);
    addEdgeToCGraph(&g, 1, 2, 10);
    addEdgeToCGraph(&g, 1, 3, 15);
    addEdgeToCGraph(&g, 2, 3, 11);
    addEdgeToCGraph(&g, 2, 4, 2);
    addEdgeToCGraph(&g, 3, 4, 6);

    clock_t start = clock();  // Start timer
    dijkstraCGraph(&g, 0);  // Perform Dijkstra's algorithm
    clock_t end = clock();    // End timer

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for Dijkstra in C: %f seconds\n", time_taken);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>  // For using std::priority_queue
#include <limits.h>  // For INT_MAX
#include <chrono> // For benchmarking
#include <iomanip>  // For fixed and setprecision
using namespace std;
using namespace chrono;

class CPPGraph {
public:
    int num_nodes;
    vector<vector<pair<int, int>>> adj;  // Adjacency list with weight (pair of <neighbor, weight>)

    CPPGraph(int nodes) {
        num_nodes = nodes;
        adj.resize(nodes);  // Resize adjacency list
    }

    void addEdgeToCPPGraph(int src, int dest, int w) {
        adj[src].push_back({dest, w});
        adj[dest].push_back({src, w});  // For undirected graph
    }

    void dijkstraCPPGraph(int start) {
        vector<int> dist(num_nodes, INT_MAX);  // Store the shortest distances from the start node
        vector<bool> visited(num_nodes, false);  // Track visited nodes

        dist[start] = 0;  // Distance to the source is 0

        // Priority queue to select the node with the smallest distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});  // Push the start node with distance 0

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;  // Skip if already visited
            visited[u] = true;

            // Explore the neighbors of the current node
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});  // Push the updated distance to the priority queue
                }
            }
        }
        /*
        // Print the result (distances from the start node)
        cout << "Dijkstra's Shortest Path from node " << start << ":\n";
        for (int i = 0; i < num_nodes; i++) {
            if (dist[i] == INT_MAX) {
                cout << "Node " << i << " is unreachable\n";
            } else {
                cout << "Distance to node " << i << ": " << dist[i] << endl;
            }
        }
        */
    }
};

int cpp() {
    CPPGraph g(6);  // Initialize graph with 6 nodes

    // Adding edges (undirected with weights)
    g.addEdgeToCPPGraph(0, 1, 7);
    g.addEdgeToCPPGraph(0, 2, 9);
    g.addEdgeToCPPGraph(0, 3, 14);
    g.addEdgeToCPPGraph(1, 2, 10);
    g.addEdgeToCPPGraph(1, 3, 15);
    g.addEdgeToCPPGraph(2, 3, 11);
    g.addEdgeToCPPGraph(2, 4, 2);
    g.addEdgeToCPPGraph(3, 4, 6);

    auto start = high_resolution_clock::now();  // Start timer
    g.dijkstraCPPGraph(0);  // Perform Dijkstra's algorithm
    auto end = high_resolution_clock::now();    // End timer

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken for Dijkstra in C++: " << fixed<<duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}
int main() {
    c();  // Call C Dijkstra function
    cpp();  // Call C++ Dijkstra function
    return 0;
}