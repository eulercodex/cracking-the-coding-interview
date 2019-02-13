//
//  CTCI-08.h
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 12/28/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef CTCI_08_h
#define CTCI_08_h
//8.2 from CTIC
typedef struct Point{
    int x;
    int y;
} Point;

bool operator==(const Point &p1,const Point &p2)
{
    return (p1.x == p2.x && p1.y == p2.y);
}

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point& p) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return ((hash<int>()(p.x) ^ (hash<int>()(p.y) << 1)) >> 1);
        }
    };
}

bool findPathHelper(const vector<vector<int>>&grid,Point origin,Point destination, vector<Point> &path, unordered_set<Point> &visitedPoints) {
    if(origin.x < 0 || origin.x >= grid.size() || origin.y < 0 || origin.y >= grid[0].size() || !grid[origin.x][origin.y])
        return false; //out of bound or can't access point
    //    cout <<"Point: (" <<origin.x<<","<<origin.y<<"), count: "<<visitedPoints.count(origin)<<endl;
    if(visitedPoints.count(origin) > 0) {
        return false; //already visited this path
    }
    else visitedPoints.insert(origin); //just visited this point so let's move on
    bool hasReachedDestination = origin.x == destination.x && origin.y == destination.y;
    if(hasReachedDestination || findPathHelper(grid, {origin.x+1,origin.y}, destination, path, visitedPoints) ||
       findPathHelper(grid, {origin.x,origin.y+1}, destination, path, visitedPoints)) {
        path.push_back(origin);
        return true;
    }
    return false;
}
int findPath(const vector<vector<int>> &grid,Point origin,Point destination, vector<Point> &path) {
    if(grid.size()==0 || grid[0].size()==0)
        return -1; //empty grid
    if(origin.x < 0 || origin.x >= grid.size() || origin.y < 0 || origin.y >= grid[0].size() ||
       destination.x < 0 || destination.x >= grid.size() || destination.y < 0 || destination.y >= grid[0].size())
        return -1; //at least one point is out of bound
    path.resize(0); //reset path
    unordered_set<Point> visitedPoints;
    if(findPathHelper(grid, origin, destination, path, visitedPoints))
        return 0;
    return -1;
}
//8.4 power set from CTIC
void getSubsetsHelper(vector<int>&set,int index,vector<vector<int>> &allSubsets) {
    if (index == set.size())
        return;
    size_t size = allSubsets.size();
    for (int i = 0; i < size; i++) {
        vector<int> newSubset(allSubsets[i]);
        newSubset.push_back(set[index]);
        allSubsets.push_back(newSubset);
    }
    getSubsetsHelper(set, index+1, allSubsets);
}
vector<vector<int>>getSubsets(vector<int> &set) {
    vector<vector<int>> allSubsets;
    vector<int>empty;
    allSubsets.push_back(empty);
    getSubsetsHelper(set, 0, allSubsets);
    return allSubsets;
}
//8.5
void recursiveMultiplyHelper(int a, int b, int &result) {
    if(b!=0) {
        if((b & 1)==1)
            result += a;
        recursiveMultiplyHelper(a<<1,b>>1,result);
    }
    
}
int recursiveMultiply(int a, int b){
    int result = 0;
    recursiveMultiplyHelper(a, b, result);
    return result;
}
//8.6 tower of hanoi
void moveTop(stack<int> &from, stack<int> &to) {
    int top = from.top();
    from.pop();
    to.push(top);
}
void moveDisks(int n, stack<int> &origin, stack<int> &destination, stack<int> &buffer, int &count) {
    count++;
    if(n > 0) {
        moveDisks(n-1, origin, buffer, destination,count);
        moveTop(origin, destination);
        moveDisks(n-1, buffer, destination, origin,count);
    }
}
void towerOfHanoi(int n) {
    if(n <= 0) return;//nothing to do here
    std::stack<int> stack1;
    std::stack<int> stack2;
    std::stack<int> stack3;
    for(int i = n; i > 0; i--) {
        stack1.push(i); //initialize first stack
    }
    int count =0;
    moveDisks(n, stack1, stack3, stack2, count);
}
//8.9 parens
void parensHelper(int open, int closed,string aString,vector<string> &result) {
    if(closed > open && closed > 0) {
        string newString = aString + ")";
        parensHelper(open, closed-1,newString, result);
    }
    if(open > 0) {
        string newString = aString + "(";
        parensHelper(open-1, closed,newString, result);
    }
    if(closed == 0 && open == 0)
        result.push_back(aString);
}
vector<string> parens(int n) {
    vector<string> result;
    if(n<=0) return result;
    parensHelper(n, n,"",result);
    return result;
}
#endif /* CTCI_08_h */
