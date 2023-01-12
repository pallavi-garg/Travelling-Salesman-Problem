#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <map>
#include <graph.h>

class DisjointSet {

private:
    std::map<const Vertex *, const Vertex *> parent_map;
    std::map<const Vertex *, int> rank;

public:
    void make_set(const Vertex *v);
    const Vertex *find(const Vertex *v);
    void merge(const Vertex *v, const Vertex *u);
};

#endif