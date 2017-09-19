//
// Created by metinu - Miguel Medina Ballesteros - on September 2017. maximetinu@gmail.com
//
#include <stdlib.h>
#include "../include/dijkstra.h"
#include "../include/IO_dijkstra.h"

int is_valid_node(int node, int max);

/*
 * USAGES:
 *      ./program (input and output by terminal)
 *      ./program <input_csv_filename> (output by terminal)
 *      ./program <input_csv_filename> <output_filename> (starting and target node input by terminal)
 *      ./program <input_csv_filename> <output_filename> <starting_node> <target_node>
 */

int main(int argc, char **argv){
    struct Dijkstra_input input;

    int IO_success = 1;

    // INPUT
    argc--; // ignoring filename argument for more visual switch case...
    switch (argc){
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
    switch (argc){
        case 2:
            IO_success = output_to_file(argv[2],&output);
            break;
        case 4:
            IO_success = output_to_file(argv[2],&output);
            break;
        default:
            print_dijkstra_ouput(&output);
    }

    if (!IO_success)
        return -1;

    return 0;
}

int are_valid_nodes(int node_a, int node_b, int max){
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