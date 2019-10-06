// Copyright Radu Nichita 311CA 27.03.2019 TEMA1 STRUCTURI DE DATE
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <class T>
struct Node {
	T id;
	Node <T> *next;
	Node() {
		next = nullptr;
	}
	explicit Node(T id) {
		this -> id = id;
		next = nullptr;
	}
	T getValue() {
		return id;
	}
};
template <class T> class LinkedList {
	Node <T> * head;
	Node <T> * tail;
	int size;
 public:
	LinkedList();
	LinkedList(const LinkedList &src);
	~LinkedList();
	LinkedList& operator=(LinkedList src);
	void insert_sorted(T id);
	void add(T id);
	void addF(T id);
	void print();
	Node<T>* refhead();
	Node<T>* reftail();
};

#endif  // LINKEDLIST_H_
