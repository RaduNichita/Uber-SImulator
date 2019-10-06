// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE

#ifndef GRAPH_H_
#define GRAPH_H_
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>

int myhash(std::string s) {
    int sum = 0;
    for (size_t i = 0; i < s.length(); i++) {
      sum+=s[i];
    }
    return sum;
}

template <typename Tvalue >class Graph {
 private:
  std::vector<std::list <int> >nodes;
  std::vector<std::list<int> > neigh;
  int size;

 public:
  Hashtable < Tvalue, int > *Graph_Hashtable;
  explicit Graph(int size) {
    this -> size = size;
    Graph_Hashtable = new Hashtable <Tvalue, int>(size, &myhash);
    for (int i = 0; i < size; i++) {
      std::list <int> list;
      nodes.emplace_back(list);
      neigh.emplace_back(list);
    }
  }
  ~Graph() {
    delete Graph_Hashtable;
  }
  int getSize() const {
    return this->size;
  }
  void insert(Tvalue key, int value) {
    Graph_Hashtable -> insert(key, value);
  }
  void addEdge(Tvalue departure, Tvalue arrival) {
    int src = Graph_Hashtable->getValue(departure);
    int dst = Graph_Hashtable->getValue(arrival);
        nodes[src].emplace_back(dst);
        neigh[dst].emplace_back(src);
    }
    void removeEdge(Tvalue departure, Tvalue arrival) {
        int src = Graph_Hashtable->getValue(departure);
    int dst = Graph_Hashtable->getValue(arrival);
        for (auto it = nodes[src].begin(); it != nodes[src].end(); it++) {
            if ((*it) == dst) {
                it = nodes[src].erase(it);
                break;
            }
        }
        for (auto it = neigh[dst].begin(); it != neigh[dst].end(); it++) {
            if ((*it) == src) {
                it = neigh[dst].erase(it);
                return;
            }
        }
    }
    bool hasEdge(Tvalue departure, Tvalue arrival)  {
        int src = Graph_Hashtable->getValue(departure);
    int dst = Graph_Hashtable->getValue(arrival);
        for (auto it = nodes[src].begin(); it != nodes[src].end(); it++) {
            if ((*it) == dst) {
                return true;
            }
        }
        return false;
    }
    bool hasPath(Tvalue &departure, Tvalue &arrival) const {
      int src = Graph_Hashtable->getValue(departure);
    int dst = Graph_Hashtable->getValue(arrival);
    if (src == dst) {
      return true;
    }
    std::queue <int> findPath;
    std::vector<bool> visited(size, 0);
    findPath.push(src);
    visited[src] = 1;
    while (!findPath.empty()) {
      int current = findPath.front();
      findPath.pop();
      for (auto it = nodes[current].begin();
                                      it != nodes[current].end(); it++) {
        if (visited[*it] == 0) {
          findPath.push(*it);
          visited[*it] = 1;
        }
        if (*it == dst) {
          return true;
        }
      }
    }
    return false;
    }
    int  minPath(Tvalue &departure, Tvalue &arrival) const {
    int src = Graph_Hashtable->getValue(departure);
    int dst = Graph_Hashtable->getValue(arrival);
    if (src == dst) {
      return 0;
    }
    std::queue <int> findPath;
    std::vector<bool> visited(size, 0);
    std::vector<int> dist(size);
    findPath.push(src);
    dist[src] = 0;
    visited[src] = 1;
    while (!findPath.empty()) {
      int current = findPath.front();
      findPath.pop();
      for (auto it = nodes[current].begin();
                          it != nodes[current].end(); it++) {
        if (visited[*it] == 0) {
          findPath.push(*it);
          visited[*it] = 1;
          dist[*it] = dist[current] + 1;
        }
        if (*it == dst) {
          return dist[dst];
        }
      }
    }
    return -1;
    }
    std::list<int>& getNeighbors(Tvalue &location) {
      int closest_location = Graph_Hashtable->getValue(location);
        return nodes[closest_location];
    }
    std::list<int>& getClosestNeighbors(int closest_location) {
        return neigh[closest_location];
    }
    int minPathmustVisit(Tvalue departure, Tvalue arrival, Tvalue middlepoint) {
    int dist1 = this->minPath(departure, middlepoint);
    if (dist1 == -1) {
      return -1;
    }
    int dist2 = this->minPath(middlepoint, arrival);
    if (dist2 == -1) {
      return -1;
    }
    return dist1 + dist2;
    }
};

#endif  // GRAPH_H_
