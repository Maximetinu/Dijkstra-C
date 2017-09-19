//
// Created by metinu on 9/18/17.
//

#ifndef DIJKSTRA_DIJKSTRA_H
#define DIJKSTRA_DIJKSTRA_H
#define NODES_MAX 10
#define FILE_MAX 8192
// struct descripting a path, wich will be the shortest path calculated by Dijkstra
struct Dijkstra_output {
    int distance;
    int path[NODES_MAX];
    int size;
};

// algorithm input
struct Dijkstra_input {
    int adjacency[NODES_MAX][NODES_MAX];
    int nodes;
    int starting_node;
    int target_node;
};

struct Dijkstra_output dijkstra(struct Dijkstra_input *input);

#endif //DIJKSTRA_DIJKSTRA_H
