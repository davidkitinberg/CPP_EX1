// davidkitinberg@gmail.com


#include "UnionFind.h"
#include <stdexcept>

namespace ds {

UnionFind::UnionFind(int n) : size(n) {
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; ++i) {
        parent[i] = i;   // each element is its own parent initially
        rank[i] = 0;     // rank (tree height estimate)
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int u) {
    if (u < 0 || u >= size) {
        throw std::out_of_range("Index out of range in find()");
    }

    // Path compression
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void UnionFind::unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV) return; // Already in same set

    // Union by rank
    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

bool UnionFind::connected(int u, int v) {
    return find(u) == find(v);
}

}