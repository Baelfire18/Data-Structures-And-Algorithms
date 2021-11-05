#pragma once

// a structure to represent a weighted edge in graph
typedef struct edge {
  int src, dest, weight, id;
} Edge;

// a structure to represent a connected, undirected
// and weighted graph
typedef struct graph {
  // V-> Number of vertices, E-> Number of edges
  int V, E;
 
  // graph is represented as an array of edges.
  // Since the graph is undirected, the edge
  // from src to dest is also edge from dest
  // to src. Both are counted as 1 edge here.
  Edge* edge;
} Graph;

// A structure to represent a subset for union-find
typedef struct subset {
  int parent, rank;
} Subset;

Graph* createGraph(int V, int E);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int myComp(const void* a, const void* b);
void KruskalMST(Graph* graph, FILE* output_file);
