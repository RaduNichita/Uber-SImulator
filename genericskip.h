// Copyright Radu Nichita 311CA 27.03.2019 TEMA1 STRUCTURI DE DATE

#ifndef GENERICSKIP_H_
#define GENERICSKIP_H_
#define MINKEY -100000
#define MAXKEY  100000
#include "./LinkedList.h"

template <class T, class V>
struct SkipList_Node {
	T value;
	SkipList_Node ** forward;
	LinkedList <V> id_list;
	T getValue(){
		return this->value;
	}
	void setValue(T value){
		this->value = value;
		return;
	}
	SkipList_Node(T value, int level){
		this -> value = value;
		forward = new SkipList_Node <T, V>* [level + 1];
		for (int i = 0; i< level+1; i++) {
			forward[i] = nullptr;
		}
	}
	void add(V id) {
		this -> id_list.add(id);
	}
	void addF(V id) {
		this -> id_list.addF(id);
	}
	void insert_sorted(V id){
		this -> id_list.insert_sorted(id);
	}
	Node<V>* startlist(){
		return id_list.refhead();
	}
	Node<V>* endlist(){
		return id_list.reftail();
	}
	~SkipList_Node(){
		delete [] forward;
	}
};
template <class T, class V>
class SkipList {
	int max_level;
	float P;
	int level;
	SkipList_Node<T, V> *head;
	SkipList_Node<T, V> *tail;
 public:
	explicit SkipList(const int max_level = 4, const float P = 0.5,
								T minkey = MINKEY, T maxkey = MAXKEY);
	~SkipList();
		SkipList(const SkipList &otherSkiplist);
	SkipList& operator=(const SkipList *otherSkiplist);
	int randomLevel();
	SkipList_Node<T, V> *createNode(T key, int level);
	SkipList_Node<T, V>* insertElement(T key);
	SkipList_Node<T, V>* searchElement(T key);
	void print();
	SkipList_Node<T, V>* base();
	SkipList_Node<T, V> * end();
	LinkedList <V> *list_ordered_players();
};

#endif  // GENERICSKIP_H_
