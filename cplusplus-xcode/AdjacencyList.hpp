//
//  Graph.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/24/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef AdjacencyList_hpp
#define AdjacencyList_hpp

#include <vector>

typedef struct edgenode {
    string name;
    int nodeIndex;
    int weight;
    struct edgenode * next;
} edgenode;

class AdjacencyList {
private:
public:
    AdjacencyList();
    vector<edgenode> nodes;
};

AdjacencyList::AdjacencyList() {
    
}
#endif /* AdjacencyList_hpp */
