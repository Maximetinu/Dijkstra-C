//
// Created by metinu - Miguel Medina Ballesteros - on September 2017. maximetinu@gmail.com
//
#include<stdio.h>
#include <stdbool.h>

#define INFINITY 9999
#define MAX 10

// struct descripting a path, wich will be the shortest path calculated by Dijkstra
struct Dijkstra_output {
    int distance;
    int path[MAX];
    int size;
};

// algorithm input
struct Dijkstra_input {
    int adjacency[MAX][MAX];
    int nodes;
    int starting_node;
    int target_node;
};

struct Dijkstra_output dijkstra(struct Dijkstra_input *input);
struct Dijkstra_input input_by_terminal(); // takes the input by keyboard using scanf
void print_dijkstra_ouput(struct Dijkstra_output *output); // prints the input in terminal using printf

int main() {
    struct Dijkstra_input input = input_by_terminal();
    struct Dijkstra_output shortest_path = dijkstra(&input);
    print_dijkstra_ouput(&shortest_path);

    return 0;
}

struct Dijkstra_output dijkstra(struct Dijkstra_input *input) {

    int costs[MAX][MAX];
    int distances_to_source[MAX];
    int predecessors[MAX];
    bool visited[MAX];
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
struct Dijkstra_input input_by_terminal() {
    struct Dijkstra_input input;
    do {
        printf("Enter no. of vertices:");
        scanf("%d", &input.nodes);
    } while (input.nodes > MAX || input.nodes <= 1);


    bool self_distance_valid = true;
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < input.nodes; i++)
        for (int j = 0; j < input.nodes; j++) {
            scanf("%d", &input.adjacency[i][j]);
            if (i == j && input.adjacency[i][j] != 0) {
                self_distance_valid = false;
                input.adjacency[i][j] = 0;
            }
        }

    if (!self_distance_valid) {
        printf("\nA distance between a node to himself is not zero.\nThe adjacency matrix has been corrected to: \n");
        for (int i = 0; i < input.nodes; i++) {
            printf("\n");
            for (int j = 0; j < input.nodes; j++)
                printf("%d ", input.adjacency[i][j]);
        }
        printf("\n");
    }

    do {
        printf("\nEnter the starting node:");
        scanf("%d", &input.starting_node);
    } while (input.starting_node > input.nodes || input.starting_node < 0);

    do {
        printf("\nEnter the target node:");
        scanf("%d", &input.target_node);
    } while (input.target_node >= input.nodes || input.target_node < 0 || input.target_node == input.starting_node);
    return input;
}
void print_dijkstra_ouput(struct Dijkstra_output *output) {
    printf("\nThe Dijkstra shortest path is: %d", output->path[0]);
    for (int i = 1; i < output->size; i++) {
        printf("-->%d", output->path[i]);
    }
    printf("\nPath total distance: %d", output->distance);
}

// TODO: if (args) input_by_file(filename)
// TODO: print_dijkstra_input - for checking the file reading
// TODO: text_output_to_file(filename)
// TODO: graphic_output_to_[window][plotting graph][image]
// TODO: separate files between .h and .c

