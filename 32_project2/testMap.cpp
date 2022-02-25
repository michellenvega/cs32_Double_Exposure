#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;
int main() {
    
    Map my_map;
    assert(my_map.empty() == true);
    my_map.insert("hello", 45.0);
    assert(!my_map.empty() && my_map.size()== 1 && !my_map.contains("Hello"));
    my_map.insert("what", 43.0);
    assert(!my_map.empty() && my_map.size()== 2);
    my_map.insert("yellow", 23.0);
    assert(!my_map.empty() && my_map.size()== 3);
    my_map.update("yellow", 0.0);
    my_map.update("hello", 2.0);
    assert(my_map.size()== 3);
    assert(my_map.contains("hello") && !my_map.contains("Michelle"));
    my_map.insertOrUpdate("yellow", 9);
    assert(!my_map.contains("Teresa"));
    my_map.insertOrUpdate("Teresa", 17);
    assert(my_map.contains("Teresa") && my_map.size()== 4);
    my_map.erase("hello");
    assert(my_map.size()== 3 && !my_map.contains("hello"));

    my_map.insert("Camila", 8.70);
    ValueType test;
    assert(my_map.get("Camila", test) && test==8.70);
    assert(!my_map.get("hello", test) && test==8.70);
    assert(my_map.get("yellow", test) && test==9);

    Map m1;
    m1.insert("yolo", 55.0);
    
    my_map.swap(m1);
    assert(m1.size() != 0 && my_map.size() == 1);
    my_map.swap(my_map);
    assert(my_map.size() == 1);
    ValueType test1;
    assert(m1.get("Camila", test1) && test1==8.70);
    
    //check copy constructor
    Map testMe = m1;
    ValueType test2;
    assert(testMe.get("Camila", test2) && test2==8.70);
    assert(testMe.size() == 4);
    //check assignment operator
    Map your_map;
    your_map = my_map;
    ValueType your_val;
    your_map.get("yolo", your_val);
    assert(your_map.size() == 1 && your_val == 55.0);
    your_map.erase("yolo");
    assert(!your_map.contains("yolo"));
    //check merge function
    Map my_result;
    my_result.insert("no", 0.0);
    
    Map mm1; Map mm2;
    mm1.insert("a", 1.0);
    mm1.insert("c", 3.0);
    mm2.insert("b", 2.0);
    mm2.insert("d", 4.0);
    assert(merge(mm1, mm2, my_result)&& my_result.size()==4);
    mm2.insert("c", 4.5);
    assert(!merge(mm1, mm2, my_result) && my_result.size()==3);
    
    Map cs1; Map cs2; Map cs_result;
    cs_result.insert("no", 3.0);
    cs1.insert("Fred", 123);
    cs1.insert("Ethel", 456);
    cs1.insert("Lucy", 789);
    cs2.insert("Lucy", 789);
    cs2.insert("Ricky", 321);
    assert(merge(cs1, cs2, cs_result) && cs_result.size()==4
           && !cs_result.contains("no"));
    cs2.update("Lucy", 788);
    assert(!merge(cs1, cs2, cs_result) && cs_result.size()==3
           && !cs_result.contains("Lucy"));

    
    //check reassign function
    
    
    //refer to same map? reassign same map!
    Map redo;
    redo.insert("Fred", 123);
    redo.insert("Ethel", 456);
    redo.insert("Lucy", 789);
    redo.insert("Ricky", 321);
    reassign(redo, redo);
    assert(redo.size()==4);
    //must have:     "Fred"  789      "Ethel"  123      "Lucy"  321      "Ricky"  456
    ValueType fred, ethel, lucy, ricky;
    redo.get("Fred", fred);
    redo.get("Ethel", ethel);
    redo.get("Lucy", lucy);
    redo.get("Ricky", ricky);
    assert(fred == 789 && ethel == 123 && lucy == 321 && ricky == 456);
    
    Map redo2; Map redo3;
    redo2.insert("Fred", 123);
    redo2.insert("Ethel", 456);
    redo2.insert("Lucy", 456);
    
    reassign(redo2, redo3);
    redo3.get("Fred", fred);
    redo3.get("Ethel", ethel);
    redo3.get("Lucy", lucy);
    // must have:      "Fred"  456      "Ethel"  123      "Lucy"  456
    assert(fred == 456 && ethel == 123 && lucy == 456);
    
    redo3.erase("Lucy");
    assert(!redo3.contains("Lucy") && !redo3.get("Lucy", lucy));
    
    //test reassign for map with only one value;
        Map j;
        Map k;
        j.insert("The Avengers 3", 4.7);
        reassign(j, k); ValueType y;
        assert(k.get("The Avengers 3", y) && y == 4.7);
        assert(k.size() == 1);
    
    cout << "All tests passed.\n";
    
    
    //TO DO!
    //do report.docx!
    //test erase for tail pointer!
    //GO BACK AND MAKE COMMENTS
    
}


