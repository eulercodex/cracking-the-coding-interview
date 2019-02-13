//
//  CTCI-16.h
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 1/2/17.
//  Copyright © 2017 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_16_h
#define CTCI_16_h
#include <vector>
#include <string>
#include <algorithm>
//16.2
int wordFrequencies1(std::vector<std::string> &book, std::string word) {
    int count = 0;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for(string s : book) {
        string copy(s);
        transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        if(copy.compare(word) == 0) {
            count++;
        }
    }
    return count;
}
std::unordered_map<string, int> preprocessBook(vector<string> & book) {
    std::unordered_map<string,int> table;
    for(string s : book) {
        string copy(s);
        transform(copy.begin(), copy.end(), copy.begin(),::tolower);
        if(table.count(copy) > 0) {
            table[copy]++;
        }
        else {
            table[copy] = 1;
        }
    }
    return table;
}
int wordFrequencies2(std::unordered_map<string, int> & table, std::string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if(table.count(word) > 0)
        return table[word];
    return 0;
}
//16.3---implement it one of these days
//16.4 this solution does not assume that we know what the last move is
enum TicTacToePiece {
    empty, red, black
};
template <size_t N>
TicTacToePiece hasWonTicTacToe(TicTacToePiece (&board)[N][N]) {
    //check diagonals
    //up-down
    TicTacToePiece piece = board[0][0];
    if(piece != empty) {
        int i = 1;
        for(; i < N; i++) {
            if(piece != board[i][i]) {
                break;
            }
        }
        if(i == N) {//last element
            return piece;
        }
        
    }
    //down-up
    piece = board[N-1][0];
    if(piece != empty) {
        int i = 1;
        for(;i < N; i++) {
            if(piece != board[N-1-i][i]) {
                break;
            }
        }
        if(i == N) {
            return piece;
        }
    }
    //check rows
    for(int i = 0; i < N; i++) {
        piece = board[i][0];
        if(piece == empty) continue;
        int j = 0;
        for(; j < N; j++) {
            if(piece != board[i][j]) {
                break;
            }
        }
        if(j == N)
            return piece;
    }
    //check diagonal
    for(int j = 0; j < N; j++) {
        piece = board[0][j];
        if(piece == empty) continue;
        int i = 0;
        for(; i < N; i++) {
            if(piece != board[i][j]) {
                break;
            }
        }
        if(i == N)
            return piece;
    }
    return empty;
}
//16.5
int factorialZeros(int n) {
    int count = 0;
    for(int i = 5; i <= n; i *= 5) {
        count += n/i;
    }
    return count;
}
//16.18
std::string buildStringUsingPatternAndSubstrings(const string &pattern, const std::string &sub1, const std::string &sub2) {
    //i wont even try to check if pattern is an empty string
    char first = pattern[0];
    std::string result(sub1);
    for(int i = 1; i < pattern.size(); i++) {
        if(pattern[i] == first) {
            result += sub1;
        }
        else {
            result += sub2;
        }
    }
    return result;
}
bool patternMatching(std::string pattern, std::string value) {
    if(pattern.size() == 0) {
        return value.size() == 0; //totally debatable or is it?
    }
    for(int i = 1; i <= value.size(); i++) {
        std::string substring1 = value.substr(0,i);
        for (int j = 1; j <= (value.size() - i); j++) {
            std::string substring2 = value.substr(i,j);
            std::string candidate = buildStringUsingPatternAndSubstrings(pattern,substring1,substring2);
            if(candidate.compare(value) == 0) {
                return true;
            }
        }
    }
    return false;
}

#endif /* CTCI_16_h */
