#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits.h>

using namespace std;

// Node class
class Node {
public:
  int id;
  string sequence;
  vector<pair<Node*, int>> arcs; // vector of arcs (node pointer, weight)
  // vector<Node*> arcs;

  Node(int nodeId, const string& nodeSequence) {
    id = nodeId;
    sequence = nodeSequence;
    arcs = vector<pair<Node*, int>>();
    //arcs = vector<Node*>();
  }

};

// Directed graph class
class Graph {
private:
public:
  vector<Node> nodes;
  int numNodes;
  int k;

  Graph(int numNodes, int k)
  {
    this->numNodes = numNodes;
    this->k = k;
  }

  void addAllNodes()
  {
    for (int i=0; i<numNodes; i++) {
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
      int weight = lengthSequence;
      x.arcs.push_back(make_pair(&y, weight));
      //x.arcs.push_back(&y);
    }
  }

  int commonSequence(const Node& x, const Node& y, int k)
  {
    int xSize = x.sequence.length();
    int ySize = y.sequence.length();
    int minSize = min(xSize, ySize);
    int cont = 0;

    for (int i=1; i<=minSize; i++) {
      string xEnd = x.sequence.substr(xSize - i);
      string yStart = y.sequence.substr(0, i);
      if (xEnd == yStart)
        cont = i;
    }
    return cont;
  }

  void print()
  {
    for (const auto& it : nodes) {
      std::cout << it.id << ": " << it.sequence << std::endl;
      std::cout << "Arcs: " << std::endl;
      for (const auto& it2 : it.arcs) {
         std::cout << "(" << it2.first->sequence << " , " << it2.second << ")" << std::endl;
        //std::cout << it2->sequence << std::endl;
      }
      std::cout << std::endl;
    }
  }

  void breakCycles()
  {
    vector<bool> begin(numNodes, false);
    vector<bool> end(numNodes, false);
    int time = 0;
    for (auto& node : nodes) {
      if (!begin[node.id])
        breakCyclesHelper(node, begin, end, time);
    }
  }
  void breakCyclesHelper(Node& node, vector<bool>& begin, vector<bool>& end, int& time)
  {
    time++;
    // dfs
    begin[node.id] = true;
    auto neighbour = node.arcs.begin();
    while (neighbour != node.arcs.end()) {
      if (!begin[(*neighbour).first->id]) {
        breakCyclesHelper(*(*neighbour).first, begin, end, time);
        neighbour++;
      }
      else if (!end[(*neighbour).first->id]) {
        neighbour = node.arcs.erase(neighbour);
      }
      else {
        neighbour++;
      }
    }
    end[node.id] = true;
  }

  vector<Node*> getFonts()
  {
    vector<int> countInDegree(numNodes, 0);
    for (int i=0; i<numNodes; i++) {
      for (auto& neighbour : nodes[i].arcs) {
        countInDegree[neighbour.first->id]++;
      }
    }
    vector<Node*> fonts;
    for (int i=0; i<numNodes; i++) {
      if (countInDegree[i] == 0)
        fonts.push_back(&nodes[i]);
    }
    return fonts;
  }

  string longestPath()
  {
    vector<Node*> fonts = getFonts();
    int longestSize = 0;
    vector<int> dist(numNodes), prev(numNodes), prevLongest(numNodes, -1);
    int pathSize;
    for (auto& font : fonts) {
      fill(dist.begin(), dist.end(), INT_MIN);
      fill(prev.begin(), prev.end(), -1);
      dist[font->id] = 0;
      prev[font->id] = -1;
      pathSize = longestPathHelper(font, dist, prev);
      // verifies if the new path is longer than the present one
      if (dist[pathSize] > longestSize) {
        longestSize = dist[pathSize];
        // make a copy of prev to prevLongest
        for (int i=0; i<numNodes; i++)
          prevLongest[i] = prev[i];
      }
    }

    // build the longest path string using the prev vector
    int currId = pathSize;
    string longestPath = "";
    vector<int> longestPathIds;
    while (currId != -1) {
      longestPathIds.insert(longestPathIds.begin(), currId);
      currId = prevLongest[currId];
    }
    // print the longest path nodes
    // for (int it : longestPathIds) {
    //   cout << it << " ";
    //   cout << nodes[it].sequence << " ";
    // }
    // cout << endl;

    if (longestPathIds.size() > 0) {
      longestPath = nodes[longestPathIds[0]].sequence;
      // cout << longestPath << endl;
      for (unsigned int i=1; i<longestPathIds.size(); i++) {
        longestPath = longestPath + uniteSequences(longestPath, nodes[longestPathIds[i]].sequence);
        //cout << longestPath << endl;
      }
    }

    return longestPath;
  }
  int longestPathHelper(Node* font, vector<int>& dist, vector<int>& prev)
  {
    // bfs to find the longest path
    queue<int> queue;
    queue.push(font->id);
    int u;
    while (!queue.empty()) {
      u = queue.front(); queue.pop();
      // pass through the adjacents
      for (auto& neighbour : nodes[u].arcs) {
        int v = neighbour.first->id;
        if (dist[u] >= dist[v]) {
          prev[v] = u;
          dist[v] = dist[u] + 1;
          queue.push(v);
        }
      }
    }
    return u; // returns the index of the last node of the longest path
  }
  string uniteSequences(string back, string front)
  {
    int backSize = back.length();
    int frontSize = front.length();
    int minSize = min(backSize, frontSize);
    int cont = 0, i = this->k;
    for (; i<=minSize; i++) {
      string backEnd = back.substr(backSize - i);
      string frontStart = front.substr(0, i);
      if (backEnd == frontStart)
        cont = i;
    }
    return front.substr(cont);
  }
};

double accuracyPercentage(const string& original, const string& longestPath)
{
  int originalSize = original.length();
  int longestPathSize = longestPath.length();
  int cont = 0; // counts the number of wrong characters
  int i = 0, j = 0;
  while (i<originalSize && j<longestPathSize) {
    if (original[i] != longestPath[j]) {
      cont++; j++;
    }
    else {
      i++; j++;
    }
  }
  return (1 - (double)cont / (double)originalSize) * 100;
}
