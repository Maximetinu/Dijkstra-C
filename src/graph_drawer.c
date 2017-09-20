//
// Created by metinu on 9/19/17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/graph_drawer.h"

#define GRAPH_COMMAND_MAX 8096

int sucessors_in_solution(int i, int j, struct Dijkstra_output *output) {
    int i_follows_j = 0;
    int j_follows_i = 0;
    for (int k = 0; k < output->size - 1; k++)
        if (output->path[k] == i && output->path[k + 1] == j)
            j_follows_i = 1;
        else if (output->path[k] == j && output->path[k + 1] == i)
            i_follows_j = 1;

    return i_follows_j + j_follows_i;
}

// Building graph.dot based on echo "digraph G {Hello->World}" | dot -Tpng >hello.png
void draw_solution_to_image(struct Dijkstra_input *input, struct Dijkstra_output *output, char *filename_out) {
    //TODO: beautify this code
    char graph_command[GRAPH_COMMAND_MAX] = "echo \"digraph G {\n";
    int symmetric[input->nodes][input->nodes];
    for (int i = 0; i < input->nodes; i++)
        for (int j = 0; j < input->nodes; j++)
            if ((input->adjacency[i][j] == input->adjacency[j][i]) && i != j)
                symmetric[i][j] = symmetric[j][i] = 1;
            else
                symmetric[i][j] = symmetric[j][i] = 0;


    char str[4];
    for (int i = 0; i < input->nodes; i++)
        for (int j = 0; j < input->nodes; j++)
            if (input->adjacency[i][j] != 0) {
                if (symmetric[i][j] == 0) {
                    sprintf(str, "%d", i);
                    strcat(graph_command, str);
                    strcat(graph_command, "->");
                    sprintf(str, "%d", j);
                    strcat(graph_command, str);
                    if (sucessors_in_solution(i, j, output))
                        strcat(graph_command, " [color=red,penwidth=3.0,dir=both,label=\"");
                    else
                        strcat(graph_command, " [dir=both,label=\"");
                    sprintf(str, "%d", input->adjacency[i][j]);
                    strcat(graph_command, str);
                    strcat(graph_command, "\"]\n");
                } else if (symmetric[i][j] == 1) {
                    sprintf(str, "%d", i);
                    strcat(graph_command, str);
                    strcat(graph_command, "->");
                    sprintf(str, "%d", j);
                    strcat(graph_command, str);
                    if (sucessors_in_solution(i, j, output))
                        strcat(graph_command, " [color=red,penwidth=3.0,dir=both,label=\"");
                    else
                        strcat(graph_command, " [dir=both,label=\"");
                    sprintf(str, "%d", input->adjacency[i][j]);
                    strcat(graph_command, str);
                    strcat(graph_command, "\"]\n");
                    symmetric[j][i] = -1;
                }
            }

    sprintf(str, "%d", input->starting_node);
    strcat(graph_command, str);
    strcat(graph_command, "[xlabel=\"start\",shape=circle,style=filled,fillcolor=red]");

    sprintf(str, "%d", input->target_node);
    strcat(graph_command, str);
    strcat(graph_command, "[xlabel=\"target\",shape=circle,style=filled,fillcolor=red]");

    strcat(graph_command, "}\" | dot -Tpng >");
    strcat(graph_command, filename_out);
    strcat(graph_command, ".png");
    system(graph_command);
}
