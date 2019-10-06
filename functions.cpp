// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <queue>
#include <vector>
#include <stack>
#include "./functions.h"
inline Driver determine_closest_new(Graph<std::string> &map,
      std::string departure, std::vector<Location * > &locations,
                                                      int &distance) {
  Driver top_driver;
  distance = -1;
  const int size = locations.size();
  std::queue<int> myqueue;
  std::vector<int> dist(size);
  std::vector<bool> visited(size, false);
  int src = map.Graph_Hashtable->getValue(departure);
  if (locations[src]->getAvailableDrivers()) {
    top_driver = locations[src]->getBest();
    distance = 0;
    return top_driver;
  }
  dist[src] = 0;
  myqueue.emplace(src);
  visited[src] = 1;
  while (!myqueue.empty()) {
    int x = myqueue.front();
    myqueue.pop();
    auto mylist = map.getClosestNeighbors(x);
  for (auto it = mylist.begin(); it != mylist.end(); ++it) {
    if (visited[*it] == 0) {
        visited[*it] = 1;
        dist[*it] = dist[x] + 1;
        myqueue.push(*it);
        if (locations[*it]->getAvailableDrivers()) {
          if (distance == -1) {
            distance = dist[*it];
            distance = dist[*it];
            top_driver = locations[*it]->getBest();
          } else if (dist[*it] == distance &&
                      top_driver < locations[*it]->getBest()) {
            top_driver = locations[*it]->getBest();
          } else if (dist[*it] > distance && distance != -1) {
            return top_driver;
          }
        }
      }
    }
  }
  if (distance == -1) {
    return Driver("Target Unreachable", "0");
  } else {
    return top_driver;
  }
}


template <typename T>
void swap(T &a, T &b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}
template <typename T>
int partition(std::vector<T> &v, int &low, int &high, int (&comp)(T &, T &)) {
    T pivot = v[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (comp(v[j], pivot) < 0)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}
template <typename T>
void iterativeqsort(std::vector<T> &v, int (*comp)(T &, T &)) {
  int low = 0;
  int high = v.size() -1;
  std::stack <std::pair<int, int> > local_stack;
  local_stack.push(std::make_pair(low, high));
  while (!local_stack.empty()) {
    low = local_stack.top().first;
    high = local_stack.top().second;
    local_stack.pop();
    int pivot = partition(v, low, high, comp);
    if (pivot - 1 > low) {
      local_stack.push(std::make_pair(low, pivot - 1));
    }
    if (pivot + 1 < high) {
      local_stack.push(std::make_pair(pivot + 1, high));
    }
  }
}
inline void print_distance(std::vector<Driver> &v,
                              size_t size, std::ofstream& fout) {
    size_t min;
  if (size < v.size()) {
    min = size;
  } else {
    min = v.size();
  }
    for (size_t i = 0; i < min; ++i) {
      fout << v[i].getName() << ":" << v[i].getDistance() << " ";
    }
}
inline void top_dist(std::vector<Driver> &v,
                            unsigned int size, std::ofstream& fout) {
  if (v.size() != 0) {
    SkipList<int, Driver> *leaderboard = new SkipList<int, Driver>;
    for (size_t i = 0; i <v.size(); i++) {
       SkipList_Node<int, Driver> *tmp;
        tmp = leaderboard ->searchElement(v[i].getDistance());
        if (tmp){
            tmp -> insert_sorted(v[i]);
        } else {
            SkipList_Node<int, Driver>*tmp =
                            leaderboard->insertElement(v[i].getDistance());
            tmp -> insert_sorted(v[i]);
        }
    }
    LinkedList <Driver> *mylist = leaderboard -> list_ordered_players();
     Node <Driver> *tmp = mylist -> refhead();
     int i = 0;
      while (tmp) {
          v[i++] = tmp->id;
          tmp = tmp->next;
         }
    delete mylist;
    delete leaderboard;
  print_distance(v, size, fout);
  }
  fout << "\n";
}

inline void top_rating(std::vector<Driver> &v,
                                  size_t size, std::ofstream& fout) {
  if (v.size() != 0) {
     SkipList<double, Driver> *leaderboard = new SkipList<double, Driver>;
    for (size_t i = 0; i <v.size(); i++) {
       SkipList_Node<double, Driver> *tmp;
        tmp = leaderboard ->searchElement(v[i].getRating());
        if (tmp){
            tmp -> insert_sorted(v[i]);
        } else {
            SkipList_Node<double, Driver>*tmp =
                            leaderboard->insertElement(v[i].getRating());
            tmp -> insert_sorted(v[i]);
        }
    }
    LinkedList <Driver> *mylist = leaderboard -> list_ordered_players();
     Node <Driver> *tmp = mylist -> refhead();
     int i = 0;
      while (tmp) {
          v[i++] = tmp->id;
          tmp = tmp->next;
         }
    delete mylist;
    delete leaderboard;
  size_t min;
  if (size < v.size()) {
    min = size;
  } else {
    min = v.size();
  }
    fout << std::fixed;
     fout.precision(3);
    for (size_t i = 0; i < min; ++i) {
      fout << v[i].getName() << ":" << v[i].getRating() << " ";
    }
  }
  fout << "\n";
}

void print_rides(std::vector<Driver> &v, size_t size, std::ofstream& fout) {
  size_t min;
  if (size < v.size()) {
    min = size;
  } else {
    min = v.size();
  }
    for (size_t i = 0; i < min; ++i) {
      fout << v[i].getName() <<  ":" << v[i].getRides() << " ";
    }
}

void top_rides(std::vector<Driver> &v, unsigned int size,
                                          std::ofstream& fout) {
  if (v.size() != 0) {
    SkipList<int, Driver> *leaderboard = new SkipList<int, Driver>;
    for (size_t i = 0; i <v.size(); i++) {
       SkipList_Node<int, Driver> *tmp;
        tmp = leaderboard ->searchElement(v[i].getRides());
        if (tmp){
            tmp -> insert_sorted(v[i]);
        } else {
            SkipList_Node<int, Driver>*tmp =
                            leaderboard->insertElement(v[i].getRides());
            tmp -> insert_sorted(v[i]);
        }
    }
    LinkedList <Driver> *mylist = leaderboard -> list_ordered_players();
     Node <Driver> *tmp = mylist -> refhead();
     int i = 0;
      while (tmp) {
          v[i++] = tmp->id;
          tmp = tmp->next;
         }
    delete mylist;
    delete leaderboard;
    print_rides(v, size, fout);
  }
  fout << "\n";
}

void print_rating(std::vector<Driver> &v, size_t size, std::ofstream& fout) {
  size_t min;
  if (size < v.size()) {
    min = size;
  } else {
    min = v.size();
  }
     fout << std::fixed;
     fout.precision(3);
    for (size_t i = 0; i < min; ++i) {
      fout << v[i].getName() <<  ":" << v[i].getRating() << " ";
    }
}
