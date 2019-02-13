//
//  CTCI-03.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 11/28/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_03_hpp
#define CTCI_03_hpp

//3.2
#include <stack>
#include <exception>

template <class T>
class StackWithMin {
private:
    std::stack<T> minStack;
    std::stack<T> dataStack;
public:
    void push(T element);
    void pop();
    bool empty();
    T & top();
    T & min();
};

template <class T>
void StackWithMin<T>::push(T element) {
    dataStack.push(element);
    if(minStack.empty()) {
        minStack.push(element);
        return;
    }
    if(element < minStack.top()) {
        minStack.push(element);
    }
    else {
        minStack.push(minStack.top());
    }
}
template <class T>
void StackWithMin<T>::pop() {
    if(dataStack.empty()) {
        throw std::exception();
    }
    else {
        dataStack.pop();
        minStack.pop();
    }
}
template <class T>
bool StackWithMin<T>::empty() {
    return dataStack.empty();
}
template <class T>
T & StackWithMin<T>::top() {
    return dataStack.top();
}
template <class T>
T & StackWithMin<T>::min() {
    return minStack.top();
}
//3.3
template <class T>
class SetOfStacks {
private:
    std::vector<stack<T>> stacks;
    int stackSize;
    int sizeOfTheLastStack;
public:
    SetOfStacks(int size);
    void push(T element);
    void pop();
    bool empty();
    T & top();
    void popAtIndex(int index);
};
template <class T>
SetOfStacks<T>::SetOfStacks(int size) {
    sizeOfTheLastStack = 0;
    stackSize = size;
}
template <class T>
void SetOfStacks<T>::push(T element) {
    if(stacks.size() == 0) {
        stacks.push_back(stack<T>());
        stacks[stacks.size()-1].push(element);
        sizeOfTheLastStack++;
        return;
    }
    if(sizeOfTheLastStack == stackSize) {
        stacks.push_back(stack<T>());
        stacks[stacks.size()-1].push(element);
        sizeOfTheLastStack = 1;
    }
    else {
        stacks[stacks.size()-1].push(element);
        sizeOfTheLastStack++;
    }
    return;
}
template <class T>
void SetOfStacks<T>::pop() {
    if(stacks.size() == 0) {
        throw exception();
    }
    if(sizeOfTheLastStack == 0) {
        stacks.pop_back();
        stacks[stacks.size()-1].pop();
        sizeOfTheLastStack = stackSize - 1;
    }
    else {
        stacks[stacks.size()-1].pop();;
        sizeOfTheLastStack--;
    }
}
template <class T>
bool SetOfStacks<T>::empty() {
    if(stacks.size() == 0) {
        return true;
    }
    return false;
}
template <class T>
T & SetOfStacks<T>::top() {
    if(stacks.size() == 0) {
        throw exception();
    }
    return (sizeOfTheLastStack==0)? stacks[stacks.size()-2].top(): stacks[stacks.size()-1].top();
}
template <class T>
void SetOfStacks<T>::popAtIndex(int index) {
    if(index >= stacks.size())
        throw exception();
    //not implemented :/
}
//3.4
template <class T>
class QueueViaStacks {
private:
    std::stack<T> in;
    std::stack<T> out;
public:
    void push(T element);
    void pop();
    T & front();
    bool empty();
};
template <class T>
void QueueViaStacks<T>::push(T element){
    in.push(element);
}
template <class T>
void QueueViaStacks<T>::pop(){
    if(!out.empty()){
        out.pop();
    }
    else{
        if(in.empty()) {
            throw exception();
        }
        while(!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        out.pop();
    }
}
template <class T>
T & QueueViaStacks<T>::front(){
    if(!out.empty()){
        return out.top();
    }
    if(in.empty()) {
        throw exception();
    }
    while(!in.empty()) {
        out.push(in.top());
        in.pop();
    }
    return out.top();
}
template <class T>
bool QueueViaStacks<T>::empty(){
    if(in.empty() && out.empty()) {
        return true;
    }
    return false;
}
//3.5
template <class T>
void sortStack(std::stack<T> &stack) {
    if(stack.empty())
        return; //and we are done here
    std::stack<T> tempStack;
    int count = 0;
    while(!stack.empty()){
        count++;
        T element = stack.top();
        stack.pop();
        if(tempStack.empty()) {
            tempStack.push(element);
        }
        else {
            while(!tempStack.empty() && element < tempStack.top()) {
                count++;
                stack.push(tempStack.top());
                tempStack.pop();
            }
            tempStack.push(element);
        }
    }
    while(!tempStack.empty()){
        count++;
        stack.push(tempStack.top());
        tempStack.pop();
    }
//    std::cout<<"count:\t"<<count<<endl;
}
#endif /* CTCI_03_hpp */
