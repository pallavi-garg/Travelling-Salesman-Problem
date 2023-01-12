#include <iostream>
#include <map>
#include <vector>
#include <string>

#include <bnbagent.h>
#include <slsagent.h>
#include <reader.h>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> time_type;

Graph *Make_Graph(int n, std::vector<std::vector<double>> &inputMatrix)
{
    Graph *graph = new Graph();
    for (int x = 1; x <= n; ++x)
        graph->vertices.push_back(new Vertex(x));

    graph->distanceMatrix = inputMatrix;
    return graph;
}

void print_all_results(std::string file_path, BnbAgent *agent, time_type start_time, bool timed_out, std::vector<std::vector<double>> &inputMatrix)
{
    bnb_result *result = agent->results.back();

    std::string path = std::to_string(agent->startingPoint->id) + "->";
    double cost = 0;
    Vertex *prev = agent->startingPoint;
    while (true)
    {
        Vertex *next = (*(result->path_map))[prev];
        cost += inputMatrix[prev->id - 1][next->id - 1];
        path = path + std::to_string(next->id);
        prev = next;
        if (next->id == agent->startingPoint->id)
        {
            break;
        }
        path += "->";
    }
    // Output format: file_path, timeout, time taken to caluclate result in ms, cost, number of expanded nodes, number of pruned nodes, path
    std::chrono::duration<double> elapsed_seconds = result->calculated_at - start_time;
    std::cout << file_path << ", ";
    if (timed_out)
        std::cout << "timeout, ";
    else
        std::cout << ", ";

    std::cout << elapsed_seconds.count() * 1000 << " ms, " << std::fixed << result->cost << ", " << agent->expanded << ", " << agent->pruned << ", " << path << std::endl;
    for (auto *r : agent->results)
    {
        delete r;
    }
}

void run_bnb(int n, std::vector<std::vector<double>> &inputMatrix, std::string file_path, std::chrono::duration<double> time_limit)
{
    bool timed_out = false;
    BnbAgent *agent = new BnbAgent();
    Graph *graph = Make_Graph(n, inputMatrix);

    time_type start_time = std::chrono::system_clock::now();

    // add 0.0001 so that if initial path taken is the optimal one, then the algo must return it
    double upperBound = agent->CalculateUpperBound(n, inputMatrix) + 0.0001;
    std::map<Vertex *, Vertex *> *result = agent->BranchAndBound(const_cast<Graph *>(graph), upperBound, time_limit, start_time, timed_out);

    if (!result || (int)result->size() != n)
        std::cout << "No solution found." << std::endl;
    else
        print_all_results(file_path, agent, start_time, timed_out, inputMatrix);
    delete result;
    delete agent;
    delete graph;
}

void run_sls(int n, std::vector<std::vector<double>> &inputMatrix, std::chrono::duration<double> time_limit, std::string filename)
{
    time_type start_time = std::chrono::system_clock::now();

    SLSAgent *agent = new SLSAgent(n, inputMatrix);
    double cost = agent->SimulatedAnnealing(start_time, time_limit);
    std::chrono::duration<double> elapsed_seconds = agent->calculated_at - start_time;
    // Output format: file_path, timeout,  time taken to caluclate result in ms, cost, number of iterations taken
    std::cout << filename << ", ";
    if (agent->timed_out)
        std::cout << "timeout, ";
    else
        std::cout << ", ";
    std::cout << cost << ", " << elapsed_seconds.count() * 1000 << "ms, " << agent->iterations << std::endl;
    delete agent;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int n = 0;
        std::vector<std::vector<double>> inputMatrix;
        std::string file_path = std::string(argv[2]);
        filereader *reader = new filereader();
        reader->read_file(file_path, n, inputMatrix);
        delete reader;

        std::string agant_name = std::string(argv[1]);
        std::chrono::duration<double> time_limit(10 * 60);

        if (agant_name == "bnb")
            run_bnb(n, inputMatrix, file_path, time_limit);
        else if (agant_name == "sls")
            run_sls(n, inputMatrix, time_limit, file_path);
        else
            std::cout << "Please provide either bnb or sls as first argument." << std::endl;

        return 0;
    }
}