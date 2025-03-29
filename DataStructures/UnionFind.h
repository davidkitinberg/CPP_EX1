// davidkitinberg@gmail.com


#ifndef UNION_FIND_H
#define UNION_FIND_H

namespace ds {

class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n);
    ~UnionFind();

    int find(int u);
    void unite(int u, int v);
    bool connected(int u, int v);
};

}

#endif
