#include <vector>
#include <disjoint_set.h>

void DisjointSet::make_set(const Vertex *v)
{
    parent_map[v] = v;
    rank[v] = 0;
}

const Vertex *DisjointSet::find(const Vertex *v)
{
    if (v != parent_map[v])
        parent_map[v] = find(parent_map[v]);
    return parent_map[v];
}

void DisjointSet::merge(const Vertex *u, const Vertex *v)
{
    u = find(u);
    v = find(v);

    if (rank[u] > rank[v])
        parent_map[v] = u;
    else
        parent_map[u] = v;
    if (rank[u] == rank[v])
        rank[v]++;
}

