#include<stdio.h>
#include <stdbool.h>

#define INFINITY 9999
#define MAX 10

struct Path dijkstra(int adjacency[MAX][MAX], int nodes, int starting_node, int target_node);

struct Path {
    int distance;
    int path[MAX];
    int size;
};

int main() {
    int adjacency[MAX][MAX];
    int nodes;
    int starting_node;
    int target_node;

    do {
        printf("Enter no. of vertices:");
        scanf("%d", &nodes);
    } while (nodes > MAX || nodes <= 1);


    bool self_distance_valid = true;
    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &adjacency[i][j]);
            if (i == j && adjacency[i][j] != 0) {
                self_distance_valid = false;
                adjacency[i][j] = 0;
            }
        }

    if (!self_distance_valid) {
        printf("\nA distance between a node to himself is not zero.\nThe adjacency matrix has been corrected to: \n");
        for (int i = 0; i < nodes; i++) {
            printf("\n");
            for (int j = 0; j < nodes; j++)
                printf("%d ", adjacency[i][j]);
        }
        printf("\n");
    }

    do {
        printf("\nEnter the starting node:");
        scanf("%d", &starting_node);
    } while (starting_node > nodes || starting_node < 0);

    do {
        printf("\nEnter the target node:");
        scanf("%d", &target_node);
    } while (target_node >= nodes || target_node < 0 || target_node == starting_node);

    struct Path shortest_path = dijkstra(adjacency, nodes, starting_node, target_node);

    printf("\nThe Dijkstra shortest path is: %d", shortest_path.path[0]);
    for (int i = 1; i < shortest_path.size; i++) {
        printf("-->%d", shortest_path.path[i]);
    }
    printf("\nPath total distance: %d", shortest_path.distance);

    return 0;
}

struct Path dijkstra(int adjacency[MAX][MAX], int nodes, int starting_node, int target_node) {

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
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            if (adjacency[i][j] == 0)
                costs[i][j] = INFINITY;
            else
                costs[i][j] = adjacency[i][j];

    // initializing predecessors[] to starting node, distances_to_source[i] to cost between i and start and visited[] to false
    for (int i = 0; i < nodes; i++) {
        distances_to_source[i] = costs[starting_node][i];
        predecessors[i] = starting_node;
        visited[i] = false;
    }

    // initializing the source as already visited and distance to himself to zero
    distances_to_source[starting_node] = 0;
    visited[starting_node] = true;
    count = 1;

    // for each possible neighbour
    while (count < nodes - 1) {
        min_distance = INFINITY;

        // looping neighbours nodes except the already visited
        for (int i = 0; i < nodes; i++)
            if (distances_to_source[i] < min_distance && !visited[i]) {
                min_distance = distances_to_source[i];
                next_node = i;
            }

        // setting next_node as already visited
        visited[next_node] = true;

        // choosing next_node by checking the one with minimum distance to source
        for (int i = 0; i < nodes; i++)
            if (!visited[i])
                if (min_distance + costs[next_node][i] < distances_to_source[i]) {
                    distances_to_source[i] = min_distance + costs[next_node][i];
                    predecessors[i] = next_node;
                }
        count++;
    }

    // building shortest_path in solution struct
    struct Path solution;

    solution.distance = distances_to_source[target_node];
    solution.path[0] = target_node;
    solution.size = 1;

    // filling path with predecessors
    for (int i = target_node; i != starting_node; solution.size++, i = predecessors[i])
        solution.path[solution.size] = predecessors[i];

    // reverting path (predecessors) to make a path from source(0) to target(size - 1)
    for (int temp, end = solution.size - 1, i = 0; i < nodes / 2; i++) {
        temp = solution.path[i];
        solution.path[i] = solution.path[end];
        solution.path[end] = temp;
        end--;
    }

    // returning shortest_path calculated with Dijkstra algorithm as Path struct
    return solution;
}
