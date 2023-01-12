#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class filereader
{
public:
    void read_file(std::string filePath, int &n, std::vector<std::vector<double>> &input_matrix);
};

#endif