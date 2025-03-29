// davidkitinberg@gmail.com


#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <cstdlib>
#include "../../Graph/Graph.h"

namespace algo {

class DFS {
  public:
    static int* buildDFSTree(const Graph& g, int source);

   };

}

#endif 
