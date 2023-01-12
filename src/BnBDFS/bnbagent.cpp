#include <vector>
#include <queue>
#include <stack>
#include <bnbagent.h>
#include <graph.h>
#include <bnbagent.h>
#include <solution.h>
#include <vector>
#include <limits.h>
#include <chrono>

double BnbAgent::CalculateUpperBound(int n, std::vector<std::vector<double>> &inputMatrix)
{
    double upper_bound = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        upper_bound += inputMatrix[i][i + 1];
    }
    upper_bound += inputMatrix[n - 1][0];
    return upper_bound;
}

std::map<Vertex *, Vertex *> *BnbAgent::BranchAndBound(const Graph *graph, double initialUpperBound, std::chrono::duration<double> time_limit, time_type start_time, bool &timed_out)
{
    timed_out = false;
    Solution *p = new Solution(graph);
    Vertex *vertex = p->PickUnassignedVertex();

    priority_queue_domain_node *domain = p->OrderDomainValues(vertex);
    std::stack<std::pair<Vertex *, priority_queue_domain_node *>> stack;
    //handle case when graph has only one vertex
    if (p->HasFullAssignment())
    {
        bnb_result *result = new bnb_result();
        result->cost = 0;
        result->path_map = p->CurrentFullAssignment();
        results.push_back(result);
    }
    else
    {
        stack.push(std::make_pair(vertex, domain));
        ++expanded;
    }

    double upperBound = initialUpperBound;
    startingPoint = vertex;

    while (!stack.empty())
    {
        time_type current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - start_time;
        if (elapsed_seconds >= time_limit)
        {
            timed_out = true;
            break;
        }
        std::map<Vertex *, Vertex *> *bestSolution = nullptr;
        std::pair<Vertex *, priority_queue_domain_node *> node = stack.top();
        if (node.second->empty())
        {
            p->UnassignVertex(node.first);
            delete node.second;
            stack.pop();
        }
        else
        {
            vertex = node.first;
            domain = node.second;
            p->AssignVertex(node.first, domain->top());
            domain->pop();
            if (p->currentLowerBound >= upperBound)
            {
                ++pruned;
                continue;
            }

            if (p->HasFullAssignment())
            {
                if (bestSolution)
                    delete bestSolution;
                bestSolution = p->CurrentFullAssignment();
                upperBound = p->currentLowerBound;
                bnb_result *result = new bnb_result();
                result->cost = upperBound;
                result->path_map = bestSolution;
                results.push_back(result);
            }
            else
            {
                ++expanded;
                vertex = p->PickUnassignedVertex();
                domain = p->OrderDomainValues(vertex);
                stack.push(std::make_pair(vertex, domain));
            }
        }
    }
    delete p;
    return results.empty() ? nullptr : results.back()->path_map;
}
