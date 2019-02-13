//
//  main.cpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/4/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#include <iostream>
#include "ArrayList.hpp"
#include "Stack.cpp"
#include "HashTable.hpp"
#include "Stringbuiler.hpp"
#include "ArrayList.hpp"
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include "CTCI-01.h"
#include "CTCI-02.h"
#include "CTCI-03.h"
#include "CTCI-04.h"
#include "CTCI-08.h"
#include "CTCI-10.h"
#include "CTCI-16.h"
#include "extra.h"
#include "data_structures.h"

using namespace std;

template <class T>
struct TreeNode {
    T data;
    TreeNode<T> * left = nullptr;
    TreeNode<T> * right = nullptr;
};

string joinWords(string array[],size_t length) {
    Stringbuilder builder;
    for (int i = 0; i < length; i++) {
        builder.append(array[i]);
    }
    return builder.toString();
}
// A utility function to get maximum value in arr[]
int getMax(vector<int> arr)
{
    int mx = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(vector<int> &arr, int exp)
{
    int n = (int)arr.size();
    vector<int> output(n); // output array
    int i, count[10] = {0};
    
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
    
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(vector<int>arr)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr);
    
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, exp);
}

int random(int k);

vector<int> createPermutedArray(int n)
{
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = i;
    for(int i = 0; i < n - 1; i++)
    {
        int j = i + random(n - i);
        swap(a[i], a[j]);
    }
    return a;
}

int random(int k)
{
    double r = random(); // [0..1)
    return r * k;
}
template <int N>
void printGrid(int (&grid)[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

int main(/*int argc, const char * argv[]*/) {
    /*
    ArrayList<int> array(6);
    array[0] = 0;
    array[1] = 10;
    array[2] = 20;
    array[3] = 30;
    array.push_back(70);
    for (int i = 0; i < array.length(); i++) {
        cout << array[i] <<"\t";
    }
    cout << "\nArray length: " << array.length()<<"\n";
    cout << "\nArray capacity: " << array.capacity()<<"\n";
    // insert code here...
    cout << "Hello, World!\n";
    string s = "a string";
    char * charArray = new char[s.length()+1];
    strcpy(charArray, s.data()); //s.c_str()
    charArray[0] = '1';
    cout << charArray<<"\n";
    cout << s <<"\n";
    string s2(charArray);
    cout <<"the new allocated string: " + s2+"\n";
    Stack<int> stack;
    for (int i = 0; i < 5; i++) {
        stack.push(i);
    }
    for (int i = 0; i < 5; i++) {
        cout << stack.top() <<"\t";
        stack.pop();
    }
    cout<<"\n";
    HashTable<string, int> map;
    map["1"] = 12345;
    cout << map["1"]<<"\n";
    string words[5] = {"ab","cd","efg","h","ijk"};
    string result = joinWords(words, 5);
    cout <<result+"\n";
    int x = 5;
    int &r = x;
    int *p = &r;
    r = 7;
    cout<<"pointer address: "<<(&x+1)<<", reference address: "<<p<<"\n";
    int * r1 = new int[2,0];
    int r2 = *r1;
    cout<<(*r1==r2)<<"\n";
    cout<<(typeid(ArrayList<int>)==typeid(array))<<"\n";
    vector<int>mm = {1,2,3};
     */
    vector<int>arr= {170, 45, 75, 90, 802, 24, 2, 66};
    radixsort(arr);
    TreeNode<int> node;
    node.data = 10;
    node.left = new TreeNode<int>;
    node.left->data = 2;
    node.right = new TreeNode<int>;
    vector<Point>path;
    findPath({{1,1,1,1,1},{1,1,1,0,1},{1,1,1,0,1},{1,1,1,0,1},{1,1,1,0,1}}, {0,0}, {4,4},path);
    vector<int> set = {1,2,3};
    vector<vector<int>> allSubsets = getSubsets(set);
    recursiveMultiply(3, 3);
    towerOfHanoi(3);
    parens(3);
    isUnique1("absertpyihp");
    isUnique2("absertpyihp");
    isUnique3("absertpyihp");
    checkPermutation("abcde", "dabcf");
    string s = "Mr John Smith    ";
    URLify(s, 13);
    oneAway("pale", "ple");
    oneAway("pales", "pale");
    oneAway("pale", "bale");
    oneAway("pale", "bake");
    cout<<stringCompression("aabcccccaaa")<<endl;
    int matrix[][3] = {{1,2,3},{4,5,6},{7,8,9}};
    rotateMatrixClockwise(matrix);
    int matrix2[4][3] = {{1,2,3},{4,0,6},{7,8,0},{7,8,9}};
    zeroMatrix(matrix2);
    SinglyLinkedListNode<int> node1 = SinglyLinkedListNode<int>(1,nullptr);
    node1.appendToTail(2), node1.appendToTail(3), node1.appendToTail(2), node1.appendToTail(3);
    removeDups1(&node1);
    SinglyLinkedListNode<int> * node2 = new SinglyLinkedListNode<int>(1,nullptr);
    node2->appendToTail(2), node2->appendToTail(3), node2->appendToTail(2), node2->appendToTail(3);
    removeDups2(node2);
    SinglyLinkedListNode<int> * node3 = new SinglyLinkedListNode<int>(1,nullptr);
    node3->appendToTail(2), node3->appendToTail(3), node3->appendToTail(4), node3->appendToTail(5); //1->2->3->4->5
    returnKthToLast(node3, 2);
    SinglyLinkedListNode<int> node4(1,nullptr);
    node4.appendToTail(2);node4.appendToTail(3);node4.appendToTail(4); //1->2->3->4
    deleteMiddleNode(node4.next->next);
    SinglyLinkedListNode<int> node5(3,nullptr);node5.appendToTail(5);node5.appendToTail(8);node5.appendToTail(5);node5.appendToTail(10);node5.appendToTail(2);node5.appendToTail(1); //3->5->8->5->10->2->1
    partition(&node5,5);
    SinglyLinkedListNode<int> a({7,1,6});
    SinglyLinkedListNode<int> b({5,9,2});
    sumLists1(&a, &b);
    SinglyLinkedListNode<int> c({1,2,2,3,2,2,1});
    palindrome(&c);
    SinglyLinkedListNode<int> e({1,2,3,4});
    SinglyLinkedListNode<int> f({2,3});
    SinglyLinkedListNode<int> d({1,2,4,5,6,7,7});
    e.next->next->next->next = &d;
    f.next->next = &d;
    intersection(&e, &f);
    SinglyLinkedListNode<int> g({1,2,3,4,5});
    g.next->next->next->next->next = g.next->next;
    loopDetection(&g);
    //3
    StackWithMin<int> aStackWithMin;
    SetOfStacks<int> stackOfStacks(2);
    stackOfStacks.push(5);cout<<stackOfStacks.top()<<"\t"<<stackOfStacks.empty()<<endl;
    stackOfStacks.push(4);cout<<stackOfStacks.top()<<"\t"<<stackOfStacks.empty()<<endl;
    stackOfStacks.push(3);cout<<stackOfStacks.top()<<"\t"<<stackOfStacks.empty()<<endl;
    stackOfStacks.pop();cout<<stackOfStacks.top()<<"\t"<<stackOfStacks.empty()<<endl;
    QueueViaStacks<int> queueViaStacks;
    cout<<queueViaStacks.empty()<<endl;
    queueViaStacks.push(1);cout<<queueViaStacks.front()<<"\t"<<queueViaStacks.empty()<<endl;
    queueViaStacks.push(2);cout<<queueViaStacks.front()<<"\t"<<queueViaStacks.empty()<<endl;
    queueViaStacks.push(3);cout<<queueViaStacks.front()<<"\t"<<queueViaStacks.empty()<<endl;
    queueViaStacks.pop();cout<<queueViaStacks.front()<<"\t"<<queueViaStacks.empty()<<endl;
    stack<int> aStackToSort; aStackToSort.push(1);aStackToSort.push(2);aStackToSort.push(3);aStackToSort.push(4);aStackToSort.push(5);
    sortStack(aStackToSort);
    //10
    vector<int> largeSortedVector = {1,3,5,7,0,0,0,0};
    vector<int> smallSortedVector = {2,4,6,7};
    sortedMerge(largeSortedVector, 4, smallSortedVector, 4);
    vector<string> someArrayOfStringAnagram1={"abc","bca","dh","dhe","hd","cab"};
    vector<string> someArrayOfStringAnagram2={"abc","bca","dh","cab","dhe","hd"};
    sortGroupAnagramArray1(someArrayOfStringAnagram1);
    sortGroupAnagramArray2(someArrayOfStringAnagram2);
    vector<int> rotatedSortedArray = {15,16,19,20,25,1,3,4,5,7,10,14};
    searchInRotatedArray(rotatedSortedArray, 5);
    int index = sortedSearchNoSize(Listy<int>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}),15);
    findDuplicates({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,2,5,8,9,16,17},17);
    vector<SinglyLinkedListNode<int> *> adjacentList;
    //4
    MaxHeap<int> blah({3,2,1,7,8,4,10,16,12});
    vector<int>somedopearray={3,2,1,7,8,4,10,16,12};
    maxHeapifyBottomUp(somedopearray);
    Trie trie({"the", "a", "there", "answer", "any",
        "by", "bye", "their"});
    cout <<trie.containsWord("answer")<<endl;
    cout <<trie.containsPrefix("ans")<<endl;
    BinaryTreeNode<int> bst(1);
    bst.insertInOrder(0);
    bst.insertInOrder(3);
    bst.insertInOrder(-1);
    bst.deleteNode();
    bst.deleteNode();
    bst.deleteNode();
    BinaryTreeNode<int> * bstMinimal = minimalTree(vector<int>({1,2,3,4,5}));
    BinaryTreeNode<int> bstBalanced(1);
    bstBalanced.insertInOrder(0);bstBalanced.insertInOrder(-1);bstBalanced.insertInOrder(3);bstBalanced.insertInOrder(5);
    balanced(&bstBalanced);
    balanced(bstMinimal);
    validateBinarySearchTree(bstMinimal);
    BinaryTreeNode<int> * bstnode = successor(bstMinimal->left->right);
    GraphNoWeight topologicalOrderGraph(6);
    topologicalOrderGraph.addEdge(5, 2);
    topologicalOrderGraph.addEdge(5, 0);
    topologicalOrderGraph.addEdge(4, 0);
    topologicalOrderGraph.addEdge(4, 1);
    topologicalOrderGraph.addEdge(2, 3);
    topologicalOrderGraph.addEdge(3, 1);
    cout << "Following is a Topological Sort of\n";
    topologicalOrderGraph.printTopologicalOrder();
    BinaryTreeNode<int> * root = new BinaryTreeNode<int>(1);
    root->insertToTheLeft(2);
    root->insertToTheRight(3);
    root->left->insertToTheLeft(4);
    root->left->insertToTheRight(5);
    root->right->insertToTheLeft(6);
    root->right->insertToTheRight(7);
    firstCommonAncestor1(root, root->left, root->left->left);
    //4.9
    BinaryTreeNode<int> * rootForBSTSequence = new BinaryTreeNode<int>(3);
    rootForBSTSequence->insertToTheLeft(1);
    rootForBSTSequence->insertToTheRight(4);
    rootForBSTSequence->left->insertToTheRight(2);
    vector<vector<int>>bstSequences = bstSequenceHelper(rootForBSTSequence);
    //4.10 too lazy to verify if it works
    //4.11
    BinaryTreeNode<int> someRandBst(4);
    for(int i : {2,1,3,6,5,7}) {
        someRandBst.insertInOrder(i);
    }
    std::cout <<someRandBst.getNthNode(0)->data<<endl;
    std::cout <<someRandBst.getNthNode(1)->data<<endl;
    std::cout <<someRandBst.getNthNode(2)->data<<endl;
    std::cout <<someRandBst.getNthNode(3)->data<<endl;
    std::cout <<someRandBst.getNthNode(4)->data<<endl;
    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        someRandBst.getRandomNode();
    }
    //4.12
    BinaryTreeNode<int> pathWithSums(10);
    pathWithSums.left = new BinaryTreeNode<int>(5);
    pathWithSums.right = new BinaryTreeNode<int>(-3);
    pathWithSums.left->left = new BinaryTreeNode<int>(3);
    pathWithSums.left->right = new BinaryTreeNode<int>(2);
    pathWithSums.right->right = new BinaryTreeNode<int>(11);
    pathWithSums.left->left->left = new BinaryTreeNode<int>(3);
    pathWithSums.left->left->right = new BinaryTreeNode<int>(-2);
    pathWithSums.left->right->right = new BinaryTreeNode<int>(1);
    int targetSum = 18;
    pathsWithSum1(&pathWithSums, targetSum);
    pathsWithSum2(&pathWithSums, targetSum);
    cout<<factorialZeros(20)<<endl;
    GraphWithWeight ggg(1);
    dijkstra(ggg, 0);
    int grid[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };
    if (solveSudoku(grid) == true)
        printGrid(grid);
    else
        printf("No solution exists");
    cout << "verify sudoku: " << verifySudoku(grid) << endl;
    return 0;
}
