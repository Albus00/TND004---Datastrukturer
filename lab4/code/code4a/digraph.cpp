/*********************************************
 * file:	~\code4a\digraph.cpp              *
 * remark: implementation of directed graphs  *
 **********************************************/

#include <iostream>
#include <algorithm>
#include <limits>  //std::numeric_limits
#include <vector>
#include <cassert>
#include <queue>
#include <format>

#include "digraph.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

Digraph::Digraph(int n)
    : table(size_t(n) + 1)
    , size{n}
    , n_edges{0}
    , dist(size_t(n) + 1)
    , path(size_t(n) + 1)
    , done(size_t(n) + 1) {
    assert(n >= 1);

    // Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<Edge>& V, int n) : Digraph{n} {
    for (auto e : V) {
        insertEdge(e);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge e = (u, v, w)
// update weight w if edge (u, v) is present
void Digraph::insertEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    // Check if edge e already exists
    if (auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                               [e](const Edge& ed) { return e.links_same_nodes(ed); });
        it == end(table[e.head])) {
        table[e.head].push_back(e);  // insert new edge e
        ++n_edges;
    } else {
        it->weight = e.weight;  // update the weight
    }
}

// remove directed edge e
void Digraph::removeEdge(const Edge& e) {
    assert(e.head >= 1 && e.head <= size);
    assert(e.tail >= 1 && e.tail <= size);

    auto it = std::find_if(begin(table[e.head]), end(table[e.head]),
                           [e](const Edge& ed) { return e.links_same_nodes(ed); });

    assert(it != end(table[e.head]));
    table[e.head].erase(it);
    --n_edges;
}

// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // *** TODO ***

    std::queue<int> queue; // Create an empty queue.
    queue.push(s); // Add the start-node to the queue.

    // The dist vector. Checking distance from start to each and every node. 
    std::vector<int> dist(size + 1, std::numeric_limits<int>::max());
    dist[0] = s; // Distance from the startnode to itself should be set to zero.

    // Breadth-first-search algorithm implementation
    while (!queue.empty())
    {
        int compareNode = queue.front();
        queue.pop();
        for (int v : adj[i])
        {

        }

    }



    
    // dist vector should be initialized with std::numeric_limits<int>::max()
}

// construct positive weighted single source shortest path-tree for start vertex s
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
    assert(s >= 1 && s <= size);

    // *** TODO ***
    // dist vector should be initialized with std::numeric_limits<int>::max()
}

// print graph
void Digraph::printGraph() const {
    std::cout << std::format("{:-<66}\n", '-');
    std::cout << "Vertex  adjacency lists\n";
    std::cout << std::format("{:-<66}\n", '-');

    for (int v = 1; v <= size; ++v) {
        std::cout << std::format("{:4} : ", v);
        for (auto const& e : table[v]) {
            std::cout << std::format("({:2}, {:2}) ", e.tail, e.weight);
        }
        std::cout << "\n";
    }
    std::cout << std::format("{:-<66}\n", '-');
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << std::format("{:-<22}\n", '-');
    std::cout << "vertex    dist    path\n";
    std::cout << std::format("{:-<22}\n", '-');

    for (int v = 1; v <= size; ++v) {
        std::cout << std::format("{:4} : {:6} {:6}\n", v,
                                 ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]),
                                 path[v]);
    }
    std::cout << std::format("{:-<22}\n", '-');
}

// print shortest path from s to t and the corresponding path length
// Hint: consider using recursion
void Digraph::printPath(int t) const {
    assert(t >= 1 && t <= size);

    // *** TODO ***
}
