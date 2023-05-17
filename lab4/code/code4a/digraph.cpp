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


// *** TODO ***
// construct unweighted single source shortest path-tree for start vertex s
void Digraph::uwsssp(int s) const {
    assert(s >= 1 && s <= size);

    std::queue<int> queue; // Create an empty queue.

    // The dist vector. Checking distance from start to each and every node. 
    for (int i = 1; i <= size; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        path[i] = 0;
    }
    dist[s] = 0; // Distance from the startnode to itself should be set to zero.

    queue.push(s); // Add the start-node to the queue.

    // Breadth-first-search algorithm implementation
    while (!queue.empty())
    {
        int compare = queue.front();
        queue.pop();

        for (Edge e : table[compare])
        {
            if (dist[e.tail] == std::numeric_limits<int>::max())
            {
                dist[e.tail] = dist[compare] + 1;
                path[e.tail] = compare;
                queue.push(e.tail);
            }
        }
    }
}

// construct positive weighted single source shortest path-tree for start vertex s
// Dijktra’s algorithm
// *** TODO ***
void Digraph::pwsssp(int s) const {
    assert(s >= 1 && s <= size);

    //for (int i = 0; i < size; i++)
    //{
    //    dist[i](std::numeric_limits<int>::max());
    //    path.push_back(0);
    //    done.push_back(false);
    //}

    // Complexity is equal to size of the vectors which is the size of the vector, therefore it's O(n)
	std::fill(dist.begin(), dist.end(), std::numeric_limits<int>::max());
	std::fill(path.begin(), path.end(), 0);
	std::fill(done.begin(), done.end(), false);

    dist[s] = 0;
    done[s] = true;
    int v = s;

    while (true)
    {
        
        for (Edge e : table[v])
        {
            if (done[e.tail] == false && dist[e.tail] > dist[v] + e.weight)
            {
                dist[e.tail] = dist[v] + e.weight; // Info about weight is in edge.h (Note for us)
                path[e.tail] = v;
            }
        }

		// find_smallest_undone_distance_vertex();
		int minDist = std::numeric_limits<int>::max();
        for (int i = 1; i <= size; i++) {
			if (minDist > dist[i] && !done[i])
			{
			    v = i;
			    minDist = dist[i];
			}
        }

        if (minDist == std::numeric_limits<int>::max())
        {
            break;
        }

        done[v] = true;
    }
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
// *** TODO ***
void Digraph::printPath(int t) const {
    assert(t >= 1 && t <= size);

    std::vector<int> shortestPath;
    int steps = 0;

    while (dist[t] != 0)
    {
        shortestPath.push_back(t);
        t = path[t];
        steps++;
    }

	shortestPath.push_back(t);

	std::reverse(shortestPath.begin(), shortestPath.end());

    std::cout << "  ";
    for (int i : shortestPath)
    {
        std::cout << i << "  ";
    }

    std::cout << " (" << steps << ")";

}
