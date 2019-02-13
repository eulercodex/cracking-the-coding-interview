//
//  Stringbuiler.cpp
//  cplusplus-xcode
//
//  Created by Jesse Mihigo on 10/17/16.
//  Copyright © 2016 Jesse Mihigo. All rights reserved.
//

#include "Stringbuiler.hpp"

void Stringbuilder::append(string s) { //for some reasons i have to include string and vector on top
    size_t length = s.length();
    for (int i = 0; i < length; i++) {
        storage.push_back(s[i]);
    }
    size += length;
}
string Stringbuilder::toString() {
    return string(&storage[0],size);
}
