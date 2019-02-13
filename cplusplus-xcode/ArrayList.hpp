//
//  ArrayList.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/8/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef ArrayList_hpp
#define ArrayList_hpp

#include <iostream>
using namespace std;

template <class T>
class ArrayList {
private:
    int lastIndex;
    int size;
    T * array;
public:
    ArrayList();
    ArrayList(int size);
    ~ArrayList();
    void removeAtIndex(int index);
    int capacity();
    int length();
    void push_back(T element);
    T & operator[] (int index);
    int lastElementIndex();
};
template <class T>
ArrayList<T>::ArrayList() {
    size = 0;
    array = new T[0];
}
template <class T>
ArrayList<T>::ArrayList(int newSize) {
    size = newSize;
    array = new T[size];
    lastIndex = newSize - 1;
}
template <class T>
ArrayList<T>::~ArrayList() {
    delete[] array;
}
template <class T>
void ArrayList<T>::removeAtIndex(int index) {
    if(index < size && index >= 0) {
        memcpy(array+sizeof(T)*index, array+sizeof(T)*(index+1), sizeof(T)*(size-index-1));
    }
}

template <class T>
T & ArrayList<T>::operator[] (int index) {
    return array[index];
}
template <class T>
int ArrayList<T>::capacity() {
    return size;
}
template <class T>
int ArrayList<T>::length() {
    return lastIndex+1;
}
template <class T>
void ArrayList<T>::push_back(T element){
    if(size == 0) {
        array = new T[1];
        size = 1;
        lastIndex = 0;
    }
    else if(lastIndex == size - 1) {
        int oldSize = size;
        size *= 2;
        T * temp = array;
        array = new T[size];
        memcpy(array, temp, sizeof(T)*oldSize);
        delete[] temp;
        lastIndex++;
    }
    array[lastIndex] = element;
}
#endif /* ArrayList_hpp */
