#ifndef BNB_AGENT_H
#define BNB_AGENT_H

#include <map>
#include <vector>
#include <graph.h>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> time_type;

class bnb_result
{
public:
    std::map<Vertex *, Vertex *> *path_map;
    double cost;
    time_type calculated_at = std::chrono::system_clock::now();
};

class BnbAgent
{
public:
    Vertex *startingPoint;
    std::vector<bnb_result*> results;
    int pruned = 0;
    int expanded = 0;
    double CalculateUpperBound(int n, std::vector<std::vector<double>> &inputMatrix);
    std::map<Vertex *, Vertex *> *BranchAndBound(const Graph *graph, double initialUpperBound, std::chrono::duration<double> time_limit, time_type start_time, bool &timed_out);
};

#endif