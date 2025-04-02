// davidkitinberg@gmail.com


#include "UnionFind.h"
#include <stdexcept>

namespace ds {

// Constructor
UnionFind::UnionFind(int n) : size(n) {
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; ++i) {
        parent[i] = i;   // each element is its own parent initially
        rank[i] = 0;     // rank (tree height)
    }
}

// Destructor
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Find operation with path compression
int UnionFind::find(int u) {
    if (u < 0 || u >= size) {
        throw std::out_of_range("Index out of range in find()");
    }

    // If we did not find the root, recursively find the root and compress the path
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void UnionFind::unite(int u, int v) {
    int rootU = find(u); // Find root of u
    int rootV = find(v); // Find root of v

    if (rootU == rootV) return; // If already in same connected component dont unite

    // Union by rank
    if (rank[rootU] < rank[rootV]) // If u's tree is smaller (rank)
    {
        parent[rootU] = rootV; // Connect u's connected component to v's connected component
    } 
    else if (rank[rootU] > rank[rootV]) // If v's tree is smaller (rank)
    {
        parent[rootV] = rootU; // Connect v's connected component to u's connected component
    } 
    else // If ranks are equal, we choose one as root and increase its rank
    {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

// Check whether two elements are in the same connected component
bool UnionFind::connected(int u, int v) {
    return find(u) == find(v);
}

}