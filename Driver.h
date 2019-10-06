// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE
#ifndef DRIVER_H_
#define DRIVER_H_
#include <string>
class Driver {
 private:
  std::string name;
  std::string location;
  float rating;
  int total_rating;
  int total_distance;
  int total_rides;

 public:
  bool status;
  Driver();
  Driver(std::string name, std::string location);
  void turnOnline(std::string new_location);
  void turnOffline();
  std::string getName() const;
  inline std::string getLocation() const;
  inline int getDistance() const;
  inline double getRating() const;
  inline int getRides() const;
  inline bool getStatus() const;
  Driver operator=(const Driver& other);
  inline bool operator==(const std::string &driver_name);
  inline bool operator<(const Driver& other);
  inline bool operator> (const Driver& other);
  friend std::ostream& operator << (std::ostream &out, const Driver &driver);
  void change_position(std::string &new_location, int distance);
  void receive_rating(int newrating);
  Driver* operator*();
  friend class Location;
};
std::ostream& operator << (std::ostream &out, const Driver &driver) {
    out << std::fixed;
    out.precision(3);
    std::string real_status;
    if (driver.getStatus() == 1) {
      real_status = "online";
    } else {
      real_status = "offline";
    }
        out << driver.getName()<< ": ";
        out << driver.getLocation()<< " ";
        out << driver.getRating()<< " ";
        out << driver.getRides()<< " ";
        out << driver.getDistance()<< " ";
        out << real_status << "\n";
        return out;
    }

  Driver::Driver(std::string name, std::string location) {
    this -> name = name;
    this -> location = location;
    status = true;
    rating = 0.0;
    total_distance = 0;
    total_rides = 0;
    total_rating = 0;
  }

  Driver::Driver() { }
  void Driver::turnOnline(std::string new_location) {
    location = new_location;
    status = true;
  }
  void Driver::turnOffline() {
    status = false;
  }
  std::string Driver::getName() const {
    return this-> name;
  }
  inline std::string Driver::getLocation() const {
    return this->location;
  }
  inline int Driver::getDistance() const {
    return this->total_distance;
  }
  inline double Driver::getRating() const {
    return this->rating;
  }
  inline int Driver::getRides() const {
    return total_rides;
  }
  inline bool Driver::getStatus() const {
    return status;
  }
    Driver Driver::operator=(const Driver& other) {
    this->name = other.name;
    this->location = other.location;
    status = other.status;
    rating = other.rating;
    total_distance = other.total_distance;
    total_rides = other.total_rides;
    total_rating = other.total_rating;
    return *this;
  }
  inline bool Driver::operator==(const std::string &driver_name) {
    return (this->name.compare(driver_name) == 0);
  }
  inline bool Driver::operator<(const Driver& other) {
    if (this -> rating < other.rating) {
      return 1;
    } else if (this-> rating > other.rating) {
      return 0;
    } else {
      if (this->name.compare(other.name) > 0) {
        return 1;
      } else {
        return 0;
      }
    }
  }
  inline bool Driver::operator> (const Driver& other) {
    if (this -> name.compare(other.name) > 0) {
      return 0;
    } else {
      return 1;
    }
  }
  void Driver::change_position(std::string &new_location, int distance) {
    total_distance += distance;
    location = new_location;
  }
  void Driver::receive_rating(int newrating) {
    this->total_rating+=newrating;
    total_rides += 1;
    rating  = (1.0 * total_rating) / total_rides;
  }
  Driver* Driver::operator*(){
    return this;
  }
#endif   //   DRIVER_H_
