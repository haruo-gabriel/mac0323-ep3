#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Node class
class Node {
public:
  int id;
  string sequence;
  vector<pair<Node*, int>> arcs; // vector of arcs (node pointer, weight)

  Node(int nodeId, const string& nodeSequence) {
    id = nodeId;
    sequence = nodeSequence;
    arcs = vector<pair<Node*, int>>();
  }

};

// Directed graph class
class Graph {
public:
  vector<Node> nodes;
  int numNodes;
  int k; // k-mer length

  Graph(int numNodes, int k) {
    this->numNodes = numNodes;
    this->k = k;
  }

  void addAllNodes() {
    for (int i = 0; i < numNodes; i++) {
      string seq; cin >> seq;
      Node node = Node(i, seq);
      nodes.push_back(node);
    }
  }

  void addArcs() {
    for (auto& it : nodes) {
      for (auto& it2 : nodes) {
        if (&it != &it2) addArc(it, it2);
      }
    }
  }
  
  void addArc(Node& x, Node& y) {
    int lengthSequence = commonSequence(x, y, k);
    if (lengthSequence >= k) {
      int weight = lengthSequence;
      x.arcs.push_back(make_pair(&y, weight)); // Store the pointer to the node
    }
  }

  int commonSequence(const Node& x, const Node& y, int k) {
    int xSize = x.sequence.length();
    int ySize = y.sequence.length();
    int minSize = min(xSize, ySize);
    int cont = 0;

    for (int i = 1; i <= minSize; i++) {
      string xEnd = x.sequence.substr(xSize - i);
      string yStart = y.sequence.substr(0, i);
      if (xEnd == yStart) {
        cont = i;
      }
    }
    return cont;
  }

  void print() {
    for (const auto& it : nodes) {
      cout << it.id << ": " << it.sequence << endl;
      cout << "Arcs: " << endl;
      for (const auto& it2 : it.arcs) {
        cout << "(" << it2.first->sequence << " , " << it2.second << ")" << endl;
      }
      cout << endl << endl;
    }
  }

};
