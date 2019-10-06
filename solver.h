// Copyright 2019 NICHITA RADU 4.05.2019 TEMA 2 STRUCTURI DE DATE

#ifndef SOLVER_H_
#define SOLVER_H_
#define NMAX 200
#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include "./functions.h"

class solver {
 private:
    int stations;
    int connections;
    Graph <std::string > * Map_Graph;
    std::vector<Location * > Locations;
    std::vector<Driver> *mydriver;

 public:
    ~solver() {
      delete Map_Graph;
      delete mydriver;
      for (auto it = Locations.begin(); it != Locations.end(); it++) {
        delete (*it);
      }
      Locations.clear();
    }
    void initializations(std::ifstream& fin) {
      //   reads intersections and connections between them
      fin >> this->stations;
      fin >> this->connections;
      Map_Graph = new Graph <std::string> (stations);
      mydriver = new std::vector<Driver>;
       mydriver->reserve(NMAX);
       Locations.reserve(stations);
      for (int i = 0; i < stations; i++) {
        std::string current_location;
        fin >> current_location;
        Map_Graph -> insert(current_location, i);
        Locations.emplace_back(new Location(i, current_location));
      }
      for (int i = 0; i < connections; i++){
        std::string src;
        std::string dst;
        fin >> src >> dst;
        Map_Graph -> addEdge(src, dst);
      }
    }
    void task1_solver(std::ifstream& fin, std::ofstream& fout) {
      // check if there is a path between 2 intersections.
        this->initializations(fin);
      int queries;
      fin >> queries;
      for (int i = 0; i < queries; i++) {
        std::string src;
        std::string dst;
        fin >> src >> dst;
        if (Map_Graph->hasPath(src, dst) == 1) {
          fout << "y\n";
        } else {
          fout << "n\n";
        }
      }
    }
    void task2_solver(std::ifstream& fin, std::ofstream& fout) {
      // check the pathlength between 2 intersections
      int queries;
      fin >> queries;
      for (int i = 0; i < queries; i++) {
        std::string src;
        std::string dst;
        fin >> src >> dst;
        fout << Map_Graph->minPath(src, dst) << "\n";
      }
     }
    void task3_solver(std::ifstream& fin, std::ofstream& fout) {
      // check the pathlength between 2 intersection, via a midpoint
        char command;
        int queries;
        fin>> queries;
        for (int i = 0; i < queries; i++) {
          fin >> command;
          if (command == 'c') {
          std::string src;
          std::string dst;
          fin >> src >> dst;
          int direction;
          fin >> direction;
          switch (direction) {
            case 0:
              if (Map_Graph->hasEdge(src, dst) == 0) {
                Map_Graph->addEdge(src, dst);
              }
              break;
            case 1:
                Map_Graph->removeEdge(src, dst);
                Map_Graph->removeEdge(dst, src);
              break;
            case 2:
              if (Map_Graph->hasEdge(src, dst) == 0) {
                Map_Graph->addEdge(src, dst);
              }
              if (Map_Graph->hasEdge(dst, src) == 0) {
                Map_Graph->addEdge(dst, src);
              }
              break;
            case 3:
              if (Map_Graph->hasEdge(src, dst) == 1
                                  && Map_Graph->hasEdge(dst, src) == 0) {
                Map_Graph->removeEdge(src, dst);
                Map_Graph->addEdge(dst, src);
              } else if (Map_Graph->hasEdge(src, dst) == 0
                                  && Map_Graph->hasEdge(dst, src) == 1) {
                Map_Graph -> removeEdge(dst, src);
                Map_Graph->addEdge(src, dst);
              }
              break;
            }
          } else if (command == 'q') {
            std::string src;
            std::string dst;
            fin >> src >> dst;
            int direction;
            fin >> direction;
            switch (direction) {
              case 0:
                if (Map_Graph->hasPath(src, dst) == 1) {
                  fout << "y\n";
                } else {
                  fout << "n\n";
                }
                break;
              case 1:
                fout << Map_Graph->minPath(src, dst)<< "\n";
                break;
              case 2:
                std::string middlepoint;
                fin >> middlepoint;
                fout<<
                    Map_Graph->minPathmustVisit(src, dst, middlepoint) << "\n";
                break;
              }
          }
        }
     }
    void task4_solver(std::ifstream& fin, std::ofstream& fout) {
      int queries;
      bool ok = 1;   //  keep track of changes in "r command"
      bool change_rides = 0;
      bool change_rating = 0;
      bool change_distance = 0;
      fin >> queries;
      for (int i = 0; i< queries; ++i) {
        std::string command;
        std::string name;
        fin >> command;
        if (command == "d") {  //  turns a driver online
          bool is_new = true;
          std::string location;
          fin >> name >> location;
          for (auto it = mydriver->begin(); it != mydriver->end(); ++it) {
            if (it->getName() == name) {
              it -> turnOnline(location);
              Locations[Map_Graph->Graph_Hashtable->
                                getValuebyRef(location)]->addDriver(*it);
              is_new = false;
              break;
            }
          }
          if (is_new) {  //  adds new driver
            ok = 0;
            Driver new_driver(name, location);
            Locations[Map_Graph->
                    Graph_Hashtable->
                            getValuebyRef(location)]
                                        ->addDriver(new_driver);
            mydriver->emplace_back(new_driver);
          }
        }
        if (command == "b") {  //  turn a driver offline
          fin >> name;
          for (auto it = mydriver->begin(); it != mydriver->end(); ++it) {
            if (it->getName() == name) {
              it->turnOffline();
              Locations[Map_Graph->
                      Graph_Hashtable->
                              getValuebyRef
                                  (it->getLocation())]->removeDriver(name);
              break;
            }
          }
        }
        if (command == "r") {
          std::string start;
          std::string end;
          fin >> start >> end;
          int rating;
          fin >> rating;
          int distance;
          auto my_driver_name =
                    determine_closest_new
                                (*Map_Graph, start, Locations,
                                                distance);
          std::string driver_name = my_driver_name.getName();
          // take the best driver suitable for the ride
          if (driver_name == "Target Unreachable") {
            fout << "Soferi indisponibili\n";
          } else {
            for (auto it = mydriver->begin(); it != mydriver->end(); it++) {
              if (it-> getName() == driver_name) {
                std::string old_loc = it->getLocation();
                int old_dist = distance;
                Locations[Map_Graph->
                      Graph_Hashtable->
                          getValuebyRef(it->getLocation())]->
                                      removeDriver(driver_name);
                it->change_position(start, distance);
                distance = Map_Graph -> minPath(start, end);
                if (distance != -1) {
                  ok = 0;
                  it->change_position(end, distance);
                  it->receive_rating(rating);  //  update the stats
                  Locations[
                      Map_Graph->Graph_Hashtable
                                      ->getValuebyRef(end)]->addDriver(*it);
                } else {
                  std::list <int> mylist = Map_Graph->getNeighbors(end);
                  if (mylist.empty()) {
                    fout << "Destinatie inaccesibila\n";
                    Locations[Map_Graph->Graph_Hashtable->
                                  getValuebyRef(old_loc)]->addDriver(*it);
                    it->change_position(old_loc, -old_dist);

                  } else {
                    int first_neigh = -1;
                    for (auto it = mylist.begin(); it != mylist.end(); it++){
                      if (Map_Graph->hasPath(start, Locations[*it]->name) == 1)
                                                                             {
                        first_neigh = *it;
                        //  determine if there is any neighbour of destination
                        break;
                      }
                    }
                    if (first_neigh == -1) {
                      fout <<"Destinatie inaccesibila\n";
                      // if not ride is not made;
                      Locations[Map_Graph->Graph_Hashtable->
                                      getValuebyRef(old_loc)]->addDriver(*it);
                      it->change_position(old_loc, -old_dist);
                    } else {
                      // if yes, the stats are updated;
                      ok = 0;
                        distance = Map_Graph->
                                  minPath(start, Locations[first_neigh]->name);
                        it->change_position(Locations[first_neigh]->name,
                                                                  distance);
                        it->receive_rating(rating);
                        Locations[first_neigh]->addDriver(*it);
                    }
                  }
                }
                break;
              }
            }
          }
        }
        if (ok == 0) {
          change_distance = 0;
          change_rides = 0;
          change_rating = 0;
        }
        if (command == "top_dist") {
          //  print drivers, sorted by distance
          int number;
          fin >> number;
          static std::vector<Driver> v = *mydriver;
          if (change_distance == 1) {
            print_distance(v, number, fout);
            fout << "\n";
          } else {
            top_dist(*mydriver, number, fout);
            v = *mydriver;
            change_distance = 1;
          }
          ok = 1;
        }
        if (command == "top_rides") {
          //  print drivers, sorted by number of rides
          int number;
          fin >> number;
         static std::vector<Driver> v = *mydriver;
         if (change_rides == 1) {
          print_rides(v, number, fout);
          fout << "\n";
         } else {
          top_rides(*mydriver, number, fout);
          v = *mydriver;
          change_rides = 1;
         }
         ok = 1;
        }
        if (command == "top_rating") {
          // print  drivers, sorted by rating
          int number;
          fin >> number;
          static std::vector<Driver> v = *mydriver;
          if (change_rating == 1) {
           // std::cout<<i<<"este \n";
            print_rating(v, number, fout);
            fout<< "\n";
          } else {
            top_rating(*mydriver, number, fout);
            v = *mydriver;
            change_rating = 1;
          }
          ok = 1;
        }
        if (command == "info") {
          //  display information about a driver
          fin >> name;
          for (auto it = mydriver->begin(); it != mydriver->end(); ++it) {
            if (it->getName() == name) {
              fout << *it;
              break;
            }
          }
        }
      }
     }

    void task5_solver(std::ifstream& fin, std::ofstream& fout) {
       int fuel_left, stations;
       std::string driver_name;
       std::string driver_location;
       auto size = Locations.size();
      std::vector<bool> visited(size, false);
      std::vector<std::pair<std::string, int> > distances;
       fin >> fuel_left >> driver_name;
        for (auto it = mydriver->begin(); it != mydriver->end(); it++) {
          if (it->getName() == driver_name) {
              driver_location = it->getLocation();
              break;
          }
        }
       fin >> stations;
       for (int i = 0; i < stations; i++) {
        // for every intersection compute if there is enough fuel
          std::string current_location;
          fin >> current_location;
          int index = Map_Graph->Graph_Hashtable->getValue(current_location);
        if (visited[index] == 0) {
          visited[index] = 1;
          int current_distance = Map_Graph->
                          minPath(driver_location, current_location);
          if (current_distance != -1 && current_distance <=fuel_left) {
            distances.emplace_back(std::make_pair
                          (current_location, current_distance));
          }
        }
       }
       for (size_t i = 0; i < distances.size() -1; i++) {
         // Bubble sort to determine the closest intersections available
        for (size_t j = i; j < distances.size(); j++) {
          if (distances[i].second > distances[j].second) {
            auto tmp = distances[i];
            distances[i] = distances[j];
            distances[j] = tmp;
          } else if (distances[i].second == distances[j].second) {
            if (distances[i].first.compare(distances[j].first) > 0) {
               auto tmp = distances[i];
              distances[i] = distances[j];
              distances[j] = tmp;
            }
          }
        }
       }
       for (size_t i = 0; i < distances.size(); i++) {
        fout << distances[i].first << " ";
       }
    }
};

#endif  // SOLVER_H_
