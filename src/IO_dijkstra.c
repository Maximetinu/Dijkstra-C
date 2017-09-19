//
// Created by metinu on 9/18/17.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/IO_dijkstra.h"

void input_nodes(struct Dijkstra_input *input);

struct Dijkstra_input input_by_terminal() {
    struct Dijkstra_input input;
    do {
        printf("Enter no. of vertices:");
        scanf("%d", &input.nodes);
    } while (input.nodes > NODES_MAX || input.nodes <= 1);


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

    input_nodes(&input);

    return input;
}

void print_dijkstra_ouput(struct Dijkstra_output *output) {
    printf("\nThe Dijkstra shortest path is: %d", output->path[0]);
    for (int i = 1; i < output->size; i++) {
        printf("-->%d", output->path[i]);
    }
    printf("\nPath total distance: %d", output->distance);
}

int input_from_file_nodes_by_keyboard(char *filename, struct Dijkstra_input *input) {
    int error_code;
    error_code = input_from_file(filename, &input);
    input_nodes(input);
    return error_code;
}

int input_from_file(char *filename, struct Dijkstra_input *input) {
    char buffer[FILE_MAX];
    char *record, *line;
    FILE *fstream;
    int i, j = 0;
    int columns = 0;
    bool columns_found = false;

    fstream = fopen(filename, "r");
    if (fstream == NULL) {
        printf("\nFile opening failed when reading input.");
        return -1;
    }


    while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL) {
        record = strtok(line, ";");
        while (record != NULL) {
            input->adjacency[i][j] = (record);
            j++;
            record = strtok(NULL, ";");
        }
        if (!columns_found) {
            columns = input->nodes = j;
            columns_found = true;
        } else if (j < columns)
            printf("\nLess columns than %d in %dª row, they will be treated as 0", columns, i + 1);
        else if (j > columns)
            printf("\nMore columns than %d in %dª row, the rest will be ignored", columns, i + 1);
        j = 0;
        ++i;
    }

    return 1;
}

void input_nodes(struct Dijkstra_input *input) {
    do {
        printf("\nEnter the starting node:");
        scanf("%d", &input->starting_node);
    } while (input->starting_node >= input->nodes || input->starting_node < 0);

    do {
        printf("\nEnter the target node:");
        scanf("%d", &input->target_node);
    } while (input->target_node >= input->nodes || input->target_node < 0 ||
             input->target_node == input->starting_node);
}

void print_dijkstra_input(struct Dijkstra_input *input) {
    printf("\nReaded adjacency matrix:");
    for (int i = 0; i < input->nodes; i++) {
        printf("\n");
        for (int j = 0; j < input->nodes; j++)
            printf("%d ", input->adjacency[i][j]);
    }
    printf("\n");
    printf("The shortest path to find is from node %d to node %d\n", input->starting_node, input->target_node);
}

int output_to_file(char *filename, struct Dijkstra_output *output) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    const char *text = "Shortest path calculated by Dijkstra: ";
    fprintf(f, "%s %d", text, output->path[0]);
    for (int i = 1; i < output->size; i++) {
        fprintf(f, "-->%d", output->path[i]);
    }
    fprintf(f, "\nTotal distance: %d", output->distance);

    fclose(f);
    return 1;
}