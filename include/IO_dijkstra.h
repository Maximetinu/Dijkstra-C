//
// Created by metinu on 9/18/17.
//

#ifndef DIJKSTRA_IO_DIJKSTRA_H
#define DIJKSTRA_IO_DIJKSTRA_H

#include "dijkstra.h"

struct Dijkstra_input input_by_terminal(); // takes the input by keyboard using scanf
void print_dijkstra_ouput(struct Dijkstra_output *output); // prints the input in terminal using printf
void print_dijkstra_input(struct Dijkstra_input *input);

int output_to_file(char *filename, struct Dijkstra_output *output);

int input_from_file(char *filename, struct Dijkstra_input *input);

int input_from_file_nodes_by_keyboard(char *filename, struct Dijkstra_input *input);

#endif //DIJKSTRA_IO_DIJKSTRA_H
