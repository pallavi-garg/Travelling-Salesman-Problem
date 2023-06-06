#ifndef DP_AGENT_H
#define DP_AGENT_H

#include <vector>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> time_type;

class DPAgent
{
private:
    int number_of_cities = 0;
    std::vector<std::vector<double>> city_matrix;
    std::vector<std::vector<double>> memo;

public:
    int iterations = 0;
    time_type calculated_at;
    bool timed_out = false;
    const int MAX = 1000000;
    double calculate(int i, int mask);
    DPAgent(int number_of_cities, std::vector<std::vector<double>> city_matrix);
    double Find(time_type start_time, std::chrono::duration<double> time_limit);
};

#endif