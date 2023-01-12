#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>

class Vertex
{
public:
    const int id;
    Vertex(int id);
};

class Edge
{
public:
    const double cost;
    const Vertex* const source;
    const Vertex* const destination;

    Edge(double cost, const Vertex *source, const Vertex *destination);
};

class EdgeComparator
{
public:
    bool operator()(Edge *a, Edge *b)
    {
        return a->cost > b->cost;
    }
};

typedef std::priority_queue<Edge *, std::vector<Edge *>, EdgeComparator> priority_queue_edge;

class Graph
{
public:
    std::vector<Vertex *> vertices;
    std::vector<std::vector<double>> distanceMatrix;

    Vertex *GetVertex(int id) const;
    Edge *GetEdge(const Vertex *from, const Vertex *to) const;
    double GetCost(const Vertex *source, const Vertex *destination) const;
    Graph();
    ~Graph();
};

#endif