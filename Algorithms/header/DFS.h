// davidkitinberg@gmail.com


#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <cstdlib>
#include "../../Graph/Graph.h"

namespace algo {

class DFS {
  public:
        static graph::Graph buildDFSTree(const graph::Graph& g, int source);

   };

}

#endif 
