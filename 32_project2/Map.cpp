#include "Map.h"


Map::Map(){
    //initializes an empty map
    n_head = nullptr;
    n_tail = nullptr;
    map_size = 0;
}

Map::~Map(){
    if(n_head==nullptr)return;
    //deallocates memory of linked list
    Node *p = n_head;
    while(p!=nullptr){
        Node *temp = p->n_next;
        delete p;
        p = temp;
    }
    
}

Map::Map(const Map& other){
    //copy size
    map_size = other.map_size;
    
    if(other.size()==0){
        n_head = nullptr; n_tail = nullptr;
        //creates empty map, like other
        return;
    }
   //create a new linked list
    n_head = new Node;
    n_head->n_prev = nullptr;
    Node*p= n_head;
    Node*q=other.n_head;
    
    //copies all but the last node
    while(q->n_next!=nullptr){
        Node* newNode = new Node;
        //allocates new nodes as we iterate
         p->m_key = q->m_key;
         p->m_value = q->m_value;
         p->n_next = newNode;
         newNode->n_prev = p;
        //move to next node
         p = p->n_next;
         q=q->n_next;
    }
    
    //copies data to last node and sets next to nullptr
        p->m_key = q->m_key;
        p->m_value = q->m_value;
        p->n_next = nullptr;
    if(n_head->n_next != nullptr)
        //sets tail pointer
        n_tail = p;
    else
        n_tail = nullptr;
    
    
}


Map& Map::operator=(const Map& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}




bool Map::empty() const{
    //if first item is null
    //map is empty
    if (n_head==nullptr)
        return true;
    //if not, it is not empty
    return false;
}
int Map::size() const{
    //returns size of map
    return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value){
   if(contains(key)){
       return false;
   }
    if(n_head == nullptr){
        /* 1. allocate node */
        Node* new_node = new Node;
        /* Put in the data */
        new_node->m_key = key;
        new_node->m_value = value;
        /* Make next of new node as head
        and previous as NULL */
        new_node->n_prev = nullptr;
        new_node->n_next = n_head;
        n_head = new_node;
   
        map_size++;
        return true;
    }
    
    //determine if at top
    else if(key < n_head->m_key){
        /* 1. allocate node */
          Node* new_node = new Node;
        /* Put in the data */
         new_node->m_key = key;
         new_node->m_value = value;
        /* Make next of new node as head
        and previous as NULL */
        new_node->n_next = n_head;
        new_node->n_prev = NULL;

          if (n_head != NULL)
         n_head->n_prev = new_node;
              
      
         n_head = new_node;
        
        map_size++;
        return true;
         }
    else{
        //which value is it greater than?
        /* 1. allocate node */
       Node* new_node = new Node;
       Node* p = n_head;
       while(p!=nullptr){
            if(key < p->m_key){
                /* Put in the data */
                new_node->m_key = key;
                new_node->m_value = value;
                new_node->n_next = p;
                new_node->n_prev = p->n_prev;
                p->n_prev->n_next = new_node;
                p->n_prev = new_node;
                map_size++;
                return true;
       
       }
       //Move on to next node
           if(p->n_next==nullptr) break;
               p = p->n_next;
       }
        /* Put in the data */
        
        new_node->m_key = key;
        new_node->m_value = value;
        new_node->n_prev = p;
        new_node->n_next = nullptr;
        p->n_next = new_node;
        n_tail = new_node;
        map_size++;
        
        
    }

    return true;
}

bool Map::update(const KeyType& key, const ValueType& value){
    if(n_head == nullptr) return false;
    Node* p = n_head;
    while(p!=nullptr){
        if(p->m_key == key){
            p->m_value = value;
            return true;
        }
        if(p->n_next!=nullptr)
            p = p->n_next;
        else
            return false;
    }
    
    return false;
}


// insert or update
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if(n_head == nullptr) insert(key, value);
    
 // If key is equal to a key currently in the map, then make that key no
 // longer map to the value that it currently maps to, but instead map to
 // the value of the second parameter; return true in this case.
 if(contains(key)) update(key, value);
 
 // If key is not equal to any key currently in the map and if the
 // key/value pair can be added to the map, then do so and return true.
 if(!contains(key))insert(key, value);
    

 // Otherwise, make no change to the map and return false (indicating
 // that the key is not already in the map and the map has a fixed
 // capacity and is full).
 return true;
 
}


// erase
bool Map::erase(const KeyType& key){
    //not in map or map is empty, return false
    if(!contains(key) || n_head == nullptr) return false;
    
    if(n_head->m_key == key){ // holds item we wish to delete
        Node *killMe = n_head; //temp pointer for head
        n_head = killMe->n_next; //becomes 2nd node in the list
        delete killMe; //deletes temp
        map_size--;
        return true;
    }
    
    Node* p = n_head;
    //find value
    while(p!=nullptr){
        if(p->n_next !=nullptr && p->n_next->m_key == key) break; // found key!
        p = p->n_next;
    }
    
    //found value, now let's delete it!
    bool isTail = false;
    if(n_tail->m_key == p->n_next->m_key) isTail = true;
    if(p!=nullptr && !isTail){
        Node *killMe = p->n_next; //temp pointer for p
        p->n_next = killMe->n_next; //becomes 2nd node in the list
        if(p->n_next!=nullptr)
        p->n_next->n_prev = p;
        delete killMe; //deletes temp
    } else if (isTail){
        n_tail = p;
        Node *killMe = p->n_next; //temp pointer for p
        p->n_next = killMe->n_next; //becomes 2nd node in the list
        if(p->n_next!=nullptr)
        p->n_next->n_prev = p;
        delete killMe; //deletes temp
    }
        

    
    
    
    
    //if tail pointer
    
    
    map_size--;
    return true;
}


bool Map::contains(const KeyType& key) const{
   if(n_head == nullptr) return false;
    Node* p = n_head;
    while(p!=nullptr){
        //if found, then return true
        if(p->m_key == key) return true;
        //if not move to next node
        if(p != n_tail) p = p->n_next;
        else // is that the last one? return false
            return false;
    }
    
    return false;
}


bool Map::get(const KeyType& key, ValueType& value) const{
    if(n_head == nullptr || !contains(key)) return false;
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.
    Node* p = n_head;
    while(p!=nullptr){
        //if found, then return true
        if(p->m_key == key) {
            value = p->m_value;
            return true;}
        //if not move to next node
        if(p != n_tail && p->n_next!=nullptr) p = p->n_next;
        
    }
    
    //Otherwise, make no change to the value parameter of this function and return
    // false.
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (0<=i && i < size()){
        Node *p = n_head;
        int count = 0;
        while (count <= i){
            
            if (count ==i){
                value = p->m_value;
                    key = p->m_key;
                    return true;
            }
            if (p->n_next!=nullptr)
            p=p->n_next;
            count++;
        }
    }
    return false;
}


void Map::swap(Map& other){
    // Exchange the contents of this map with the other one.
    //If attempting to swap map with itself, return
    if(&other == this) return;
    
    //have to swap, head,tail,and map_size
    //swap heads first
    Node *temp = this->n_head;
    this->n_head = other.n_head;
    other.n_head = temp;
    
    //swap tails
    Node *tempTail = this->n_tail;
    this->n_tail = other.n_tail;
    other.n_tail = tempTail;
    
   //switch sizes
    int tempSize = this->map_size;
    this->map_size = other.map_size;
    other.map_size = tempSize;
    
}
bool merge(const Map& m1, const Map& m2, Map& result){ //merge two maps into one, no duplicates!
    //if same key, must have same value! and return true
    //we must not assume result is empty when it is passed in to this function; it might not be.
    //copies m1 contents into result
    result = m1;
    bool isSame = true; //is the value of a duplicate the same?
    for(int i=0; i < m2.size();i++){
        //define and initialize variables for the keys and values
        KeyType tempKey; ValueType tempVal;
        m2.get(i, tempKey, tempVal);
        ValueType getTemp;
        //bool to determine whether it is
        //already in result
        bool get = result.get(tempKey, getTemp);
        if(!get) result.insert(tempKey, tempVal);
        else if(getTemp != tempVal){
        //if not, still merge but do not include it and return false
            isSame = false;
            result.erase(tempKey);
        }
    }
    return isSame;
    
}

void reassign(const Map& m, Map& result){
    if(m.size()==1){
        result = m;
        return;}
    else if(m.size()==0)return;
    Map temp; //temp map
    bool passed= false; //have we already added a value?
//go down and switch current with next
    for(int i=0; i < m.size()-1;i++){
        //define variables for the keys and values
        KeyType currKey; ValueType currVal;
        KeyType nextKey; ValueType nextVal;
        if(!passed){
        //if obtaining values for the first time
        m.get(i, currKey, currVal);
        m.get(i+1, nextKey, nextVal);
            passed = true;
        }
        else{ //obtain values
        temp.get(i, currKey, currVal); //current
        m.get(i+1, nextKey, nextVal);} //one after curren
        
        if(temp.contains(currKey)){
        //if in temp, must update
        //reassign current and next values
        temp.insertOrUpdate(currKey, nextVal);
        temp.insertOrUpdate(nextKey, currVal);}
        else{ //if not, then insert
        //reassign current and next values
        temp.insert(currKey, nextVal);
        temp.insert(nextKey, currVal);
        }

    }

    result = temp; //temp map as the result
    
}
