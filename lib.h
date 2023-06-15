#include <utility>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Node class
class Node {
public:
  int id;
  string sequence;
  //vector<pair<Node*, int>> arcs; // vector of arcs (node pointer, weight)
  vector<Node*> arcs;

  Node(int nodeId, const string& nodeSequence) {
    id = nodeId;
    sequence = nodeSequence;
    //arcs = vector<pair<Node*, int>>();
    arcs = vector<Node*>();
  }

};

// Directed graph class
class Graph {
public:
  vector<Node> nodes;
  int numNodes;
  int k; // k-mer length

  Graph(int numNodes, int k)
  {
    this->numNodes = numNodes;
    this->k = k;
  }

  void addAllNodes()
  {
    for (int i = 0; i < numNodes; i++) {
      string seq; cin >> seq;
      Node node = Node(i, seq);
      nodes.push_back(node);
    }
  }

  void addArcs()
  {
    for (auto& it : nodes) {
      for (auto& it2 : nodes) {
        if (&it != &it2) addArc(it, it2);
      }
    }
  }
  
  // Add an arc from x to y if the common sequence between x and y is at least k
  void addArc(Node& x, Node& y)
  {
    int lengthSequence = commonSequence(x, y, k);
    if (lengthSequence >= k) {
      //int weight = lengthSequence;
      //x.arcs.push_back(make_pair(&y, weight));
      x.arcs.push_back(&y);
    }
  }

  int commonSequence(const Node& x, const Node& y, int k)
  {
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

  void print()
  {
    for (const auto& it : nodes) {
      std::cout << it.id << ": " << it.sequence << std::endl;
      std::cout << "Arcs: " << std::endl;
      for (const auto& it2 : it.arcs) {
        // std::cout << "(" << it2.first->sequence << " , " << it2.second << ")" << std::endl;
        std::cout << it2->sequence << std::endl;
      }
      std::cout << std::endl << std::endl;
    }
  }

  void breakCycles()
  {
    unordered_map<Node*,int> beginTimes;
    unordered_map<Node*,int> endTimes;
    int time = 0;
    // initialize begin and end times
    for (int i=0; i<numNodes; i++) {
      beginTimes[&nodes[i]] = -1;
      endTimes[&nodes[i]] = -1;
    }

    for (auto& node : nodes) {
      if (beginTimes[&node] == -1) {
        dfsR(node, beginTimes, endTimes, time);
      }
    }
  }
  void dfsR(Node& node, unordered_map<Node*,int>& beginTimes, unordered_map<Node*,int>& endTimes, int& time)
  {
    beginTimes[&node] = time++; // begin time
    for (auto& neighbour : node.arcs) {
      if (beginTimes[neighbour] == -1) {
        dfsR(*neighbour, beginTimes, endTimes, time);
      }
      // checks if it is a returning arc
      else if (endTimes[neighbour] == -1) {
        // remove the arc
        auto it = find(node.arcs.begin(), node.arcs.end(), neighbour);
        if (it != node.arcs.end())
          node.arcs.erase(it);
      }
    }
    endTimes[&node] = time++; // end time
  }

  vector<Node*> topologicalSort()
  {

  }

  string longestPath()
  {

  }

};

// TODO - implement this function
double accuracyPercentage (const string& original, const string& longestPath)
{
  int originalSize = original.length();
  int longestPathSize = longestPath.length();
  int cont = 0;

  for (int i = 0; i < originalSize; i++)
    if (original[i] == longestPath[i]) cont++;

  return 100 * (double)cont / longestPathSize;
}