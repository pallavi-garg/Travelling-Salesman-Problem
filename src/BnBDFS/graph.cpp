#include <vector>
#include <graph.h>

Vertex::Vertex(int id) : id(id)
{
}

Edge::Edge(double cost, const Vertex *source, const Vertex *destination) : cost(cost), source(source), destination(destination)
{
}

Vertex *Graph::GetVertex(int id) const
{
    return vertices[id - 1];
}

Edge *Graph::GetEdge(const Vertex *from, const Vertex *to) const
{
    Edge *edge = new Edge(distanceMatrix[from->id - 1][to->id - 1], from, to);
    return edge;
}

double Graph::GetCost(const Vertex *source, const Vertex *destination) const
{
    return distanceMatrix[source->id - 1][destination->id - 1];
}

Graph::Graph()
{
}

Graph::~Graph()
{
    for (Vertex *v : vertices)
    {
        delete v;
    }
}