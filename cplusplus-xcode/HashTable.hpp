//
//  HashTable.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/16/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <vector>
#include <list>

#define DEFAULT_CAPACITY 256

using namespace std;

//you can't template a typedef, also there is no need to typedef structs in C++ but you we can still use the "typedef" shortcuts during initialization
template <class T, class U>
struct hashItem {
    T key;
    U data;
};
template <class T, class U>
class HashTable {
private:
    //You have to use = or {} for in-place member initialization, because it could be confused for a function
    vector<list<hashItem<T,U>>> linkedListArray = vector<list<hashItem<T,U>>>(DEFAULT_CAPACITY);
    size_t capacity = DEFAULT_CAPACITY;
    size_t size = 0;
public:
    U & operator[](T key);
};

template <class T, class U>
U & HashTable<T,U>::operator[](T key) {
    std::hash<T> hash_fn;
    size_t index = hash_fn(key)%capacity; //I had to add the template T maybe because of hash being a template itself
    list<hashItem<T,U>> &aList = linkedListArray[index]; //i had to add & and I don't even know why :/ maybe because it returns a reference but i still cant wrap my head around it
    if(aList.size() == 0) {
        hashItem<T, U> newItem;
        newItem.key = key;
        aList.push_back(newItem);
        return aList.back().data;
    }
    else {
        //need to add 'typename'
        for(typename list<hashItem<T,U>>::iterator it = aList.begin(); it != aList.end(); it++) {
            if ((*it).key == key) return (*it).data;
        }
        hashItem<T, U> newItem;
        newItem.key = key;
        aList.push_back(newItem);
        return aList.back().data;
    }
}
#endif /* HashTable_hpp */
