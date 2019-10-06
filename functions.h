// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
	#include <iostream>
	#include <fstream>
	#include <utility>
	#include <vector>
	#include <string>
	#include "./Driver.h"
	#include "./Location.h"
	#include "./LinkedList.cpp"
	#include "./genericskip.cpp"
	#include "./Hashtable.h"
	#include "./Graph.h"
	#include "./functions.cpp"
inline Driver determine_closest_new(Graph<std::string> &map,
      std::string departure, std::vector<Location * > &locations,
                                                      int &distance);
template <typename T>
void swap(T &a, T &b);
template <typename T>
int partition(std::vector<T> &v, int &low, int &high, int (&comp)(T &, T &));
template <typename T>
void iterativeqsort(std::vector<T> &v, int (*comp)(T &, T &));
#endif  // FUNCTIONS_H_
