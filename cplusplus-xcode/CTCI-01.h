//
//  CTCI-1.cpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 11/24/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//
#ifndef CTCI_01
#define CTCI_01
#include <vector>
#include <deque>
#include <unordered_map>
#include <string>


using namespace std;

//1.1
bool isLessThan(char a, char b) { //comparator
    return (a<b);
}
bool isUnique1(string aString) { //time: O(log n) space: O(log n) if quicksort or O(n) is mergesort
    
    std::sort(aString.begin(),aString.end(), isLessThan); //if quicksort, it has O(log n) space
    for (int i = 1; i <aString.size(); i++) {
        if(aString[i] == aString[i-1])
            return false;
    }
    return true;
}
bool isUnique2(string aString) {
    //assume ASCII string
    //if(aString.size() > 256) return false; //well, we dont even have that many characters :D
    //deque<bool> map(256,false); //can't use vector because it stores bools using 1 bit internally
    vector<bool> map(256);
    for (int i = 0; i < aString.size(); i++) {
        if(map[aString[i]]) //we already visited this site
            return false;
        else map[aString[i]] = true; //found a new character
    }
    return true;
}
char toLowerCase(char c) {
    if( c>='A' && c<='Z') {
        return (c-('A'-'a'));
    }
    return c;
}
bool isUnique3(string aString) {
    //let's consider only words in the alphabet and map the 26 less significant bit to each word in the english alphabet
    int map = 0;//nothing has been added
    for (int i = 0; i < aString.size(); i++) {
        int bit = toLowerCase(aString[i])-'a'; //map a to bit 0, b to bit 1 and so on
        if ((map & 1 << bit) != 0)
            return false; //oh oh it's already been set
        else map = (map | 1 << bit); //set that bit 1
    }
    return true;
}
//1.2
bool checkPermutation (const string &s1, const string &s2) {
    if(s1.size() != s2.size()) return false;
    std::unordered_map<char,int> map;
    for(int i = 0; i < s1.size(); i++) {
        if(map.find(s1[i]) == map.end()) //alternatively map.count[s1[i]] == 0, no need for iterators
            map[s1[i]] = 1;
        else map[s1[i]]++;
    }
    for(int i = 0; i < s2.size(); i++) {
        if(map.find(s2[i]) == map.end())
            return false;
        else {
            map[s2[i]]--;
            if(map[s2[i]] < 0) {
                return false;
            }
        }
    }
    return true;
}
//1.3
bool URLify(string &s, int trueLength) {
    //count number of space
    int numberOfSpaces = 0;
    for (int i = 0; i < trueLength; i++) {
        if (s[i] == ' ')
            numberOfSpaces++;
    }
    int spaceNeeded = trueLength + numberOfSpaces * 2;
    if(s.size() < spaceNeeded)
        return false; //not enough space. cant edit. whatever
    for(int i = trueLength-1; i >= 0; i--) {
        if(s[i] == ' ') {
            s[--spaceNeeded] = '0';
            s[--spaceNeeded] = '2';
            s[--spaceNeeded] = '%';
        }
        else {
            s[--spaceNeeded] = s[i];
        }
    }
    return true;
}
//1.5
bool weCanReplaceOnlyOneCharacter(string s1, string s2) {
    bool foundAMismatch = false;
    for (int i = 0; i < s1.size(); i++) {
        if(s1[i] != s2[i]) {
            if(foundAMismatch) return false;
            else foundAMismatch = !foundAMismatch;
        }
    }
    return true;
}
bool weCanRemoveOnlyOneCharacter(string s1, string s2) { //assumes s1 is bigger
    bool foundAMismatch = false;
    for (int i = 0,j = 0; i < s1.size() && j < s2.size(); i++, j++) {
        if(s1[i] != s2[j]) {
            if(foundAMismatch) return false;
            else {
                foundAMismatch = !foundAMismatch;
                i++;
            }
        }
    }
    return true;
}
bool oneAway(string s1, string s2) {
    if(s1.size() > (s2.size()+1) || s1.size() < (s2.size()-1)) return false;
    if(s1.size() == s2.size())
        return weCanReplaceOnlyOneCharacter(s1,s2);
    if(s1.size() > s2.size())
        return weCanRemoveOnlyOneCharacter(s1, s2);
    else return weCanRemoveOnlyOneCharacter(s2, s1); //we can insert a character in s1
    //    return true;
}
//1.6
string stringCompression(string s) {
    size_t size = s.size();
    if (size <= 2) return s; //need to readjust the condition
    vector<char> result;
    result.push_back(s[0]);
    int count = 1;
    for(int i = 1; i < size; i++) {
        if(s[i-1]==s[i]) count++;
        else {
            result.push_back('0'+count);
            count = 1;
            result.push_back(s[i]);
        }
        if (result.size() > size) return s; //compress only when compressed size is less
    }
    result.push_back('0'+count);
    if (result.size() > size) return s;
    result.push_back('\0');
    return string(&result[0]);
}
//1.7
template <size_t row, size_t col>
void rotateMatrixClockwise(int (&matrix)[row][col]) { //this is so cool
    //rotate in place so it needs to be a square matrix
    if (row != col) return;
    int N = row; //or col
    for(int layer = 0; layer<(N/2); layer++) {
        for(int i = layer; i<(N-1-layer);i++) {
            int temp = matrix[layer][i]; //top
            matrix[layer][i] = matrix[N-1-layer-i][layer]; //left
            matrix[N-1-layer-i][layer] = matrix[N-1-layer][N-1-layer-i]; //bottom
            matrix[N-1-layer][N-1-layer-i] = matrix[i][N-1-layer]; //right
            matrix[i][N-1-layer] = temp;
        }
    }
}
//1.8 zero matrix
template <size_t row, size_t col>
void zeroMatrix(int (&matrix)[row][col]) {
    int rowZeroStorage = 0; //is a column
    int colZeroStorage = 0; //is a row
    bool setStorage = false;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            if(matrix[i][j] == 0) {
                if(setStorage) {
                    matrix[i][rowZeroStorage] = 0;
                    matrix[colZeroStorage][j] = 0;
                }
                else {
                    setStorage = true;
                    //                    matrix[i][j] = 1; //constant value to fix bug which zeroes out the whole matrix
                    rowZeroStorage = j;
                    colZeroStorage = i;
                }
            }
        }
    }
    if(!setStorage) return;
    //set all eligible columns to zero
    for(int k = 0; k < col; k++) {
        if(matrix[colZeroStorage][k]==0 && k!=rowZeroStorage) {
            for(int l = 0; l < row; l++) {
                matrix[l][k] = 0;
            }
        }
    }
    //set all eligible rows to zero
    for(int k = 0; k < row; k++) {
        if(matrix[k][rowZeroStorage]==0 && k!=colZeroStorage) {
            for(int l = 0; l< col;l++) {
                matrix[k][l] = 0;
            }
        }
    }
    //set storages to zero
    for(int i = 0; i < col; i++)
        matrix[colZeroStorage][i] = 0; //the entire row
    for(int i = 0; i < row; i++)
        matrix[i][rowZeroStorage] = 0; //the entire col
    
}
#endif
