// Copyright Radu Nichita 311CA 27.03.2019 TEMA1 STRUCTURI DE DATE
#include <iostream>
#include <random>
#include "./genericskip.h"
#define MINKEY -100000
#define MAXKEY  100000
template <class T, class V>
	 SkipList<T, V>::SkipList(const int max_level, const float P,
								T minkey, T maxkey ) {
		this -> max_level = max_level;
		this -> P = P;
		level = 0;
		head = new SkipList_Node<T, V>(minkey, max_level);
		tail = new SkipList_Node<T, V>(maxkey, max_level);
		for (int i = 0; i < max_level + 1; i++) {
			head -> forward[i] = tail;
		}
	}
template <class T, class V>
	SkipList<T, V>::~SkipList() {
		SkipList_Node<T, V> *curent = head -> forward[0];
		while (curent != tail) {
			SkipList_Node<T, V> *temp = curent;
			curent = curent -> forward[0];
			delete temp;
		}
		delete head;
		delete tail;
	}
template <class T, class V>
		SkipList<T, V>::SkipList(const SkipList &otherSkiplist) {
		this -> max_level = 8;
		this -> P = 0.5;
		level = 0;
		head = new SkipList_Node<T, V>(MINKEY, max_level);
		tail = new SkipList_Node<T, V>(MAXKEY, max_level);
		for (int i = 0; i < max_level + 1; i++) {
			head -> forward[i] = tail;
		}
		SkipList_Node <T, V> *curent = otherSkiplist.base();
		while (curent != otherSkiplist.end()) {
				*this->insertElement(curent->value);
			curent = curent -> forward[0];
		}
	}
template <class T, class V>
	SkipList<T, V>& SkipList<T, V>::operator=(const SkipList *otherSkiplist) {
		this -> max_level = 8;
		this -> P = 0.5;
		level = 0;
		head = new SkipList_Node<T, V>(MINKEY, otherSkiplist->max_level);
		tail = new SkipList_Node<T, V>(MAXKEY, otherSkiplist->max_level);
		for (int i = 0; i < otherSkiplist->max_level + 1; i++) {
			head -> forward[i] = tail;
		}
		SkipList_Node<T, V> *curent = otherSkiplist.base();
		while (curent != otherSkiplist.end()) {
				*this->insertElement(curent->value);
			curent = curent -> forward[0];
		}
		return *this;
	}
template <class T, class V>
	int SkipList<T, V>::randomLevel(){
		float randLev = (float) rand()/RAND_MAX;
		int currentLev = 0;
		while (randLev < this->P && currentLev < max_level) {
			currentLev++;
			randLev = (float) rand()/RAND_MAX;
		}
		return currentLev;
	}
template <class T, class V>
	SkipList_Node<T, V>*SkipList<T, V>::createNode(T key, int level){
		SkipList_Node<T, V> *newNode = new SkipList_Node<T, V> (key, level);
		return newNode;
	}
template <class T, class V>
	SkipList_Node<T, V>* SkipList<T, V>::insertElement(T key) {
		SkipList_Node<T, V> *update[max_level + 1];
		for(int i = 0; i< max_level + 1 ; i++){
			update[i] = nullptr;
		}
		SkipList_Node<T, V> * temp = head;
		for (int i = level; i >= 0; i--) {
			while (temp->forward[i] != tail && temp->forward[i]-> value < key) {
				temp = temp -> forward[i];
			}
			update[i] = temp;
		}
		temp = temp -> forward[0];
		if (temp == tail || temp->value != key) {
			int randlevel = randomLevel();
			if (randlevel > level) {
				for (int i = level + 1; i< randlevel+1; i++) {
					update[i] = head;
				}
				level = randlevel;
			}
			SkipList_Node<T, V> *node = new SkipList_Node<T, V>(key, randlevel);
			for (int i = 0; i <= randlevel; i++) {
				node -> forward[i] = update[i] -> forward[i];
				update[i] -> forward[i] = node;
			}
		return node;
		} else {
			temp = nullptr;
			return temp;
		}
	}
template <class T, class V>
	SkipList_Node<T, V>* SkipList<T, V>::searchElement(T key) {
		SkipList_Node<T, V> * temp = head;
		for(int i = level; i >= 0; i--) {
			while(temp -> forward[i] != tail
								&& temp->forward[i]->value < key) {
				temp = temp -> forward[i];
			}
		}
		temp = temp -> forward[0];
		if (temp != tail && temp->value == key) {
			return temp;
		} else {
			temp = nullptr;
			return temp;
		}
	}
template <class T, class V>
	void SkipList<T, V>::print(){
		std::cout << "............SkipList ...........\n";
		std::cout << "\n";
		SkipList_Node<T, V> * temp = this->head;
		for (int i = 0; i <= level; i++) {
			temp = head -> forward[i];
			std::cout << "Level " << i <<": ";
			while (temp != tail) {
				std::cout << temp -> value << " ";
				temp = temp -> forward[i];
			}
			std::cout << "..................\n";
			std::cout << std::endl;
		}
	}
template <class T, class V>
	SkipList_Node<T, V>* SkipList<T, V>::base(){
		return head -> forward[0];
	}
template <class T, class V>
	SkipList_Node<T, V>* SkipList<T, V>::end(){
		return tail;
	}
template <class T, class V>
	LinkedList<V> * SkipList<T, V>::list_ordered_players(){
		LinkedList<V> *playerlist = new LinkedList<V>;
		SkipList_Node<T, V> *curent = head -> forward[0];
		while (curent != tail) {
			Node<V> *tmp  = curent -> startlist();
			while (tmp) {
				playerlist -> addF(tmp ->getValue());
				tmp = tmp-> next;
			}
			curent = curent -> forward[0];
		}
		return playerlist;
	}
