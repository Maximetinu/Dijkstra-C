//
// Created by metinu on 9/18/17.
//
#include "../include/dijkstra.h"
#include <stdbool.h>

#define INFINITY 9999



struct Dijkstra_output dijkstra(struct Dijkstra_input *input) {

    int costs[NODES_MAX][NODES_MAX];
    int distances_to_source[NODES_MAX];
    int predecessors[NODES_MAX];
    bool visited[NODES_MAX];
    int count;
    int min_distance;
    int next_node;

    // costs[] stores the distances from node i to node j
    // distances_to_source[i] stores the distances of predecessors[i] to the source node
    // predecessors[] stores the predecessor of each node upon completed the dijkstra path
    // visited[i] stores if the node [i] has been already visited for the algorithm
    // count stores the number of nodes seen so far
    // min_distance will store the minimum distance from the source already found for the current path

    // create the cost matrix from the adjacency matrix, setting reflective costs to infinity to avoid choose them
    for (int i = 0; i < input->nodes; i++)
        for (int j = 0; j < input->nodes; j++)
            if (input->adjacency[i][j] == 0)
                costs[i][j] = INFINITY;
            else
                costs[i][j] = input->adjacency[i][j];

    // initializing predecessors[] to starting node, distances_to_source[i] to cost between i and start and visited[] to false
    for (int i = 0; i < input->nodes; i++) {
        distances_to_source[i] = costs[input->starting_node][i];
        predecessors[i] = input->starting_node;
        visited[i] = false;
    }

    // initializing the source as already visited and distance to himself to zero
    distances_to_source[input->starting_node] = 0;
    visited[input->starting_node] = true;
    count = 1;

    // for each possible neighbour
    while (count < input->nodes - 1) {
        min_distance = INFINITY;

        // looping neighbours nodes except the already visited
        for (int i = 0; i < input->nodes; i++)
            if (distances_to_source[i] < min_distance && !visited[i]) {
                min_distance = distances_to_source[i];
                next_node = i;
            }

        // setting next_node as already visited
        visited[next_node] = true;

        // choosing next_node by checking the one with minimum distance to source
        for (int i = 0; i < input->nodes; i++)
            if (!visited[i])
                if (min_distance + costs[next_node][i] < distances_to_source[i]) {
                    distances_to_source[i] = min_distance + costs[next_node][i];
                    predecessors[i] = next_node;
                }
        count++;
    }

    // building shortest_path in solution struct
    struct Dijkstra_output solution;

    solution.distance = distances_to_source[input->target_node];
    solution.path[0] = input->target_node;
    solution.size = 1;

    // filling path with predecessors
    for (int i = input->target_node; i != input->starting_node; solution.size++, i = predecessors[i])
        solution.path[solution.size] = predecessors[i];

    // reverting path (predecessors) to make a path from source(0) to target(size - 1)
    for (int temp, end = solution.size - 1, i = 0; i < input->nodes / 2; i++) {
        temp = solution.path[i];
        solution.path[i] = solution.path[end];
        solution.path[end] = temp;
        end--;
    }

    // returning shortest_path calculated with Dijkstra algorithm as Path struct
    return solution;
}