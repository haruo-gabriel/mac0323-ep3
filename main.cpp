#include "lib.h"

int main() {
  // create a graph
  int numNodes, k;
  cin >> numNodes >> k;
  Graph graph(numNodes, k);

  // add all nodes to the graph
  graph.addAllNodes();
  graph.addArcs();
  graph.print();
  return 0;
}