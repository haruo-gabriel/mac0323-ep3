#include "lib.h"

using namespace std;

int main() {
  // create a graph
  //string original; cin >> original;
  int numNodes, k; cin >> numNodes >> k;
  Graph graph(numNodes, k);

  // add all nodes to the graph
  graph.addAllNodes();
  graph.addArcs();
  graph.print();
  cout << "---------------------" << endl;
  cout << "After breaking cycles:" << endl  << endl;
  graph.breakCycles();
  graph.print();

  cout << "---------------------" << endl;
  // find the longest path
  string longestPath = graph.longestPath();
  //cout << left << setw(15) << "Original:" << left << setw(10) << original << endl;
  cout << left << setw(15) << "Longest path:" << left << setw(10) << longestPath << endl;

  // show the accuracy
  //cout << left << setw(15) << "Accuracy: "<< accuracyPercentage(original, longestPath) << "%" << endl;

  return 0;
}