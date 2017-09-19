//
// Created by metinu with <3 - Miguel Medina Ballesteros - on September 2017, in Granada. maximetinu@gmail.com
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/dijkstra.h"
#include "../include/IO_dijkstra.h"
#include "../include/graph_drawer.h"

int are_valid_nodes(int node_a, int node_b, int max);

/*
 * USAGES:
 *      ./program (input and output by terminal)
 *      ./program <input_csv_filename> (output by terminal)
 *      ./program <input_csv_filename> <output_filename> (starting and target node input by terminal, output to file and image)
 *      ./program <input_csv_filename> <output_filename> <starting_node> <target_node> (output to file and image)
 *
 *      Notes: please, omit output file extension. I will always be .txt for text and .png for picture
 *
 * REQUIREMENTS:
 *      In order to generate the graph image as output, this software uses the command 'dot', which is part of graphviz package.
 *      In case of not having graphviz installed, the image won't be generated.
 */

int main(int argc, char **argv) {
    struct Dijkstra_input input;

    int IO_success = 1;

    // INPUT
    argc--; // ignoring filename argument for more visual switch case...
    switch (argc) {
        case 1:
            IO_success = input_from_file_nodes_by_keyboard(argv[1], &input);
            break;
        case 2:
            IO_success = input_from_file_nodes_by_keyboard(argv[1], &input);
            break;
        case 4:
            IO_success = input_from_file(argv[1], &input);
            IO_success *= are_valid_nodes(atoi(argv[3]), atoi(argv[4]), input.nodes);
            input.starting_node = atoi(argv[3]);
            input.target_node = atoi(argv[4]);
            break;
        default:
            input = input_by_terminal();
    }

    if (!IO_success)
        return -1;

    struct Dijkstra_output output;
    output = dijkstra(&input);

    // OUTPUT
    switch (argc) {
        case 2:
            IO_success = output_to_file(argv[2], &output);
            break;
        case 4:
            IO_success = output_to_file(argv[2], &output);
            break;
        default:
            print_dijkstra_ouput(&output);
    }

    if (!IO_success)
        return -1;

    // GRAPHIC OUTPUT TO IMAGE
    if ((argc == 2 || argc == 4) && system("which dot") == 0) {
        draw_solution_to_image(&input, &output, argv[2]);
    } else if (system("which dot") == 256){
        printf("\nUnable to draw the graph path through \"dot\" command. Please, install the package graphviz.");
    }

    return 0;
}

int are_valid_nodes(int node_a, int node_b, int max) {
    int valid = 1;
    if (node_a < 0)
        valid = 0;
    if (node_a >= max)
        valid = 0;
    if (node_b < 0)
        valid = 0;
    if (node_b >= max)
        valid = 0;
    if (node_a == node_b)
        valid == 0;
    return valid;
}


// TODO: graphic_output_to_[window][plotting graph][image]
// --> TODO First: generate .dot file
// --> TODO Second: use library to get image from .dot file