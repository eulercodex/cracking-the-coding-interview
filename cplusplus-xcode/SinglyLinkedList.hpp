//
//  SinglyLinkedList.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/9/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef SinglyLinkedList_hpp
#define SinglyLinkedList_hpp

#include <stdio.h>
#include "Node.hpp"

class SinglyLinkedList {
private:
    Node * head;
public:
    SinglyLinkedList(Node head);
    Node * getHead();
    void deleteNode(Node node);
};

SinglyLinkedList::SinglyLinkedList(Node head) {
    this->head = &head;
}
Node * SinglyLinkedList::getHead() {
    return head;
}
//TODO: finish and test this class!!!
#endif /* SinglyLinkedList_hpp */
