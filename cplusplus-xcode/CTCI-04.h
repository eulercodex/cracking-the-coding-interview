//
//  CTCI-04.h
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 12/7/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_04_h
#define CTCI_04_h

#include <vector>
#include <queue>

//misc
template <class T>
void maxHeapifyBottomUpHelper(vector<T> & array, int root) {
    int left = 2*root+1;
    if(left >= array.size()) {
        return; //root is tree leaf
    }
    int right = 2*root+2;
    int biggest = root;
    if(array[left] > array[biggest]) {
        biggest = left;
    }
    if(right < array.size() && array[right] > array[biggest]) {
        biggest = right;
    }
    if(biggest == root) {
        return; //no need to heapify subtrees
    }
    else {
        std::swap(array[root], array[biggest]);
        maxHeapifyBottomUpHelper(array, biggest); //fix any and all broken heap property recursively
    }
}
template <class T>
void maxHeapifyBottomUp(vector<T> & array) {
    if(array.size() == 0) {
        return;
    }
    for(int root = (int)(array.size()-2)/2; root >= 0; root--) {
        maxHeapifyBottomUpHelper(array, root);
    }
}

//4.1
enum State {
    unvisited,
    visiting,
    visited
};
template <class T>
struct GraphNode1 {
    State state;
    std::vector<GraphNode1<T>*> children;
};
template <class T>
struct Graph1 {
    std::vector<GraphNode1<T>> nodes;
};
template <class T>
bool search1(Graph1<T> &graph,const GraphNode1<T> &start,GraphNode1<T> &end) {
    
}
//4.2
template <class T>
void minimalTreeHelper(BinaryTreeNode<T> *& node, const std::vector<T> & array, int low, int high, BinaryTreeNode<T> * parent = nullptr) {
    if(high < low) return;
    int middle = (low+high)/2;
    if(node == nullptr) {
        node = new BinaryTreeNode<T>(array[middle]);
        node->parent = parent;
    }
    else {
        node->data = array[middle];
    }
    minimalTreeHelper(node->left,array,low,middle-1,node);
    minimalTreeHelper(node->right,array,middle+1,high,node);
}
template <class T>
BinaryTreeNode<T> * minimalTree(const std::vector<T> &sortedArray) {
    //assume that the array is sorted
    if(sortedArray.size() == 0) {
        return nullptr;
    }
    BinaryTreeNode<T> * bst = nullptr;
    
    minimalTreeHelper(bst, sortedArray, 0, (int)sortedArray.size()-1);
    return bst;
}
//4.3
template <class T>
std::vector<BinaryTreeNode<T>*> listOfDepths(BinaryTreeNode<T> * root) {
    //modified BFS
    std::vector<std::vector<BinaryTreeNode<T>*>> depths;
    if(root != nullptr) {
        depths.push_back(vector<BinaryTreeNode<T>*>(root));
    }
    else {
        return depths; //empty vector of vectors
    }
    int i = 0;
    while(i < depths.size()) {
        for(BinaryTreeNode<T> * child: depths[i]) {
            vector<BinaryTreeNode<T> *> aDepth;
            if(child->left != nullptr) {
                aDepth.push_back(child->left);
            }
            if(child->right != nullptr) {
                aDepth.push_back(child->right);
            }
            if(aDepth.size() > 0)
                depths.push_back(aDepth);
        }
        i++;
    }
    return depths;
}
//4.4
template <class T>
int balancedHelper(BinaryTreeNode<T> * node, bool & flag) {
    if(!flag) {
        return INT_MIN;//could be any number actually. no need to compute the mess below. just go up the stack
    }
    if(node == nullptr)
        return -1;
    int left = balancedHelper(node->left, flag);
    int right = balancedHelper(node->right, flag);
    if(std::abs(left-right) > 1) {
        flag = false;
    }
    return std::max(left,right)+1;
}
template <class T>
bool balanced(BinaryTreeNode<T> * root) {
    if(root == nullptr) {
        return true;
    }
    bool flag = true;
    balancedHelper(root,flag);
    return flag;
}
//4.5
template <class T>
struct DataType {
    T data;
    bool undefined = true;
    DataType(){};
    DataType(T aData):data(aData),undefined(false){};
    bool operator >=(const T &right) {
        return this->data >= right;
    }
    bool operator <(const T &right) {
        return this->data < right;
    }
};
template <class T>
bool validateBinarySearchTreeHelper(BinaryTreeNode<T> * node, DataType<T> min, DataType<T> max) {
    if(node == nullptr) {
        return true;
    }
    if((!min.undefined && min >= node->data) || (!max.undefined && max < node->data)) {
        return false;
    }
    bool left = validateBinarySearchTreeHelper(node->left, min, DataType<T>(node->data));
    bool right = validateBinarySearchTreeHelper(node->right, DataType<T>(node->data), max);
    return left && right;
}
template<class T>
bool validateBinarySearchTree(BinaryTreeNode<T> * root) {
    if(root == nullptr) {
        return true;
    }
    return validateBinarySearchTreeHelper(root, DataType<T>(), DataType<T>());
}
//4.6
template <class T>
BinaryTreeNode<T> * successor(BinaryTreeNode<T> * node) {
    if(node == nullptr)
        return nullptr;
    if(node->right != nullptr) {
        //find leftmost child in the right subtree
        node = node->right;
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    BinaryTreeNode<T> * child = node;
    BinaryTreeNode<T> * parent = child->parent;
    while(parent != nullptr && parent->left != child) {//we want child to be on the left of parent
        child = parent;
        parent = child->parent;
    }
    return parent; //this can be nullptr
}
//4.7 solved in the GraphNoWeight class
//4.8
template <class T>
bool firstCommonAncestor1Helper(BinaryTreeNode<T> * root, BinaryTreeNode<T> * node, vector<BinaryTreeNode<T>*> &path) {
    if(root == nullptr || node == nullptr) { //checking for nodes is overkill for this problem
        return false;
    }
    if(root == node) {
        path.push_back(root);
        return true;
    }
    
    if(firstCommonAncestor1Helper(root->left, node, path) || firstCommonAncestor1Helper(root->right, node, path)) {
        path.push_back(root);
        return true;
    }
    return false;
}
template <class T>
BinaryTreeNode<T> * firstCommonAncestor1(BinaryTreeNode<T> * root, BinaryTreeNode<T> * node1, BinaryTreeNode<T> * node2) {
    //alternative solution when we know the nodes are present in the tree: http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
    if(root == nullptr || node1 == nullptr || node2 == nullptr) {
        return nullptr; //bruh really? why are you wasting my time?
    }
    if(node1 == node2) {
        return node1;//i think?
    }
    vector<BinaryTreeNode<T>*> pathToNode1;
    if(!firstCommonAncestor1Helper(root, node1, pathToNode1)) {
        return nullptr; //couldn't even find that node dawg
    }
    vector<BinaryTreeNode<T>*> pathToNode2;
    if(!firstCommonAncestor1Helper(root, node2, pathToNode2)) {
        return nullptr; //couldn't even find that node dawg
    }
    BinaryTreeNode<T> * firstCommonAncestor = nullptr;
    while((pathToNode1.size() > 0 && pathToNode2.size() > 0) && pathToNode1.back() == pathToNode2.back()) { //not sure if checking the size helps
        firstCommonAncestor = pathToNode1.back(); //can use the other vector as well, duh!
        pathToNode1.pop_back();
        pathToNode2.pop_back();
    }
    return firstCommonAncestor;
}
//4.9
void bstSequenceWeaveHelper(vector<int> &left, int indexLeft,vector<int> &right,int indexRight,vector<int> &prefix,vector<vector<int>> &sequence) {
    //deal with left first
    if(indexLeft == left.size()) {
        for(int i = indexRight; i <right.size(); i++) {
            prefix.push_back(right[i]);
        }
        sequence.push_back(prefix);
        return;
    }
    if(indexRight == right.size()) {
        for(int i = indexLeft; i <left.size(); i++) {
            prefix.push_back(left[i]);
        }
        sequence.push_back(prefix);
        return;
    }
    vector<int>prefixLeft(prefix);
    prefixLeft.push_back(left[indexLeft]);
    bstSequenceWeaveHelper(left, indexLeft+1, right, indexRight, prefixLeft, sequence);
    vector<int>prefixRight(prefix);
    prefixRight.push_back(right[indexRight]);
    bstSequenceWeaveHelper(left, indexLeft, right, indexRight+1, prefixRight, sequence);
}
vector<vector<int>> bstSequenceHelper(BinaryTreeNode<int> * node) {
    //divide and conquer
    if(node == nullptr) {
        return vector<vector<int>>(1,vector<int>());
    }
    if(node->left == nullptr && node->right == nullptr) {
        return vector<vector<int>>(1,vector<int>({node->data}));
    }
    vector<vector<int>> leftSequence = bstSequenceHelper(node->left);
    vector<vector<int>> rightSequence = bstSequenceHelper(node->right);
    vector<vector<int>> sequence;
    for(vector<int> left : leftSequence) {
        for(vector<int> right: rightSequence) {
            vector<int>prefix;
            prefix.push_back(node->data);
            bstSequenceWeaveHelper(left, 0, right, 0, prefix, sequence);
        }
    }
    return sequence;
    
}
vector<vector<int>> bstSequence(BinaryTreeNode<int> * root) {
    return bstSequenceHelper(root);
}
//4.10
template <class T>
bool areIdentical(BinaryTreeNode<T> * node1, BinaryTreeNode<T> * node2) {
    if(node1 == nullptr && node2 == nullptr) {
        return true;
    }
    if(node1 == nullptr || node2 == nullptr) {
        return false;
    }
    if(node1->data == node2->data && areIdentical(node1->left, node2->left) && areIdentical(node1->right, node2->right)) {
        return true;
    }
    return false;
}
template <class T>
bool checkSubtree(BinaryTreeNode<T> * T1, BinaryTreeNode<T> * T2) {
    if(T2 == nullptr) {
        return true; //always a subtree
    }
    if(T1 == nullptr) {
        return false; //since T2 not null, we return false
    }
    //check that they're identical
    if(areIdentical(T1, T2)) {
        return true;
    }
    //recursively check the children of T1
    if(checkSubtree(T1->left, T2) || checkSubtree(T1->right, T2)) {
        return true;
    }
    return false;
}
//4.11---check BinaryTreeNode data structure and look for getRandomNode() getNthNode()
//4.12
int pathsWithSumFromNode1(BinaryTreeNode<int> * root, int targetSum, int sum){
    if(root == nullptr) {
        return 0;
    }
    sum += root->data;
    int total = (sum == targetSum) ? 1 : 0;
    int left = pathsWithSumFromNode1(root->left, targetSum, sum);
    int right = pathsWithSumFromNode1(root->right, targetSum, sum);
    total += left + right;
    return total;
}
int pathsWithSum1(BinaryTreeNode<int> * root, int targetSum) { //O(nlogn) solution
    if(root == nullptr) {
        return 0;
    }
    int pathsWithSumFromRoot = pathsWithSumFromNode1(root, targetSum, 0); //start counting from root
    int pathsWithSumFromLeft = pathsWithSumFromNode1(root->left, targetSum, 0);
    int pathsWithSumFromRight = pathsWithSumFromNode1(root->right, targetSum, 0);
    
    return pathsWithSumFromRoot+pathsWithSumFromLeft+pathsWithSumFromRight;
}
int pathsWithSum2Helper(BinaryTreeNode<int> * root, int targetSum, std::unordered_map<int,int> &map, int runningSum) {
    if(root == nullptr) {
        return 0;
    }
    runningSum += root->data;
    bool runningSumExists = map.count(runningSum) > 0;
    if(runningSumExists) {
        map[runningSum]++;
    }
    else map[runningSum] = 1;
    int totalForThisNode;
    if(runningSum == targetSum) {
        totalForThisNode = 1;
    }
    else if(map.count(runningSum - targetSum) > 0) {
        totalForThisNode = map[runningSum - targetSum];
    }
    else {
        totalForThisNode = 0;
    }
    int left = pathsWithSum2Helper(root->left,targetSum,map,runningSum);
    int right = pathsWithSum2Helper(root->right,targetSum,map,runningSum);
    if(runningSumExists) {
        map[runningSum]--;
    }
    else {
        map.erase(runningSum);
    }
    return totalForThisNode+left+right;    
}
int pathsWithSum2(BinaryTreeNode<int> * root, int targetSum) {
    if(root == nullptr) {
        return 0;
    }
    std::unordered_map<int,int> map;
    return pathsWithSum2Helper(root, targetSum, map, 0);
}

#endif /* CTCI_04_h */
