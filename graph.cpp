/*
    File: graph.cpp
    This file contains two implementations of common graph algorithms.
    • CGraph is a C-style “class” (using structs and functions) for graph algorithms.
    • CPPGraph is a C++ class that implements the same algorithms using STL.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

// ---------------------------
// C IMPLEMENTATION (CGraph)
// ---------------------------

#define INF 1000000000

// CEdge – linked list node for an adjacency list.
typedef struct CEdge {
     int v;
     int weight;
     struct CEdge* next;
} CEdge;

// CGraph – graph structure (C style)
typedef struct CGraph {
     int n;
     CEdge** adj; // array of pointer to CEdge linked lists
} CGraph;

// Create a new CGraph with n vertices.
CGraph* createCGraph(int n) {
     CGraph* g = (CGraph*) malloc(sizeof(CGraph));
     g->n = n;
     g->adj = (CEdge**) malloc(n * sizeof(CEdge*));
     for (int i = 0; i < n; i++) {
          g->adj[i] = NULL;
     }
     return g;
}

// Free the memory allocated for the graph.
void freeCGraph(CGraph* g) {
     for (int i = 0; i < g->n; i++) {
          CEdge* edge = g->adj[i];
          while (edge) {
                CEdge* temp = edge;
                edge = edge->next;
                free(temp);
          }
     }
     free(g->adj);
     free(g);
}

// Add a directed edge u -> v with weight w.
void CGraph_addEdge(CGraph* g, int u, int v, int w) {
     CEdge* edge = (CEdge*) malloc(sizeof(CEdge));
     edge->v = v;
     edge->weight = w;
     edge->next = g->adj[u];
     g->adj[u] = edge;
}

// DFS utility for CGraph.
void CGraph_DFSUtil(CGraph* g, int v, int* visited) {
     visited[v] = 1;
     printf("%d ", v);
     for (CEdge* e = g->adj[v]; e != NULL; e = e->next) {
          if (!visited[e->v]) {
                CGraph_DFSUtil(g, e->v, visited);
          }
     }
}

// Depth-First Search starting from vertex start.
void CGraph_DFS(CGraph* g, int start) {
     int* visited = (int*) calloc(g->n, sizeof(int));
     printf("CGraph DFS: ");
     CGraph_DFSUtil(g, start, visited);
     printf("\n");
     free(visited);
}

// Breadth-First Search starting from vertex start.
void CGraph_BFS(CGraph* g, int start) {
     int* visited = (int*) calloc(g->n, sizeof(int));
     int* queue = (int*) malloc(g->n * sizeof(int));
     int front = 0, back = 0;
     visited[start] = 1;
     queue[back++] = start;
     printf("CGraph BFS: ");
     while (front < back) {
          int u = queue[front++];
          printf("%d ", u);
          for (CEdge* e = g->adj[u]; e != NULL; e = e->next) {
                if (!visited[e->v]) {
                     visited[e->v] = 1;
                     queue[back++] = e->v;
                }
          }
     }
     printf("\n");
     free(visited);
     free(queue);
}

// Dijkstra's Algorithm from start. Prints distances.
void CGraph_dijkstra(CGraph* g, int start) {
     int* dist = (int*) malloc(g->n * sizeof(int));
     int* used = (int*) calloc(g->n, sizeof(int));
     for (int i = 0; i < g->n; i++) dist[i] = INF;
     dist[start] = 0;
     for (int i = 0; i < g->n; i++) {
          int u = -1;
          for (int j = 0; j < g->n; j++) {
                if (!used[j] && (u == -1 || dist[j] < dist[u]))
                     u = j;
          }
          if(dist[u]==INF) break;
          used[u] = 1;
          for (CEdge* e = g->adj[u]; e; e = e->next) {
                if(dist[u] + e->weight < dist[e->v])
                     dist[e->v] = dist[u] + e->weight;
          }
     }
     printf("CGraph Dijkstra distances from %d:\n", start);
     for (int i = 0; i < g->n; i++) {
          printf("%d: %s%d\n", i, (dist[i]==INF?"INF ":""), dist[i]);
     }
     free(dist);
     free(used);
}

// Bellman-Ford Algorithm from start. Prints distances.
void CGraph_bellmanFord(CGraph* g, int start) {
     int* dist = (int*) malloc(g->n * sizeof(int));
     for (int i = 0; i < g->n; i++) dist[i] = INF;
     dist[start] = 0;
     // Relax edges |V|-1 times.
     for (int i = 0; i < g->n - 1; i++) {
          for (int u = 0; u < g->n; u++) {
                for (CEdge* e = g->adj[u]; e != NULL; e = e->next) {
                     if(dist[u]!=INF && dist[u] + e->weight < dist[e->v]) {
                          dist[e->v] = dist[u] + e->weight;
                     }
                }
          }
     }
     printf("CGraph Bellman-Ford distances from %d:\n", start);
     for (int i = 0; i < g->n; i++) {
          printf("%d: %s%d\n", i, (dist[i]==INF?"INF ":""), dist[i]);
     }
     free(dist);
}

// Floyd-Warshall Algorithm. Prints distance matrix.
void CGraph_floydWarshall(CGraph* g) {
     int n = g->n;
     int** dist = (int**) malloc(n * sizeof(int*));
     for (int i = 0; i < n; i++) {
          dist[i] = (int*) malloc(n * sizeof(int));
          for (int j = 0; j < n; j++) {
                dist[i][j] = (i == j) ? 0 : INF;
          }
          for (CEdge* e = g->adj[i]; e != NULL; e = e->next) {
                dist[i][e->v] = e->weight;
          }
     }
     for (int k = 0; k < n; k++)
          for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                     if(dist[i][k]!=INF && dist[k][j]!=INF && dist[i][k] + dist[k][j] < dist[i][j])
                          dist[i][j] = dist[i][k] + dist[k][j];
                          
     printf("CGraph Floyd-Warshall distance matrix:\n");
     for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
                if (dist[i][j]==INF)
                     printf("INF ");
                else
                     printf("%d ", dist[i][j]);
          }
          printf("\n");
     }
     for (int i = 0; i < n; i++)
          free(dist[i]);
     free(dist);
}

// A* Algorithm (using a dummy heuristic that always returns 0)
// Finds shortest path from start to goal.
void CGraph_aStar(CGraph* g, int start, int goal) {
     // In this simple implementation, A* equals Dijkstra’s
     int* dist = (int*) malloc(g->n * sizeof(int));
     for (int i = 0; i < g->n; i++) dist[i] = INF;
     dist[start] = 0;
     typedef struct Node {
          int vertex, f;
     } Node;
     auto cmp = [](const Node& a, const Node& b) { return a.f > b.f; };
     priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
     pq.push({start, 0});
     while (!pq.empty()) {
          Node cur = pq.top();
          pq.pop();
          if (cur.vertex == goal) break;
          for (CEdge* e = g->adj[cur.vertex]; e; e = e->next) {
                int tentative = dist[cur.vertex] + e->weight;
                if (tentative < dist[e->v]) {
                     dist[e->v] = tentative;
                     // heuristic is 0
                     pq.push({e->v, tentative});
                }
          }
     }
     printf("CGraph A* distance from %d to %d: %s%d\n", start, goal,
              (dist[goal]==INF?"INF ":""), dist[goal]);
     free(dist);
}

// Prim's Algorithm (minimum spanning tree) for undirected graphs.
// This implementation assumes that each edge is added in one direction only.
// For a correct undirected MST, add both directions.
void CGraph_primMST(CGraph* g, int start) {
     vector<int> key(g->n, INF);
     vector<int> inMST(g->n, 0);
     key[start] = 0;
     int total = 0;
     for (int i = 0; i < g->n; i++) {
          int u = -1;
          for (int v = 0; v < g->n; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u]))
                     u = v;
          }
          if(key[u]==INF) break;
          inMST[u] = 1;
          total += key[u];
          for (CEdge* e = g->adj[u]; e; e = e->next) {
                if (!inMST[e->v] && e->weight < key[e->v])
                     key[e->v] = e->weight;
          }
     }
     printf("CGraph Prim's MST total weight: %d\n", total);
}

// Kruskal's Algorithm (minimum spanning tree) using Union-Find.
typedef struct {
     int u, v, w;
} CEdgeRecord;

int findSet(int v, vector<int>& parent) {
     if (parent[v] != v)
          parent[v] = findSet(parent[v], parent);
     return parent[v];
}

void unionSet(int u, int v, vector<int>& parent) {
     parent[findSet(u, parent)] = findSet(v, parent);
}

void CGraph_kruskalMST(CGraph* g) {
     vector<CEdgeRecord> edges;
     for (int u = 0; u < g->n; u++) {
          for (CEdge* e = g->adj[u]; e; e = e->next) {
                // For undirected graph, ensure each edge is processed once.
                if (u < e->v)
                     edges.push_back({u, e->v, e->weight});
          }
     }
     sort(edges.begin(), edges.end(), [](const CEdgeRecord& a, const CEdgeRecord& b) {
          return a.w < b.w;
     });
     vector<int> parent(g->n);
     for (int i = 0; i < g->n; i++) parent[i] = i;
     int mst_weight = 0;
     for (auto &e : edges) {
          if (findSet(e.u, parent) != findSet(e.v, parent)) {
                unionSet(e.u, e.v, parent);
                mst_weight += e.w;
          }
     }
     printf("CGraph Kruskal's MST total weight: %d\n", mst_weight);
}

// Topological Sorting using DFS in a directed acyclic graph.
void CGraph_topologicalSortUtil(CGraph* g, int v, int* visited, int* stack, int* top) {
     visited[v] = 1;
     for (CEdge* e = g->adj[v]; e != NULL; e = e->next) {
          if (!visited[e->v])
                CGraph_topologicalSortUtil(g, e->v, visited, stack, top);
     }
     stack[(*top)++] = v;
}

void CGraph_topologicalSort(CGraph* g) {
     int* visited = (int*) calloc(g->n, sizeof(int));
     int* stack = (int*) malloc(g->n * sizeof(int));
     int top = 0;
     for (int i = 0; i < g->n; i++) {
          if (!visited[i])
                CGraph_topologicalSortUtil(g, i, visited, stack, &top);
     }
     printf("CGraph Topological Sort: ");
     // reverse order in stack
     for (int i = top - 1; i >= 0; i--) {
          printf("%d ", stack[i]);
     }
     printf("\n");
     free(visited);
     free(stack);
}

// ---------------------------
// C++ IMPLEMENTATION (CPPGraph)
// ---------------------------
class CPPGraph {
public:
     int n;
     vector<vector<pair<int,int>>> adj; // (neighbor, weight)

     CPPGraph(int n): n(n), adj(n) {}

     void addEdge(int u, int v, int weight) {
          // For directed graph; for undirected add both directions.
          adj[u].push_back({v, weight});
     }

     void DFSUtil(int v, vector<bool>& visited) {
          visited[v] = true;
          cout << v << " ";
          for (auto &edge : adj[v]) {
                if (!visited[edge.first])
                     DFSUtil(edge.first, visited);
          }
     }

     void DFS(int start) {
          vector<bool> visited(n, false);
          cout << "CPPGraph DFS: ";
          DFSUtil(start, visited);
          cout << "\n";
     }

     void BFS(int start) {
          vector<bool> visited(n, false);
          queue<int> q;
          visited[start] = true;
          q.push(start);
          cout << "CPPGraph BFS: ";
          while(!q.empty()){
                int u = q.front();
                q.pop();
                cout << u << " ";
                for(auto& edge: adj[u]){
                     if(!visited[edge.first]){
                          visited[edge.first] = true;
                          q.push(edge.first);
                     }
                }
          }
          cout << "\n";
     }

     vector<int> dijkstra(int start) {
          vector<int> dist(n, INF);
          dist[start] = 0;
          priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
          pq.push({0, start});
          while(!pq.empty()){
                auto [d, u] = pq.top(); pq.pop();
                if(d != dist[u]) continue;
                for(auto &edge: adj[u]){
                     int v = edge.first, w = edge.second;
                     if(dist[u] + w < dist[v]){
                          dist[v] = dist[u] + w;
                          pq.push({dist[v], v});
                     }
                }
          }
          cout << "CPPGraph Dijkstra distances from " << start << ":\n";
          for (int i = 0; i < n; i++)
                cout << i << ": " << (dist[i]==INF?"INF":to_string(dist[i])) << "\n";
          return dist;
     }

     // Bellman-Ford: returns true if no negative cycle, fills dist vector.
     bool bellmanFord(int start, vector<int>& dist) {
          dist.assign(n, INF);
          dist[start] = 0;
          for(int i = 0;i < n - 1;i++){
                for(int u = 0; u < n; u++){
                     for(auto &edge: adj[u]){
                          int v = edge.first, w = edge.second;
                          if(dist[u]!=INF && dist[u] + w < dist[v])
                                dist[v] = dist[u] + w;
                     }
                }
          }
          // Check for negative cycle
          for (int u = 0; u < n; u++){
                for(auto &edge: adj[u]){
                     int v = edge.first, w = edge.second;
                     if(dist[u]!=INF && dist[u] + w < dist[v])
                          return false;
                }
          }
          cout << "CPPGraph Bellman-Ford distances from " << start << ":\n";
          for (int i = 0; i < n; i++)
                cout << i << ": " << (dist[i]==INF?"INF":to_string(dist[i])) << "\n";
          return true;
     }

     vector<vector<int>> floydWarshall() {
          vector<vector<int>> dist(n, vector<int>(n, INF));
          for(int i = 0;i < n; i++){
                dist[i][i] = 0;
                for(auto &edge: adj[i]){
                     dist[i][edge.first] = edge.second;
                }
          }
          for (int k = 0; k < n; k++)
                for (int i = 0; i < n; i++)
                     for (int j = 0; j < n; j++)
                          if(dist[i][k]!=INF && dist[k][j]!=INF)
                                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          cout << "CPPGraph Floyd-Warshall distance matrix:\n";
          for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                     if(dist[i][j]==INF)
                          cout << "INF ";
                     else
                          cout << dist[i][j] << " ";
                }
                cout << "\n";
          }
          return dist;
     }

     // A* Algorithm using a heuristic function.
     vector<int> aStar(int start, int goal, function<int(int,int)> heuristic) {
          vector<int> gscore(n, INF), fscore(n, INF), cameFrom(n, -1);
          gscore[start] = 0;
          fscore[start] = heuristic(start, goal);
          typedef pair<int,int> pii; // (fscore, vertex)
          priority_queue<pii, vector<pii>, greater<pii>> openSet;
          openSet.push({fscore[start], start});
          while(!openSet.empty()){
                int current = openSet.top().second;
                openSet.pop();
                if(current == goal) break;
                for(auto &edge: adj[current]){
                     int tentative = gscore[current] + edge.second;
                     if(tentative < gscore[edge.first]){
                          cameFrom[edge.first] = current;
                          gscore[edge.first] = tentative;
                          fscore[edge.first] = tentative + heuristic(edge.first, goal);
                          openSet.push({fscore[edge.first], edge.first});
                     }
                }
          }
          cout << "CPPGraph A* path cost from " << start << " to " << goal << ": ";
          if(gscore[goal]==INF) {
                cout << "No path found\n";
          } else {
                cout << gscore[goal] << "\n";
          }
          return cameFrom; // For simplicity, we return the cameFrom array.
     }

     // Prim's Algorithm (for undirected graph). Assumes edges added in one direction should be mirrored.
     int primMST() {
          vector<int> key(n, INF);
          vector<bool> inMST(n, false);
          key[0] = 0;
          int total = 0;
          for(int i = 0; i < n; i++){
                int u = -1;
                for (int v = 0; v < n; v++) {
                     if (!inMST[v] && (u == -1 || key[v] < key[u]))
                          u = v;
                }
                if(key[u]==INF) break;
                inMST[u] = true;
                total += key[u];
                for(auto &edge: adj[u]){
                     if(!inMST[edge.first] && edge.second < key[edge.first])
                          key[edge.first] = edge.second;
                }
          }
          cout << "CPPGraph Prim's MST total weight: " << total << "\n";
          return total;
     }

     // Kruskal's Algorithm (for undirected graph) using Union-Find.
     int kruskalMST() {
          struct EdgeRecord {
                int u, v, w;
          };
          vector<EdgeRecord> edges;
          for (int u = 0; u < n; u++){
                for(auto &edge : adj[u]){
                     if(u < edge.first) // to avoid duplicates
                          edges.push_back({u, edge.first, edge.second});
                }
          }
          sort(edges.begin(), edges.end(), [](const EdgeRecord& a, const EdgeRecord& b) {
                return a.w < b.w;
          });
          vector<int> parent(n);
          for (int i = 0; i < n; i++) parent[i] = i;
          function<int(int)> findSet = [&](int v) {
                return parent[v] == v ? v : parent[v] = findSet(parent[v]);
          };
          auto unionSet = [&](int u, int v) {
                parent[findSet(u)] = findSet(v);
          };
          int mst_weight = 0;
          for(auto &e: edges){
                if(findSet(e.u) != findSet(e.v)){
                     unionSet(e.u, e.v);
                     mst_weight += e.w;
                }
          }
          cout << "CPPGraph Kruskal's MST total weight: " << mst_weight << "\n";
          return mst_weight;
     }

     // Topological Sort using DFS (for DAGs)
     vector<int> topologicalSort() {
          vector<bool> visited(n, false);
          vector<int> order;
          function<void(int)> dfs = [&](int v) {
                visited[v] = true;
                for(auto &edge: adj[v]){
                     if(!visited[edge.first])
                          dfs(edge.first);
                }
                order.push_back(v);
          };
          for (int i = 0; i < n; i++){
                if(!visited[i])
                     dfs(i);
          }
          reverse(order.begin(), order.end());
          cout << "CPPGraph Topological Sort: ";
          for (int v: order)
                cout << v << " ";
          cout << "\n";
          return order;
     }
};

// ---------------------------
// Main function to demonstrate usage
// ---------------------------
int main() {
     // CGraph demonstration
     int n = 6;
     CGraph* cgraph = createCGraph(n);
     // Create some edges (directed graph for DFS/BFS; for MST assume undirected by adding reverse)
     CGraph_addEdge(cgraph, 0, 1, 4);
     CGraph_addEdge(cgraph, 0, 2, 2);
     CGraph_addEdge(cgraph, 1, 2, 1);
     CGraph_addEdge(cgraph, 1, 3, 5);
     CGraph_addEdge(cgraph, 2, 3, 8);
     CGraph_addEdge(cgraph, 2, 4, 10);
     CGraph_addEdge(cgraph, 3, 4, 2);
     CGraph_addEdge(cgraph, 3, 5, 6);
     CGraph_addEdge(cgraph, 4, 5, 3);

     CGraph_DFS(cgraph, 0);
     CGraph_BFS(cgraph, 0);
     CGraph_dijkstra(cgraph, 0);
     CGraph_bellmanFord(cgraph, 0);
     CGraph_floydWarshall(cgraph);
     CGraph_aStar(cgraph, 0, 5);
     CGraph_primMST(cgraph, 0);
     CGraph_kruskalMST(cgraph);
     CGraph_topologicalSort(cgraph);
     freeCGraph(cgraph);

     // CPPGraph demonstration
     CPPGraph cppgraph(n);
     // For undirected MST algorithms, add edges in both directions.
     cppgraph.addEdge(0, 1, 4); cppgraph.addEdge(1, 0, 4);
     cppgraph.addEdge(0, 2, 2); cppgraph.addEdge(2, 0, 2);
     cppgraph.addEdge(1, 2, 1); cppgraph.addEdge(2, 1, 1);
     cppgraph.addEdge(1, 3, 5); cppgraph.addEdge(3, 1, 5);
     cppgraph.addEdge(2, 3, 8); cppgraph.addEdge(3, 2, 8);
     cppgraph.addEdge(2, 4, 10); cppgraph.addEdge(4, 2, 10);
     cppgraph.addEdge(3, 4, 2); cppgraph.addEdge(4, 3, 2);
     cppgraph.addEdge(3, 5, 6); cppgraph.addEdge(5, 3, 6);
     cppgraph.addEdge(4, 5, 3); cppgraph.addEdge(5, 4, 3);

     cppgraph.DFS(0);
     cppgraph.BFS(0);
     cppgraph.dijkstra(0);
     vector<int> bf_dist;
     cppgraph.bellmanFord(0, bf_dist);
     cppgraph.floydWarshall();
     // For A*, we use a dummy heuristic (always returns 0)
     cppgraph.aStar(0, 5, [](int a, int b){ return 0; });
     cppgraph.primMST();
     cppgraph.kruskalMST();
     cppgraph.topologicalSort();

     return 0;
}