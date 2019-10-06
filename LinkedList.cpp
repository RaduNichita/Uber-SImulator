// Copyright Radu Nichita 311CA 27.03.2019 TEMA1 STRUCTURI DE DATE
#include <iostream>
#include "./LinkedList.h"
template <class T>
	LinkedList<T>::LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
template <class T>
	LinkedList<T>::LinkedList(const LinkedList &src){
		Node<T> *tmp = src.refhead();
		while (tmp != nullptr) {
			this->add(tmp);
			tmp = tmp -> next;
		}
	}
template <class T>
	LinkedList<T>::~LinkedList() {
		Node <T> *tmp = head;
		while (tmp) {
			Node <T> *current = tmp;
			tmp = tmp -> next;
			delete current;
		}
	}
template <class T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList src) {
    	this -> head = src.refhead();
    	return *this;
	}
template <class T>
	void LinkedList<T>::insert_sorted(T id) {
		Node<T> *tmp = new Node <T>(id);
		if (size == 0 ||  head->id > id){
			tmp->next = head;
			head = tmp;
			size++;
			return;
		} else {
		Node <T> *current = head;
		while (current-> next &&  id > current->next->id)  {
			current = current->next;
		}
		tmp -> next = current -> next;
		current -> next = tmp;
		size++;
		return;
		}
	}
template <class T>
	void LinkedList<T>::add(T id) {
		Node <T> *tmp = new Node<T>(id);
		if (size == 0) {
			head = tmp;
			tail = tmp;
			tail -> next = nullptr;
		} else {
			tail -> next = tmp;
			tail = tmp;
			tail -> next = nullptr;
		}
		size++;
	}
template <class T>
	void LinkedList<T>::addF(T id) {
		Node<T> *tmp = new Node<T>(id);
		if (size == 0) {
			head = tmp;
			tail = tmp;
			tail -> next = nullptr;
		} else {
			tmp -> next = head;
			head = tmp;
		}
		size++;
	}
template <class T>
	void LinkedList<T>::print(){
		Node <T> *tmp = head;
		while (tmp) {
			std::cout << tmp->id <<"\n";
			tmp = tmp -> next;
		}
	}
template <class T>
	Node<T>* LinkedList<T>::refhead(){
		return head;
	}
template <class T>
	Node<T>* LinkedList<T>::reftail(){
		return tail;
	}
