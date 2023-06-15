#include "lib.h"

int main() {
  // create a graph
  std::string original; std::cin >> original;
  int numNodes, k; std::cin >> numNodes >> k;
  Graph graph(numNodes, k);

  // add all nodes to the graph
  graph.addAllNodes();
  graph.addArcs();
  graph.print();
  graph.breakCycles();
  graph.print();

  // find the longest path
  string longestPath = graph.longestPath();
  std::cout << "Original: " << original << std::endl;
  std::cout << "Longest path: " << longestPath << std::endl;


  // show the accuracy
  // std::cout << "Accuracy: " << accuracyPercentage(original, longestPath) << "%" << std::endl;

  return 0;
}