//
//  CTCI-04.h
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 11/30/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_10_h
#define CTCI_10_h
#include <vector>
#include <string>
#include <unordered_map>
//10.1
template <class T>
void sortedMerge(std::vector<T>& a, int lastA, std::vector<T>& b, int lastB) {
    int indexA = lastA-1;
    int indexB = lastB-1;
    int indexOfMerge = lastA + lastB - 1; //last index of merge
    while(indexB >= 0) {
        if(indexA >= 0 && a[indexA] > b[indexB]) { //in case we copy all of a before running out of b, important condition!!!
            a[indexOfMerge] = a[indexA];
            indexA--;
        }
        else {
            a[indexOfMerge] = b[indexB];
            indexB--;
        }
        indexOfMerge--;
    }
    //no need to copy the rest of A since it already occupies the lower ranges in a sorted way
}
//10.2
bool comparatorStringAnagram(string s1, string s2){
//    std::cout<<"Comparing: \t"<<s1<<" and\t"<<s2<<endl;
    std::sort(s1.begin(),s1.end());
    std::sort(s2.begin(),s2.end());
    //most definitely check this out: http://www.cplusplus.com/reference/string/string/compare/
    int comparison = s1.compare(s2);
//    std::cout<<comparison<<endl;
    return comparison;
}
void sortGroupAnagramArray1(std::vector<string> &arrayOfString) {
    std::sort(arrayOfString.begin(),arrayOfString.end(),comparatorStringAnagram);
}
void sortGroupAnagramArray2(std::vector<string> &arrayOfString) {
    std::unordered_map<string, std::vector<string>> map;
    for(string s: arrayOfString) {
        string copy = s;
        std::sort(copy.begin(),copy.end());
        map[copy].push_back(s);
    }
    int index = 0;
    for(auto element: map) {
        for(string s: element.second) {//second corresponds to value, first would be the key
            if(index == arrayOfString.size())
                throw exception(); //this should have never happened
            arrayOfString[index++] = s;
        }
    }
}
//10.3
template <class T>
int searchInRotatedArrayHelper(const std::vector<T> &array, int low, int high, T element) {
    if(high < low)
        return -1;
    int middle = (low + high)/2;
    if(array[middle] == element)
        return middle; //and we are done :)
    if(array[low] < array[middle]) {
        //left is normally ordered
        if(element >= array[low] && element < array[middle]) {
            //this means that we can search through this range
            return searchInRotatedArrayHelper(array, low, middle-1, element);
        }
        else{
            //search the other half
            return searchInRotatedArrayHelper(array, middle+1, high, element);
        }
    }
    else if (array[low] > array[middle]){
        //right is normally ordered
        if(element > array[middle] && element <= array[high]) {
            //this means that we can search through this range
            return searchInRotatedArrayHelper(array, middle+1,high, element);
        }
        else{
            //search the other half
            return searchInRotatedArrayHelper(array, low, middle-1, element);
        }
    }
    else if(array[low] == array[middle]) {
        if(array[middle] != array[high]) {
            return searchInRotatedArrayHelper(array, middle+1, high, element);
        }
        else {
            //search through both sides if necessary
            int index = searchInRotatedArrayHelper(array, low, middle-1, element);
            if(index == -1) {
                //nothing there so check right side
                return searchInRotatedArrayHelper(array, middle+1, low, element);
            }
            else return index;
        }
    }
    return -1;
}
template <class T>
int searchInRotatedArray(const std::vector<T> &array, T element) { //we return the index
    if(array.size()==0)
        return -1; //empty
    return searchInRotatedArrayHelper(array, 0, int(array.size()-1), element);
}
//10.4
template <class T>
class Listy{
private:
    std::vector<T> internal;
public:
    Listy(const std::vector<T> &source);
    T elementAt(int i) const; //const is for const objects. we can't really modify constant objects so we got to mark it to make the compiler happy
};
template <class T>
Listy<T>::Listy(const std::vector<T> &source) {
    internal.insert(internal.end(),source.begin(),source.end());
}
template <class T>
T Listy<T>::elementAt(int i) const {
    if(i >= internal.size())
        return (T)(-1); //this implifies that listy has to be negative otherwise returning -1 would not make any sort of sense
    return internal[i];
}

template <class T>
int findBoundOfTheListyUsingReverseBinarySearch(const Listy<T>& listy, T element) {
    int index = 1;
    while(listy.elementAt(index) < element && listy.elementAt(index) != -1) {
        index <<= 1; //multiply by 2
    }
    return index;
}
template <class T>
int sortedSearchNoSize(const Listy<T>& listy, T element) {
    int high = findBoundOfTheListyUsingReverseBinarySearch(listy, element);
    int low = 0;
    int middle;
    while (low <= high) {
        middle = (low + high)/2;
        if(listy.elementAt(middle) == element) {
            return middle;
        }
        else if(listy.elementAt(middle) > element || listy.elementAt(middle) == -1) {
            high = middle-1;
        }
        else if(listy.elementAt(middle) < element && listy.elementAt(middle) != -1) {
            low = middle+1;
        }
    }
    return -1;
}
//10.7
//int num = INT_MAX;
//10.8
void findDuplicates(const vector<int> & array, int upperLimit) {
    int bitSetSize = (upperLimit-1)+1;
    vector<unsigned char> bitVector(bitSetSize/8,0);
    for(int n : array) {
        int bitOffset = (n-1) % 8;
        if(bitVector[(n-1)/8] & (1<<bitOffset))
            std::cout<<"found duplicate:\t"<<n<<endl;
        else {
            bitVector[(n-1)/8] |= (1<<bitOffset);
        }
    }
}
#endif /* CTCI_10_h */
