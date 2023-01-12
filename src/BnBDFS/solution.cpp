#include <map>
#include <vector>
#include <queue>
#include <graph.h>
#include <solution.h>
#include <limits.h>
#include <disjoint_set.h>
#include <iostream>

DomainNode::DomainNode(const Vertex *vertex, double cost) : vertex(vertex), fn_value(cost)
{
}

int Solution::GetNumberOfAssignedVertex()
{
    int numberOfAssignedVertex = 0;
    for (auto p : assignment)
        if (p.second != nullptr)
            ++numberOfAssignedVertex;
    return numberOfAssignedVertex;
}

Solution::Solution(const Graph *graph) : graph(graph)
{
    for (Vertex *vertex : this->graph->vertices)
        assignment[vertex] = nullptr;
}

bool Solution::HasFullAssignment()
{
    return GetNumberOfAssignedVertex() == (int)graph->vertices.size() - 1;
}

std::map<Vertex *, Vertex *> *Solution::CurrentFullAssignment()
{
    std::map<Vertex *, Vertex *> *bestSolution = new std::map<Vertex *, Vertex *>();
    for (auto p : assignment)
    {
        if (p.second == nullptr)
        {
            bestSolution->operator[](p.first) = start;
            currentLowerBound = currentCost + graph->GetCost(const_cast<Vertex *>(p.first), const_cast<Vertex *>(start));
        }
        else
        {
            bestSolution->operator[](p.first) = const_cast<Vertex *>(p.second->vertex);
        }
    }
    return bestSolution;
}

Vertex *Solution::PickUnassignedVertex()
{
    Vertex *unassignedVertex = nullptr;
    if (lastAssignedValue != nullptr)
        unassignedVertex = lastAssignedValue;
    else
        for (auto p : assignment)
        {
            if (assignment[p.first] == nullptr)
            {
                unassignedVertex = p.first;
                break;
            }
        }
    if (start == nullptr)
        start = unassignedVertex;
    return unassignedVertex;
}

priority_queue_domain_node *Solution::OrderDomainValues(Vertex *vertex)
{
    priority_queue_domain_node *domain = new priority_queue_domain_node();
    std::vector<Vertex *> unassignedVertices;
    for (auto p : assignment)
        if (p.first != vertex and p.second == nullptr)
            unassignedVertices.push_back(p.first);

    double mst = GetMST(unassignedVertices);
    for (Vertex *v : unassignedVertices)
    {
        Edge *edge = graph->GetEdge(vertex, v);
        double heuristic = GetHeuristicValue(mst, edge, unassignedVertices);
        domain->push(new DomainNode(edge->destination, currentCost + heuristic));
        delete edge;
    }

    return domain;
}

double Solution::GetHeuristicValue(double mst, Edge *edge, std::vector<Vertex *> &unassignedVertices)
{
    return edge->cost + mst + GetMinCostToStart(edge->destination, unassignedVertices);
}

double Solution::GetMST(std::vector<Vertex *> &vertices)
{
    DisjointSet ds;
    for (Vertex *v : vertices)
    {
        ds.make_set(v);
    }

    priority_queue_edge edges;
    int num_vertices = (int)vertices.size();
    for (int i = 0; i < num_vertices - 1; ++i)
        for (int j = i + 1; j <= num_vertices - 1; ++j)
        {
            edges.push(graph->GetEdge(vertices[i], vertices[j]));
        }

    int mst_connections = 0;
    double mst_cost = 0;

    while (mst_connections < num_vertices - 1)
    {
        Edge *e = edges.top();
        edges.pop();
        if (ds.find(e->source) != ds.find(e->destination))
        {
            mst_connections++;
            ds.merge(e->source, e->destination);
            mst_cost += e->cost;
        }
        delete e;
    }

    while (!edges.empty())
    {
        Edge *e = edges.top();
        edges.pop();
        delete e;
    }

    return mst_cost;
}

double Solution::GetMinCostToStart(const Vertex *ignoredVertex, std::vector<Vertex *> &unassignedVertices)
{
    double minCostToStart = INT_MAX;
    for (Vertex *vertex : unassignedVertices)
    {
        if (vertex != ignoredVertex)
        {
            double cost = graph->GetCost(vertex, start);
            if (cost < minCostToStart)
            {
                minCostToStart = cost;
            }
        }
    }
    if (minCostToStart == INT_MAX)
    {
        if (unassignedVertices.size() > 0)
            minCostToStart = graph->GetCost(ignoredVertex, start);
        else
            minCostToStart = 0;
    }

    return minCostToStart;
}

void Solution::AssignVertex(Vertex *vertex, DomainNode *domain)
{
    lastAssignedValue = graph->GetVertex(domain->vertex->id);
    if (assignment[vertex])
    {
        currentCost -= graph->GetCost(vertex, assignment[vertex]->vertex);
        delete assignment[vertex];
    }

    currentLowerBound = domain->fn_value;
    currentCost += graph->GetCost(vertex, domain->vertex);
    assignment[vertex] = domain;
    if (start == nullptr)
        start = vertex;
}

void Solution::UnassignVertex(Vertex *vertex)
{
    double cost = graph->GetCost(vertex, assignment[vertex]->vertex);
    delete assignment[vertex];
    assignment[vertex] = nullptr;

    for (auto p : assignment)
    {
        if (p.second != nullptr and p.second->vertex->id == vertex->id)
        {
            currentLowerBound = p.second->fn_value;
            break;
        }
    }

    currentCost = currentCost - cost;
    if (lastAssignedValue == vertex)
        lastAssignedValue = nullptr;
}
