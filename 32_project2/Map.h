#include <iostream>
#include <string>
using namespace std;
#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
using KeyType = string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& src);

    
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
  private:
    
    struct Node{
        KeyType m_key;
        ValueType m_value;
        Node* n_next;
        Node* n_prev;
    };
    Node* n_head;
    Node* n_tail;
    int map_size;
};

bool merge(const Map& m1, const Map& m2, Map& result);
    //merge two maps into one, no duplicates
    
void reassign(const Map& m, Map& result);
    //When the reassign function returns, result must contain, for each pair p1 in m, a pair with p1's key mapping to a value copied from a different pair p2 in m, and no other pair in result has its value copied from p2.
    //However, if m has only one pair, then result must contain simply a copy of that pair. (You can't change partners if you're the only pair dancing!)
    //Notice that this spec does not require any particular one of the allowable reassignments and does not require that the reassignment be randomly chosen. (Hint: This function can thus be implemented without its having to repeatedly examine an auxiliary array or other container that holds a collection of many items.)

#endif /* Map_hpp */
