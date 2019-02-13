//
//  extra.h
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 1/4/17.
//  Copyright © 2017 Jesse Mihigo. All rights reserved.
//

#ifndef extra_h
#define extra_h
#include <unordered_set>
#include <string>
#include <vector>
#include <math.h>

struct EdgeNode {
    int node;
    int weight;
};
class GraphWithWeight {
private:
    int size;
    std::vector<std::list<EdgeNode>> adjacencyList;
public:
    GraphWithWeight(int aSize): size(aSize) {
        adjacencyList.resize(size);
    }
    void addEdgeWithWeight(int source, int destination, int weight, bool directed = true) {
        if(source < 0 || source >= size || destination < 0 || destination >= size)
            throw exception();
        EdgeNode node = {destination,weight};
        adjacencyList[source].push_back(node);
        if(!directed) {
            EdgeNode otherNode = {source,weight};
            adjacencyList[destination].push_back(otherNode);
        }
    }
    int edgeWeight(int source, int destination) const {
        for(EdgeNode n : adjacencyList[source]) {
            if(n.node == destination) {
                return n.weight;
            }
        }
        return INT_MAX;//error, not sure how to handle this case
    }
    int getSize() const {
        return size;
    }
};
void dijkstra(GraphWithWeight & graph, int source) {
    vector<int>minimumDistanceFromSourceToNode(graph.getSize());
    for(int i = 0; i < minimumDistanceFromSourceToNode.size(); i++) {
        minimumDistanceFromSourceToNode[i] = INT_MAX; //initialize to "infinity"
    }
    minimumDistanceFromSourceToNode[source] = 0; //except at the source of course
    vector<int>previous(graph.getSize());
    
}
vector<string> routine() {
    return vector<string>();
}

#define UNASSIGNED 0

template <int N>
bool findUnassigned(int (&matrix)[N][N], int &row, int &column) {
    for(int j = column; j < N; j++) {
        if(matrix[row][j] == UNASSIGNED) {
            column = j;
            return true;
        }
    }
    for(int i = row+1; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(matrix[i][j] == UNASSIGNED) {
                row = i;
                column = j;
                return true;
            }
        }
    }
    return false;
}
template <int N>
bool isValueSafe(int (&matrix)[N][N], int row, int column, int boxSize, int value) {
    //row
    for(int j = 0; j < N; j++) {
        if(matrix[row][j] == value)
            return false;
    }
    //column
    for(int i = 0; i < N; i++) {
        if(matrix[i][column] == value)
            return false;
    }
    //box
    int boxTopLeftRow = (row/boxSize)*boxSize;
    int boxTopLeftColumn = (column/boxSize)*boxSize;
    for(int i = 0; i < boxSize; i++) {
        for(int j = 0; j < boxSize; j++) {
            if(matrix[boxTopLeftRow + i][boxTopLeftColumn + j] == value)
                return false;
        }
    }
    //otherwise
    return true;
}
template <int N>
bool solveSudoku(int (&matrix)[N][N], int &row, int &column, int boxSize) {
    if(!findUnassigned(matrix, row, column))
        return true;
    for(int i = 1; i <= N; i++) {
        if(isValueSafe(matrix, row, column, boxSize, i)) {
            matrix[row][column] = i;
            int oldRow = row;
            int oldColumn = column;
            if(solveSudoku(matrix, row, column, boxSize)) {
                return true;
            }
            //revert back
            row = oldRow;
            column = oldColumn;
            matrix[row][column] = UNASSIGNED;
        }
    }
    return false;
}
template <int N>
bool solveSudoku(int (&matrix)[N][N]) {
    int boxSize = sqrt(N);
    //assume N to be perfect square
    if((boxSize*boxSize) != N && ((boxSize+1)*(boxSize+1)) != N)
        return false;
    int row = 0, column = 0;
    return solveSudoku(matrix, row, column, boxSize);
}
template <int N>
bool verifySudoku(int (&matrix)[N][N]) {
    //assume N is a perfect square
    int boxSize = sqrt(N);
    if (boxSize*boxSize != N && (boxSize-1)*(boxSize-1) != N)
        return false;
    //rows
    for(int i = 0; i < N; i++) {
        std::unordered_set<int> someSet;
        for(int j = 0; j < N; j++) {
            if(someSet.count(matrix[i][j]) > 0)
                return false;
            someSet.insert(matrix[i][j]);
        }
    }
    //columns
    for(int j = 0; j < N; j++) {
        std::unordered_set<int> someSet;
        for(int i = 0; i < N; i++) {
            if(someSet.count(matrix[i][j]) > 0)
                return false;
            someSet.insert(matrix[i][j]);
        }
    }
    //boxes
    for(int i = 0; i < boxSize; i++) {
        for(int j = 0; j < boxSize; j++) {
            std::unordered_set<int> someSet;
            int topLeftRow = i*boxSize;
            int topLeftColumn = j*boxSize;
            for(int k = 0; k < boxSize; k++) {
                for(int l = 0; l < boxSize; l++) {
                    if(someSet.count(matrix[topLeftRow+k][topLeftColumn+l]) > 0)
                        return false;
                    someSet.insert(matrix[topLeftRow+k][topLeftColumn+l]);
                }
            }
        }
    }
    return true;
}

#endif /* extra_h */
