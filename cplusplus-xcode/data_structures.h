//
//  data_structures.cpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 11/25/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES
#include <vector>
#include <utility>
#include <map>
#include <queue>
template <class T>
struct SinglyLinkedListNode {
    T data;
    struct SinglyLinkedListNode<T> * next;
    //
    SinglyLinkedListNode(const std::vector<T> & data):next(nullptr) {
        SinglyLinkedListNode<T> * p = this;
        if (data.size() > 0)
            this->data = data[0];
        for(int i = 1; i< data.size(); i++) {
            SinglyLinkedListNode<T> * newNode = new SinglyLinkedListNode<T>(data[i],nullptr);
            p->next = newNode;
            p = p->next;
        }
    };
    SinglyLinkedListNode(T d, SinglyLinkedListNode<T> * n): data(d), next(n) {};
    void appendToTail(T data) {
        SinglyLinkedListNode<T> * pointer = this;
        while(pointer->next != nullptr) {
            pointer = pointer->next;
        }
        SinglyLinkedListNode<T> * newNode = new SinglyLinkedListNode<T>(data,nullptr);
        newNode->next = nullptr;
        pointer->next = newNode;
    };
    void appendToTail(const std::vector<T> & data) {
        SinglyLinkedListNode<T> * pointer = this;
        while(pointer->next != nullptr) {
            pointer = pointer->next;
        }
        for(int i = 0; i < data.size(); i++) {
            SinglyLinkedListNode<T> * newNode = new SinglyLinkedListNode<T>(data[i],nullptr);
            newNode->next = nullptr;
            pointer->next = newNode;
            pointer = pointer->next;
        }
    };
};

template <class T>
class BinaryTreeNode {
private:
    int size;
public:
    T data;
    BinaryTreeNode<T> *left,*right,*parent;
    int getSize() {
        return size;
    }
    BinaryTreeNode<T>(T aData): data(aData),left(nullptr),right(nullptr),parent(nullptr),size(1) {};
    void insertToTheLeft(T aData) {
        left = new BinaryTreeNode<T>(aData);
        left->parent = this;
        this->size++;
    };
    void insertToTheRight(T aData) {
        right = new BinaryTreeNode<T>(aData);
        right->parent = this;
        this->size++;
    };
    void insertInOrder(T aData) { //binary search tree simulation
        //T needs to implement operator<=
        if(aData <= data) {
            if(left == nullptr) {
                this->insertToTheLeft(aData);
            }
            else {
                left->insertInOrder(aData);
                size++;
            }
        }
        else {
            if(right == nullptr) {
                this->insertToTheRight(aData);
            }
            else {
                right->insertInOrder(aData);
                size++;
            }
        }
    };
    BinaryTreeNode<T> * find(T aData) {
        if(data == aData) {
            return this;
        }
        else if(aData <= data) {
            if(left == nullptr) {
                return nullptr;
            }
            return left->find(aData);
        }
        else {
            if(right == nullptr) {
                return nullptr;
            }
            return right->find(aData);
        }
    }
    void deleteNode(){
        //TODO: implement size update for this method
        //3 cases
        if(this->left != nullptr && this->right != nullptr) {
            //find in-order successor
            BinaryTreeNode<T> * node = this->right;
            //find left mode node
            while(node->left != nullptr) {
                node = node->left;
            }
            this->data = node->data; //replace content from in-order successor and then recursively delete that fucking node
            node->deleteNode();
        }
        else if(this->left == nullptr && this->right == nullptr) { //it's a leaf
            if(this->data <= this->parent->data) {
                this->parent->left = nullptr;
            }
            else {
                this->parent->right = nullptr;
            }
            delete this;
        }
        else { //has only one child
            BinaryTreeNode * onlyChild;
            if(this->left != nullptr) {
                onlyChild = this->left;
            }
            else {
                onlyChild = this->right;

            }
            this->data = onlyChild->data;
            this->left = onlyChild->left;
            this->right = onlyChild->right;
            delete onlyChild;
            
        }
    }
    BinaryTreeNode<T> * getNthNode(int n) { //should probably be a private method
        //0 to n inclusive
        if(n >= size || n < 0)
            throw exception(); //more than I can chew dawg
        int leftSize = 0;
        if(this->left != nullptr) {
            leftSize = this->left->getSize();
        }
        if(n < leftSize) {
            return this->left->getNthNode(n);
        }
        else if(n == leftSize) {
            return this;
        }
        //else do the following
        return this->right->getNthNode(n-leftSize-1);
        
    }
    BinaryTreeNode<T> * getRandomNode() {
        int n = rand()%size;
        return getNthNode(n);
    }
};
template <class T>
struct MinHeap {
    vector<T>storage;
    int size() {
        return storage.size();
    };
    MinHeap(const vector<T> & initializer){
        for(T element : initializer) {
            this->push_back(element);
        }
    }
    void push_back(T element) {
        storage.push_back(element);
        int indexOfElement = (int)(storage.size()-1);
        while(indexOfElement != 0){
            int indexOfParent = (indexOfElement-1)/2;
            if(storage[indexOfElement] < storage[indexOfParent]){
                std::swap(storage[indexOfParent],storage[indexOfElement]);
                indexOfElement = indexOfParent;
            }
            else {
                break; //no need to check any further
            }
        }
    };
    T pop_back() {
        if(storage.size() == 0) {
            throw exception();//can't do that bro
        }
        T elementToReturn = storage[0];
        storage[0] = *(storage.end()-1);
        storage.pop_back(); //reduce storage size
        int indexOfElement = 0;
        int indexOfLeftChild = 2*indexOfElement+1;
        int indexOfRightChild = 2*indexOfElement+2;
        int smallest = indexOfElement;
        while(indexOfLeftChild < storage.size()){
            if(storage[indexOfLeftChild] < storage[indexOfElement]) {
                smallest = indexOfLeftChild;
            }
            if(indexOfRightChild < storage.size() && storage[indexOfRightChild] < storage[smallest]) {
                smallest = indexOfRightChild;
            }
            if(smallest != indexOfElement) {
                std::swap(storage[indexOfElement],storage[smallest]);
                indexOfElement = smallest;
            }
            else {
                break;
            }
            indexOfLeftChild = 2*indexOfElement+1;
            indexOfRightChild = 2*indexOfElement+2;
        }
        return elementToReturn;
    };
};
template <class T>
class MaxHeap {
private:
    vector<T> storage;
public:
    MaxHeap(const vector<T> &array){
        for(T element : array) {
            this->push_back(element);
        }
    }
    int size() {
        return storage.size();
    }
    void push_back(T element) {
        storage.push_back(element);
        int child = (int)storage.size()-1;
        int parent = (child-1)/2;
        while(child != 0 && storage[parent] < storage[child] ) {
            std::swap(storage[parent],storage[child]);
            child = parent;
            parent = (child-1)/2;
        }
    }
    T pop_back() {
        if(storage.size() == 0) {
            throw exception();
        }
        T elementToReturn = storage[0];
        storage[0] = *(storage.end()-1);
        storage.pop_back();
        int parent = 0;
        int left = 2*parent+1;
        int right = 2*parent+2;
        int biggest = parent; //asumption
        while(left < storage.size()) {
            if(storage[left] > storage[parent]) {
                biggest = left;
            }
            if(right < storage.size() && storage[right] > storage[biggest]) {
                biggest = right;
            }
            if(biggest != parent) {
                std::swap(storage[parent], storage[biggest]);
                parent = biggest;
                left = 2*parent+1;
                right = 2*parent+2;
            }
            else {
                break;
            }
        }
        return elementToReturn;
    }
};
class TrieNode {
private:
    std::map<char, TrieNode *> children; //binary search tree
public:
    bool isAWord = false;
    void addWord(const string & word, int index) {
        int length = (int)word.size();
        if(index >= length)
            throw exception(); //you fucked up somewhere so check your shit dawg
        char c = word[index];
        if(children.count(c) == 0) {
            children[c] = new TrieNode();
        }
        TrieNode * child = children[c];
        if(index == (length-1)) {
            child->isAWord = true;
        }
        else {
            child->addWord(word, index+1); //you can avoid this recursion bro
        }
    }
    TrieNode * getChild(char c) {
        if(children.count(c) == 0) {
            return nullptr;
        }
        return children[c];
    }
    
};
class Trie {
private:
    TrieNode root;
public:
    Trie(const vector<string> & words) {
        for(string word : words) {
            root.addWord(word, 0);
        }
    }
    bool containsPrefix(const string & prefix) {
        if(prefix.size() == 0)
            return false;
        TrieNode * node = &root;
        for(int i = 0; i < prefix.size(); i++) {
            node = node->getChild(prefix[i]);
            if(node == nullptr) {
                return false;
            }
        }
        return true;
    }
    bool containsWord(const string & word) {
        if(word.size() == 0)
            return false;
        TrieNode * node = &root;
        for(int i = 0; i < word.size(); i++) {
            node = node->getChild(word[i]);
            if(node == nullptr) {
                return false;
            }
        }
        
        return node->isAWord;
    }
};
//directed graph with no weight
class GraphNoWeight {
private:
    int size;
    std::vector<std::list<int>> adjacencyList;
public:
    GraphNoWeight(int aSize):size(aSize){
        adjacencyList.resize(aSize);
    };
    void addEdge(int source, int destination){
        if(source < 0 || source >= size || destination < 0 || destination >= size)
            throw exception(); //why dude?
        adjacencyList[source].push_back(destination);
    }
    void printTopologicalOrder() {
        vector<int> inDegrees(size,0); //initialize everything to zero, O(V) space
        for(std::list<int> list : adjacencyList) { // O(V+E) time complexity
            for(int node : list) {
                inDegrees[node]++;
            }
        }
        std::queue<int> queueNode;
        vector<int> topologicalOrder;
        int count = 0;
        for(int i = 0; i <inDegrees.size(); i++) {
            if(inDegrees[i] == 0) {
                queueNode.push(i); //add to queue
                topologicalOrder.push_back(i);
                count++;
            }
        }
        while(!queueNode.empty()) {
            int node = queueNode.front();
            queueNode.pop();
            for(int adjacentNode : adjacencyList[node]) {
                inDegrees[adjacentNode]--;
                if(inDegrees[adjacentNode] == 0) {
                    queueNode.push(adjacentNode);
                    topologicalOrder.push_back(adjacentNode);
                    count++;
                }
            }
        }
        if(count != size) {
            std::cout<<"Can't evaluate the topological order, presence of a cycle"<<std::endl;
        }
        else {
            for(int node : topologicalOrder) {
                std::cout<<node<<"\t";
            }
            std::cout<<std::endl;
        }
    }
    
};
#endif
