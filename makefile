# davidkitinberg@gmail.com


# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
VALGRIND = valgrind --leak-check=full

# Directories
SRC_DIR = Algorithms/src
DS_DIR = DataStructures
GRAPH_DIR = Graph

# Files
OBJECTS = \
    $(SRC_DIR)/BFS.cpp \
    $(SRC_DIR)/DFS.cpp \
    $(SRC_DIR)/Dijkstra.cpp \
    $(SRC_DIR)/Kruskal.cpp \
	$(SRC_DIR)/Prim.cpp \
    $(DS_DIR)/Queue.cpp \
    $(DS_DIR)/PriorityQueue.cpp \
    $(DS_DIR)/UnionFind.cpp \
    $(GRAPH_DIR)/Graph.cpp

# Default target
all: Main

# 1. Build and run main demo
Main: Main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main Main.cpp $(OBJECTS)
	./main

# 2. Run all tests
test: Test_main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test_all Test_main.cpp $(OBJECTS)
	./test_all

# 3. Run valgrind memory leak test on main
valgrind: Main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main Main.cpp $(OBJECTS)
	$(VALGRIND) ./main

# 4. Clean all generated files
clean:
	rm -f main test_all
