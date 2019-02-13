//
//  Node.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/9/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>

template <class T>
class Node {
public:
    Node(T data);
    void appendToTail(T data);
    T getData();
private:
    Node * next = nullptr;
    T data;
};
template <class T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
}
template <class T>
void Node<T>::appendToTail(T data) {
    //i dont think this variable will live beyond this scope so probably gotta call new so test this case
    Node newNode(data);
    Node * nodePointer = this;
    while((nodePointer->next) != nullptr) { //the inner parentheses is a must
        nodePointer = nodePointer->next;
    }
    nodePointer->next = &newNode;
}
template <class T>
T Node<T>::getData() {
    return data;
}

#endif /* Node_hpp */
