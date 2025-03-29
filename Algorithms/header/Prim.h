// davidkitinberg@gmail.com

#ifndef PRIM_H
#define PRIM_H

#include "../../Graph/Graph.h"

namespace algo {

class Prim {
public:
    static graph::Graph buildMST(const graph::Graph& g, int startVertex = 0);
};

} // namespace algo

#endif // PRIM_H
