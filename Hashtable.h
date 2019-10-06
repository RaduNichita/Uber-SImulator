// Copyright Radu Nichita 311CA 4.05.2019 TEMA2 STRUCTURI DE DATE

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include<list>

template <typename Tkey, typename Tvalue> struct info_t {
  Tkey key;
  Tvalue value;
};
template <typename Tkey, typename Tvalue>  class Hashtable {
 private:
  std::list < info_t <Tkey, Tvalue> > *H;
  int size;
  int capacity;
  int (*hash)(Tkey);

 public:
  Hashtable(int capacity, int(*h)(Tkey));
  ~Hashtable();
  int& getSize() const;
  void insert(Tkey &key, Tvalue &value);
  void update(Tkey key, Tvalue newvalue);
  Tvalue getValue(Tkey &key);
  Tvalue& getValuebyRef(Tkey key);
  void removeValue(Tkey key, Tvalue rvalue);
};
template <typename Tkey, typename Tvalue>
Hashtable<Tkey, Tvalue>::Hashtable(int capacity, int(*h)(Tkey)) {
    this -> capacity = capacity;
    this -> size = 0;
    this -> hash = h;
    this -> H = new std::list<info_t <Tkey, Tvalue> > [this -> capacity];
  }
template <typename Tkey, typename Tvalue>
 Hashtable<Tkey, Tvalue>::~Hashtable() {
    for (int i = 0; i < capacity; i++) {
          while (!H[i].empty()) {
            H[i].pop_back();
          }
      }
      delete [] H;
  }
template <typename Tkey, typename Tvalue>
  int& Hashtable<Tkey, Tvalue>::getSize() const {
    return size;
}

template <typename Tkey, typename Tvalue>
  void Hashtable<Tkey, Tvalue>::insert(Tkey &key, Tvalue &value) {
    int hkey = hash(key) % capacity;
    for (auto it = H[hkey].begin(); it != H[hkey].end(); it++) {
      if (it -> key == key) {
        it -> value = value;
        return;
      }
    }
      struct info_t <Tkey, Tvalue > addValue;
      addValue.key  = key;
      addValue.value = value;
      H[hkey].emplace_back(addValue);
      this -> size++;
}

template <typename Tkey, typename Tvalue>
  void Hashtable<Tkey, Tvalue>::update(Tkey key, Tvalue newvalue) {
    int hkey = hash(key) % capacity;
    for (auto it = H[hkey].begin(); it != H[hkey].end(); it++) {
      if (it -> key == key) {
        it -> value = newvalue;
        return;
      }
    }
  }
template <typename Tkey, typename Tvalue>
  Tvalue Hashtable<Tkey, Tvalue>::getValue(Tkey &key) {
    int hkey = hash(key) % capacity;
      for (auto it = H[hkey].begin(); it != H[hkey].end(); it++) {
          if (it -> key == key){
            return it -> value;
          }
      }
        return Tvalue();
    }
  template <typename Tkey, typename Tvalue>
  void Hashtable<Tkey, Tvalue>::removeValue(Tkey key, Tvalue rvalue) {
      int hkey = hash(key) % capacity;
      for (auto it = H[hkey].begin(); it != H[hkey].end(); it++){
          if (it->value == rvalue) {
          it = H[hkey].erase(it);
          return;
          }
      }
    }
  template <typename Tkey, typename Tvalue>
  Tvalue& Hashtable<Tkey, Tvalue>::getValuebyRef(Tkey key) {
      try  {
        int hkey = hash(key) % capacity;
      for (auto it = H[hkey].begin(); it != H[hkey].end(); it++) {
          if (it -> key == key){
            return (it -> value);
          }
      }
    } catch (std::exception& e) {
      std::cerr << "Standard exception" << e.what() << "\n";
    }
    return getValuebyRef(key);
  }
#endif  // HASHTABLE_H_
