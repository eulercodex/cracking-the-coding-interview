//
//  Stringbuiler.hpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/17/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#ifndef Stringbuiler_hpp
#define Stringbuiler_hpp

#include <vector>
#include <string>

using namespace std;

class Stringbuilder {
private:
    vector<char>storage;
    size_t size = 0;
public:
    void append(string s);
    string toString();
};
#endif /* Stringbuiler_hpp */
