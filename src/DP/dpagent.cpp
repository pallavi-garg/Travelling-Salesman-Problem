#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>
#include <list>
#include <dpagent.h>

DPAgent::DPAgent(int number_of_cities, std::vector<std::vector<double>> city_matrix)
{
    this->number_of_cities = number_of_cities;
    this->memo = std::vector<std::vector<double>>(this->number_of_cities + 1, std::vector<double>(1 << (this->number_of_cities + 1), 0.0));
    this->city_matrix = std::vector<std::vector<double>>(this->number_of_cities + 1, std::vector<double>(1 << (this->number_of_cities + 1), 0.0));
    for (int i = 1; i <= this->number_of_cities; ++i)
        for (int j = 1; j <= this->number_of_cities; ++j)
            this->city_matrix[i][j] = city_matrix[i - 1][j - 1];
}

// Use bit masking to keep track of visited cities
double DPAgent::calculate(int i, int mask)
{
    // base case
    // if only ith bit and 1st bit is set in our mask,
    // it implies we have visited all other nodes already
    if (mask == ((1 << i) | 3))
        return this->city_matrix[1][i];
    // memoization
    if (this->memo[i][mask] != 0.0)
        return memo[i][mask];

    double res = this->MAX;

    for (int j = 1; j <= this->number_of_cities; j++)
        if ((mask & (1 << j)) && j != i && j != 1)
            res = std::min(res, calculate(j, mask & (~(1 << i))) + this->city_matrix[j][i]);

    memo[i][mask] = res;
    return res;
}

double DPAgent::Find(time_type start_time, std::chrono::duration<double> time_limit)
{
    // memoization for top down recursion
    // starting node is 1
    double ans = MAX;
    for (int i = 1; i <= this->number_of_cities; i++)
    {
        time_type current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - start_time;
        if (elapsed_seconds >= time_limit)
        {
            timed_out = true;
            break;
        }
        ans = std::min(ans, calculate(i, (1 << (this->number_of_cities + 1)) - 1) + this->city_matrix[i][1]);
    }

    calculated_at = std::chrono::system_clock::now();
    return ans;
}
