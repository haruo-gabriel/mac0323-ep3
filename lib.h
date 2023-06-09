#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Node class
class Node {
public:
  int id;
  string sequence;
  int weight;
  vector<pair<Node*,int>> arcs; // vetor de arcos (nó, peso)

  Node(int nodeId, string nodeSequence) {
    id = nodeId;
    sequence = nodeSequence;
    weight = -1;
    arcs = vector<pair<Node*,int>>();
  }

  void addArc(Node* x) {
    int lengthSequence = commonSequence(this, x);
    if (commonSequence(this, x) > 0) {
      int weight = this->sequence.length() + x->sequence.length() - lengthSequence;
      arcs.push_back({x, weight});
    }
  }
  int commonSequence(Node* x, Node*  y) {
    int xSize = x->sequence.length();
    int ySize = y->sequence.length();
    int minSize = min(xSize, ySize);
    int cont = 0;

    for (int i = 1; i <= minSize; i++) {
      string xEnd = x->sequence.substr(xSize - i);
      string yStart = y->sequence.substr(0, i);
      if (xEnd == yStart) cont = i;
    }
    
    return cont;
  }
};

// Directed graph class
class Graph {
public:
  vector<Node*> nodes;
  int numNodes;
  int k; // k-mer length

  Graph(int numNodes, int k) : numNodes(numNodes), k(k) {}

  void addAllNodes() {
    for (int i = 0; i < numNodes; i++) {
      string seq; cin >> seq;
      Node* node = new Node(i, seq);
      nodes.push_back(node);
    }
  }

  void addArcs() {
    for (auto it : nodes) {
      for (auto it2 : nodes) {
        if (it != it2) it->addArc(it2);
      }
    }
  }

  void print() {
    for (auto it : nodes) {
      cout << it->id << ": " << it->sequence << endl;
      cout << "Arcs: ";
      for (auto it2 : it->arcs) {
        cout << "(" << it2.first->id << " , " << it2.second << ")" << endl;
      }
      cout << endl << endl;
    }
  }

};
