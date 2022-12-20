// C program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../structs/structs.h"

// Driver program to test above functions
int main(int argc, char** argv) {
  // We check arguments
  if (argc != 3) {
    printf("Modo de uso: %s <network.txt> <output.txt>\n", argv[0]);
    return 1;
  }

  FILE* input_file = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");

  int clients;
  int centers;
  int roads;
  fscanf(input_file, "%d %d %d", &clients, &centers, &roads);
  // printf("%d %d %d\n", clients, centers, roads);

  // Create graph
  int V = clients + centers;       // Number of vertices in graph
  int E = roads + (centers - 1);   // Number of edges in graph
  Graph* graph = createGraph(V, E);

  // Crete roads
  for (int id = 0; id < roads; id++) {
    int src;
    int dest;
    int weight;
    fscanf(input_file, "%d %d %d", &src, &dest, &weight);
    // printf("%d %d %d\n", src, dest, weight);
    graph->edge[id].src = src;
    graph->edge[id].dest = dest;
    graph->edge[id].weight = weight;
    graph->edge[id].id = id;
  }

  // We add roads that as 0 cost in the centers for Kruskal to work
  for (int c = 0; c < centers - 1; c++) {
    graph->edge[roads + c].src = clients + c;
    graph->edge[roads + c].dest = clients + c + 1;
    graph->edge[roads + c].weight = 0;
    graph->edge[roads + c].id = -c - 69;   // Nice! (negative number)
  }

  // We implement Kruscal algoritm
  KruskalMST(graph, output_file);

  // Free allocs
  free(graph->edge);
  free(graph);

  // Free files
  fclose(input_file);
  fclose(output_file);

  // Exit correctly
  return 0;
}
