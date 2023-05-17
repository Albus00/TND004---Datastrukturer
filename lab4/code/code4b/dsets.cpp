/*********************************************
 * file:	~\code4b\dsets.cpp                *
 * remark: implementation of disjoint sets    *
 **********************************************/

#include <iostream>
#include <format>
#include <cassert>

#include "dsets.h"

// -- CONSTRUCTORS

DSets::DSets(size_t theSize) : V(theSize + 1) {  // slot zero is not used
    assert(theSize > 0);
    init();
}

// -- MEMBER FUNCTIONS

// create initial sets
void DSets::init() {
    for (size_t i = 1; i < V.size(); ++i) {
        V[i] = -1;  // every disjoint set has one node -- singleton
    }
}

// join sets named r and s where r != s
// i.e. join trees with roots r and s
void DSets::join(int r, int s) {
    assert(r != s);
    assert(r >= 1 && r <= V.size() - 1);
    assert(s >= 1 && s <= V.size() - 1);
    assert(V[r] < 0);
    assert(V[s] < 0);

    
    // Do Union by Size
    if (V[s] < V[r])
    {
        V[s] += V[r];
        V[r] = s;
    }
    else 
    {
        V[r] += V[s];
        V[s] = r;
    }
}

// return name of current set for x
// i.e. return root of tree for x
int DSets::find(int x) {
    assert(x >= 1 && x <= V.size() - 1);

    // simple find
    if (V[x] < 0) 
    {
        return x;
    } 
    // find with path compression
    else 
    {
        int found = find(V[x]);
        V[x] = found;
        return found;
    }
}

// just in case ...
void DSets::print() const {
    std::cout << "\n";

    for (size_t i = 1; i < V.size(); i++) {
        std::cout << std::format("{:4}", i);
    }
    std::cout << "\n";

    for (auto u : V) {
        std::cout << std::format("{:4}", u);
    }
    std::cout << "\n";
}
