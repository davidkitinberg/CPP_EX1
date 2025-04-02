# Graph Algorithms Project in C++

In this project we are asked to make an Implementation of classic graph algorithms using custom data structures — fully STL-free. The project is run only in C++ and in linux environment.

---

## Project Structure

```
.
├── Algorithms/
│   ├── header/                
│   └── src/                  
├── DataStructures/            
├── Graph/                    
├── doctest.h                 
├── Main.cpp                  
├── Test_main.cpp             
├── makefile                  
└── README.md                 
```
In this project I divided the classes into different directories to keep organizable and modular project.

-   ***Algorithms/*** - Divided into two subdirectories:
        
    **Algorithms/header/ :** Contains the header files for each graph algorithm (`BFS.h`, `DFS.h`, `Dijkstra.h`, `Kruskal.h`, `Prim.h`), declaring the static interfaces for the algorithms.

    **Algorithms/src/ :** Contains the corresponding source files that implement each algorithm. Each file defines how the algorithm processes a graph and returns the modified graph after the algorithms.
-   ***DataStructures/*** - Contains the custom-built data structures that are used internally by the algorithms
-   ***Graph/*** - Contains the core Graph class implementation (`Graph.h`, `Graph.cpp`).

---

## Features

-  **Graph** representation using adjacency lists (array with linked-lists)
-  **BFS (Breadth-First Search)** — builds a shortest-path tree
-  **DFS (Depth-First Search)** — builds a depth-first tree
-  **Dijkstra’s Algorithm** — computes shortest path tree from a source
-  **Prim’s Algorithm** — builds a minimum spanning tree (MST)
-  **Kruskal’s Algorithm** — builds an MST using union-find
-  **Custom Data Structures**  
  - `Queue` — for BFS
  - `PriorityQueue` — for Dijkstra and Prim
  - `UnionFind` — for Kruskal
-  **Comprehensive Unit Tests** using [doctest](https://github.com/doctest/doctest)
-  **Memory-leak free** (compatible with Valgrind)

---

## Build Instructions

You can build and run the project using the included `makefile`.

### 1. Build and run demo (`Main.cpp`)
```
make Main
```

### 2. Run unit tests
```
make test
```

### 3. Run demo with Valgrind (memory leak check)
```
make valgrind
```

### 4. Clean up build artifacts
```
make clean
```

---

## Testing

- All test cases live in `Test_main.cpp`
- Tests include:
  - Graph edge creation
  - BFS, DFS tree validation
  - MST validation for Prim and Kruskal
  - Dijkstra distance validation
  - Custom queue and priority queue logic
  - Union-find functinality
- Uses `doctest.h` (no external installation required)

---

## Notes

- STL (like `vector`, `set`, `map`) is **not used**
-   The project uses 3 namespaces: `algo`, `ds`, `graph`:

    `algo` - Contains all the graph algorithms in this project 

    `ds` (short for data structures) - Contains all the costum data structures that were used in this project (e.g Queue,PriorityQueue,Union-Find)
    
    `graph` - Contains the Graph class and it's functions
- Project uses **manual memory management**
- Edges are added to **both ends** in the adjacency list (undirected graph)
- All algorithms are implemented as **static classes** for conveniet usage

---

##  Author

**David Kitinberg**  
-   For any questions about this project you are welcome to contact me through my email: davidkitinberg@gmail.com
