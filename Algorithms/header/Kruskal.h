// davidkitinberg@gmail.com

#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../Graph/Graph.h"

namespace algo {

class Kruskal {
public:
    static graph::Graph buildMST(const graph::Graph& g);
};

} // namespace algo

#endif // KRUSKAL_H
