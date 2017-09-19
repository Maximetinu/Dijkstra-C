# Dijkstra-C
Dijkstra algorithm implementation in C. Provides the possibility of reading the adjacency matrix from file input, and generate another file as output; or reading and printing via terminal.

[Algorithm description](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm).
### Compiling
Create folders structure with `make folders`. Compiling and linking with `make`.
### Usages
    ./program                                                 // input and output by terminal
    ./program <input_csv_filename>                            // output by terminal
    ./program <input_csv_filename> <output_filename>          // starting and target node input by terminal
    
    // Non verbose execution
    ./program <input_csv_filename> <output_filename> <starting_node> <target_node>
