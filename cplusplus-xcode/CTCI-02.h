//
//  CTCI-02.cpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 11/24/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_02
#define CTCI_02

#include "data_structures.h"
#include <unordered_set>
#include <stack>

using namespace std;

//2.1
template <class T>
void removeDups1(SinglyLinkedListNode<T> * node){
    if (node == nullptr) return;
    unordered_set<T> set;
    SinglyLinkedListNode<T> * prev = nullptr;
    SinglyLinkedListNode<T> * cur = node;
    while(cur != nullptr) {
        if(set.count(cur->data) == 0) {
            set.insert(cur->data);
            prev = cur;
            cur = cur->next;
        }
        else {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        }
    }
}
template <class T>
void removeDups2(SinglyLinkedListNode<T> * node) {
    if(node == nullptr) return;
    SinglyLinkedListNode<T> * current = node;
    while (current != nullptr) {
        SinglyLinkedListNode<T> * previousRunner = current;
        SinglyLinkedListNode<T> * runner = current->next;
        while(runner != nullptr) {
            if(runner->data == current->data) {
                previousRunner->next = runner->next;
                delete runner;
                runner = previousRunner->next;
            }
            else {
                previousRunner = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
}
//2.2
template <class T>
SinglyLinkedListNode<T> * returnKthToLastHelper(SinglyLinkedListNode<T> * node, int k, int &i) {
    if(node == nullptr) {
        //once we reach the deepest level in the recursion, this would be returned if the kth to last element does not exist :)
        return nullptr;
    }
    SinglyLinkedListNode<T> * returnedNodeFromTheRecursion = returnKthToLastHelper(node->next, k, i);
    i = i + 1; //start counting from last non-NULL node to find kth node
    if(i == k) {
        return node; //well return the node at this level of the recursion instead of the last node/tail
    }
    return returnedNodeFromTheRecursion;
}

template <class T>
SinglyLinkedListNode<T> * returnKthToLast(SinglyLinkedListNode<T> * head, int k) {
    int i = 0;
    return returnKthToLastHelper(head, k, i);
}
//2.3
template <class T>
void deleteMiddleNode(SinglyLinkedListNode<T> * node){
    if(node == nullptr || node->next == nullptr)
        return; //can't delete
    SinglyLinkedListNode<T> * next = node->next;
    node->data = next->data;
    node->next = next->next;
    delete next;
}
//2.4
template <class T>
SinglyLinkedListNode<T> * partition(SinglyLinkedListNode<T> * node, int x) {
    if(node == nullptr)
        return node;
    //make the first node the head and also the tail
    SinglyLinkedListNode<T> * head = node;
    SinglyLinkedListNode<T> * tail = node;
//    node = node->next;
    while(node != nullptr) {
        //grab the next node either add to the head or the tail depending on the partioning rule
        SinglyLinkedListNode<T> * next = node->next;
        if(node->data < x) { //add to head
            node->next = head;
            head = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
        node = next;
    }
    tail->next = nullptr;
    return head;
}
//2.5
template <class T>
SinglyLinkedListNode<T> * sumLists1(SinglyLinkedListNode<T> * a,SinglyLinkedListNode<T> * b) {
    //iteratively
    SinglyLinkedListNode<T> * node = nullptr;
    SinglyLinkedListNode<T> * head = nullptr;
    T carry = 0;
    while(a != nullptr || b != nullptr || carry != 0) {
        T sum = carry;
        if(a != nullptr) {
            sum += a->data;
            a = a->next;
        }
        if(b != nullptr) {
            sum += b->data;
            b = b->next;
        }
        T digit = sum%10;
        if(node == nullptr) {
            node = new SinglyLinkedListNode<T>(digit,nullptr);
            head = node;
        }
        else {
            node->next = new SinglyLinkedListNode<T>(digit,nullptr);
            node = node->next;
        }
        carry = (sum-digit)/10;
    }
    return head;
}
//2.6
template<class T>
bool palindrome(SinglyLinkedListNode<T> * list) {
    if(list == nullptr)
        return false; //this could go either way, doesn't matter much though
    if(list->next ==nullptr)
        return true; //list with one node is an automatic palindrome
    stack<T> store;
    SinglyLinkedListNode<T> * node = list;
    SinglyLinkedListNode<T> * runner = list;
    while(runner->next != nullptr) {
        store.push(node->data);
        if(runner->next->next != nullptr) {
            node = node->next;
            runner = runner->next->next;
        }
        else {
            runner = runner->next;//to get out of the loop when the length of the list is even
        }
    }
    if(runner->next == nullptr) {//if it's even, move node forward. 1->2->2->1, to move the 3rd node
        node = node->next;
    }
    while(!store.empty() && node != nullptr) {
        T top = store.top();
        if(top != node->data)
            return false;
        store.pop();
        node = node->next;
    }
    return true;
}
//2.7
template <class T>
SinglyLinkedListNode<T> * lastNode(SinglyLinkedListNode<T> *list, int & length) {
    length = 0;
    SinglyLinkedListNode<T> * tail = nullptr;
    while(list != nullptr) {
        length++;
        tail = list;
        list = list->next;
    }
    return tail;
}
template <class T>
SinglyLinkedListNode<T> * intersection(SinglyLinkedListNode<T> * a, SinglyLinkedListNode<T> *b) {
    int lengthOfA, lengthOfB;
    if(lastNode(a, lengthOfA) != lastNode(b, lengthOfB)) {
        return nullptr; //definitely no intersection
    }
    if(lengthOfA > lengthOfB) {
        for(int i = 0; i < (lengthOfA-lengthOfB); i++) {
            a = a->next;
        }
    }
    else {
        for(int i = 0; i < (lengthOfB-lengthOfA); i++) {
            b = b->next;
        }
    }
    while (a != b) {
        a = a->next;
        b = b->next;
    }
    return a; //or b for that matter
}
//2.8 loop detection
//find t such that d + (t-d)mod(C) = d + (2*t-d)mod(C) and t >= d (one pointer moving twice as fast
//then move on of the pointers to the head, then iterate over each node at the same speed to find intersection/beginning of the loop
//which occurs when (t-d)modC = 0
//d is delay, C is the length of the cycle, t is the position of the slower pointer after t iterations
template <class T>
SinglyLinkedListNode<T> * loopDetection (SinglyLinkedListNode<T> * node) {
    if(node == nullptr)
        return nullptr; //seriously though, what were you hoping?
    SinglyLinkedListNode<T> * slow = node;
    SinglyLinkedListNode<T> * fast = node;
    while(fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow || fast == nullptr) {
            break;
        }
    }
    if(fast == nullptr || fast->next == nullptr) {
        return nullptr; //no cycle yo!
    }
    slow = node;
    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow; //fast would have worked as well
}
#endif
