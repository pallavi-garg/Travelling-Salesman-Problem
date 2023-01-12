#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>
#include <list>
#include <slsagent.h>

SLSAgent::SLSAgent(int number_of_cities, std::vector<std::vector<double>> city_matrix)
{
    this->number_of_cities = number_of_cities;
    this->city_matrix = city_matrix;
}

std::vector<SLSEdge> SLSAgent::compute_mst(std::vector<std::vector<double>> &graph)
{
    int N = graph.size() - 1;

    std::vector<double> parent(N, 0);
    std::vector<double> key(N, 1e9);
    std::vector<bool> mstSet(N, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < N - 1; count++)
    {
        double mini = 1e9;
        double u = 0;

        for (int v = 0; v < N; v++)
        {
            if (mstSet[v] == false && key[v] < mini)
            {
                mini = key[v];
                u = v;
            }
        }
        mstSet[u] = true;
        for (int i = 0; i < N; i++)
        {
            double weight = graph[u][i];
            if (graph[u][i] && mstSet[i] == false && weight < key[i])
            {
                parent[i] = u;
                key[i] = weight;
            }
        }
    }

    for (int i = 1; i < N; i++)
    {
        mst.push_back(SLSEdge(parent[i], i, graph[parent[i]][i]));
        mst.push_back(SLSEdge(i, parent[i], graph[i][parent[i]]));
    }

    return mst;
}

std::vector<double> SLSAgent::findNextFromMST(std::vector<double> currentOrder)
{
    std::vector<double> nextOrder = currentOrder;
    int a = rand() % (number_of_cities - 1);

    if (a == number_of_cities - 1)
        --a;

    if (stopUsingMST)
    {
        if (city_matrix[nextOrder[a - 1]][nextOrder[a + 1]] < city_matrix[nextOrder[a - 1]][nextOrder[a]])
        {
            std::swap(nextOrder[a], nextOrder[a + 1]);
        }
        else
        {
            int i = a + 2;
            if (i == number_of_cities)
                i = 0;

            std::swap(nextOrder[a], nextOrder[i]);
        }
    }
    else
    {
        int i;
        SLSEdge temp = mst[a];
        for (i = 0; i < number_of_cities; i++)
            if (nextOrder[i] == temp.pt1)
                break;
        if (i == number_of_cities - 1)
            i = -1;
        if (temp.pt2 != nextOrder[i + 1])
            std::swap(nextOrder[temp.pt2], nextOrder[i + 1]);
    }

    return nextOrder;
}

double SLSAgent::getPathCost(std::vector<double> order)
{
    double cost = 0;
    for (int i = 0; i < number_of_cities - 1; i++)
        cost += city_matrix[order[i]][order[i + 1]];
    cost += city_matrix[order.back()][order.front()];

    return cost;
}

double getRandDouble()
{
    double x;
    x = rand() % 999 + 1;
    return x / 1000.0;
}

std::vector<double> SLSAgent::getOrder()
{
    std::vector<double> order;
    int counter = number_of_cities * number_of_cities;
    int pos;
    int *tab = new int[number_of_cities];
    for (int i = 0; i < number_of_cities; i++)
        tab[i] = i;

    while (counter > 0)
    {
        pos = rand() % number_of_cities;
        std::swap(tab[pos], tab[number_of_cities - 1 - pos]);
        counter--;
    }

    for (int i = 0; i < number_of_cities; i++)
        order.push_back(tab[i]);
    return order;
}

double SLSAgent::SimulatedAnnealing(time_type start_time, std::chrono::duration<double> time_limit)
{
    compute_mst(city_matrix);
    double maxTemperature = 1.0e+303;
    double temperature = number_of_cities > 200 ? DBL_MAX : maxTemperature;
    double coolRate = 0.9999;
    double threshold_temp = maxTemperature / 1.5;

    std::vector<double> currentOrder = getOrder();
    std::vector<double> bestOrder = currentOrder;

    double currentCost = getPathCost(currentOrder);
    double bestCost = currentCost;
    double delta;
    double random;

    std::vector<double> newOrder;
    double newCost = 0;

    while (temperature > 0.0001)
    {
        if (threshold_temp > temperature)
        {
            stopUsingMST = true;
        }
        time_type current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = current_time - start_time;
        if (elapsed_seconds >= time_limit)
        {
            timed_out = true;
            break;
        }
        newOrder = findNextFromMST(currentOrder);
        newCost = getPathCost(newOrder);

        delta = newCost - currentCost;

        if (newCost < bestCost)
        {
            bestOrder = newOrder;
            bestCost = newCost;
        }

        if (delta < 0)
        {
            currentOrder = newOrder;
            currentCost = newCost;
        }
        else
        {
            random = getRandDouble();
            if (random < exp(-delta / temperature))
            {
                currentOrder = newOrder;
                currentCost = newCost;
            }
        }

        temperature *= coolRate;
        ++iterations;
    }
    calculated_at = std::chrono::system_clock::now();
    return bestCost;
}
