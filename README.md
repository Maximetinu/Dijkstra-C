# Dijkstra C
Dijkstra algorithm implementation in C. Provides the possibility of reading the adjacency matrix from file input, and generate another file as output; or reading and printing via terminal.

[Algorithm description](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm).
## Current features
- Dijkstra shortest path algorithm implementarion, through an adjacency graph, directed or bidirectional.
- Supports both input and ouput via terminal and files.
- Supports CSV files representing the adjacency graph input. Don't be shy and use spreadsheets to create huges graphs!
- Supports drawing computed shortest path as output.
- Supports differents usages, one of them non verbosing, ideal for repeating program execution in a set of files.
- Applies segregations of concerns, separating logic from algorithm and from input/output through 3 main public interfaces:
    - `dijkstra.h`, responsible of algorithm calculation. Completely reusable.
    - `IO_dijkstra.h`, utilities for reading algorithm input via keyboard and printing output to terminal or files
    - `graph_drawer.h`, not a drawer actually, but has the responsability of calling the actual graph drawer, [graphviz](http://www.graphviz.org/).
## Graph output example
![Graph shortest path example](https://raw.githubusercontent.com/Maximetinu/Dijkstra-C/master/example_io_files/example_solution.png "Logo Title Text 1")
## Compiling
Create folders structure with `make folders`. Compiling and linking with `make`.
## Usages
    ./program                                                 // input and output by terminal
    ./program <input_csv_filename>                            // output by terminal
    ./program <input_csv_filename> <output_filename>          // starting and target node input by terminal
    
    // Non verbose execution
    ./program <input_csv_filename> <output_filename> <starting_node> <target_node
## Credits
Proghetto per il corso Fondamenti di Informatica, Università Degli Studi di Firenze. Unlicensed.
