#ifndef SLS_AGENT_H
#define SLS_AGENT_H

#include <vector>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> time_type;

struct SLSEdge
{
    double pt1, pt2;
    double weight;
    SLSEdge(double u, double v, double wt) : pt1(u), pt2(v), weight(wt) {}

    bool operator==(const SLSEdge &e)
    {
        return weight == e.weight && ((pt1 == e.pt1 && pt2 == e.pt2) || (pt2 == e.pt1 && pt1 == e.pt2));
    }
};

class SLSAgent
{
private:
    int number_of_cities = 0;
    std::vector<std::vector<double>> city_matrix;
    std::vector<SLSEdge> mst;
    bool stopUsingMST = false;

    std::vector<double> getOrder();
    std::vector<SLSEdge> compute_mst(std::vector<std::vector<double>> &graph);
    std::vector<double> findNextFromMST(std::vector<double> currentOrder);
    double getPathCost(std::vector<double> order);

public:
    int iterations = 0;
    time_type calculated_at;
    bool timed_out = false;
    SLSAgent(int number_of_cities, std::vector<std::vector<double>> city_matrix);
    double SimulatedAnnealing(time_type start_time, std::chrono::duration<double> time_limit);
};


#endif