/*************************************************
 * file:	~\code4a\edge.h                      *
 * remark: interface for directed weighted edges *
 *************************************************/

#pragma once

#include <iostream>
#include <format>
#include <compare>  // three-way comparison operator <=>

// Represents a directed edge from head to tail with weight
class Edge {
public:
    // -- CONSTRUCTORS
    Edge(int u = 0, int v = 0, int w = 0) : head{u}, tail{v}, weight{w} {
    }

    bool links_same_nodes(const Edge &e) const {
        return (head == e.head && tail == e.tail);
    }

    Edge reverse() const {
        return {tail, head, weight};
    }

    // -- Three way comparison operator
    // used in exercise of Part B
    std::partial_ordering operator<=>(const Edge &e) const {
        return weight <=> e.weight;
    }

    // -- FRIENDS
    friend std::ostream &operator<<(std::ostream &os, const Edge &e) {
        os << std::format("({:2}, {:2}, {:2}) ", e.head, e.tail, e.weight);
        return os;
    }

    // -- DATA MEMBERS: represent an edge from 'head' to 'tail' with 'weight'
    int head;
    int tail;
    int weight;
};
