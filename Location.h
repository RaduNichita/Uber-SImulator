// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE
#ifndef LOCATION_H_
#define LOCATION_H_
#include <string>
#include <list>
class Location {
 private:
  int id;
  int drivers_available;
  std::list < Driver> drivers;

 public:
  std::string name;
  Location();
  Location(int &id, std::string &name);
  inline void addDriver(const Driver &new_driver);
  inline void removeDriver(std::string &driver_name);
  inline int getAvailableDrivers();
  inline bool DriverOnline();
  inline Driver getBest();
};

  Location::Location() { }
  Location::Location(int &id, std::string &name) {
    this->id = id;
    this->name = name;
    drivers_available = 0;
  }
  inline void Location::addDriver(const Driver &new_driver) {
    drivers.emplace_back(new_driver);
    drivers_available++;
  }
  inline void Location::removeDriver(std::string &driver_name) {
    for (auto it = drivers.begin(); it != drivers.end(); it++) {
      if (it -> name == driver_name) {
        it = drivers.erase(it);
        drivers_available--;
        return;
      }
    }
  }
  inline int Location::getAvailableDrivers() {
    return this -> drivers_available;
  }
  inline bool Location::DriverOnline() {
    for (auto it = drivers.begin(); it != drivers.end(); it++){
        if (it->status == 1) {
          return true;
        }
      }
      return false;
  }
  inline Driver Location::getBest() {
    if (drivers_available <= 0) {
      return Driver();
    } else if (drivers_available == 1) {
      return drivers.front();
    } else {
      Driver top_driver = drivers.front();
      for (auto it = drivers.begin(); it != drivers.end(); it++){
        if (top_driver < *it) {
          top_driver = *it;
        }
      }
      return top_driver;
    }
  }

#endif  // LOCATION_H_
