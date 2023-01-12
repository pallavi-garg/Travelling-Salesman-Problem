#ifndef SOLUTION_H
#define SOLUTION_H

#include <map>
#include <vector>
#include <graph.h>

class DomainNode
{
public:
    const Vertex *const vertex;
    // represents f(vertex) = g(vertex) + h(vertex)
    const double fn_value;
    DomainNode(const Vertex *vertex, double cost);
};

class NodeComparator
{
public:
    bool operator()(DomainNode *a, DomainNode *b)
    {
        return a->fn_value > b->fn_value;
    }
};

typedef std::priority_queue<DomainNode *, std::vector<DomainNode *>, NodeComparator> priority_queue_domain_node;

class Solution
{
public:
    const Graph *const graph;
    std::map<Vertex *, DomainNode *> assignment;
    double currentCost = 0, currentLowerBound = 0;
    Vertex *start = nullptr, *lastAssignedValue = nullptr;

    Solution(const Graph *graph);
    bool HasFullAssignment();
    int GetNumberOfAssignedVertex();
    std::map<Vertex *, Vertex *> *CurrentFullAssignment();
    Vertex *PickUnassignedVertex();
    priority_queue_domain_node *OrderDomainValues(Vertex *vertex);
    void AssignVertex(Vertex *vertex, DomainNode *domain);
    void UnassignVertex(Vertex *vertex);

private:
    double GetMinCostToStart(const Vertex *ignoredVertex, std::vector<Vertex *> &unassignedVertices);
    double GetMST(std::vector<Vertex *> &vertices);
    double GetHeuristicValue(double mst, Edge *edge, std::vector<Vertex *> &unassignedVertices);
};

#endif