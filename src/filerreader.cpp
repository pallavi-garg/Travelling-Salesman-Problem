#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <reader.h>

void filereader::read_file(std::string filePath, int &n, std::vector<std::vector<double>> &input_matrix)
{
    std::string line = "";
    std::ifstream dataFile;
    dataFile.open(filePath);
    
    if (dataFile.is_open())
    {
        std::getline(dataFile, line);
        n = std::stoi(line);
        int length = 0;
        std::string data = "";
        std::vector<double> line_data;
        while (dataFile.good())
        {
            std::getline(dataFile, line);
            length = line.length();
            for (int i = 0; i < length; ++i)
            {
                if (line[i] != ' ')
                    data += line[i];
                else
                {
                    line_data.push_back(std::stod(data));
                    data = "";
                }
            }
            if(data.length() > 0)
                line_data.push_back(std::stod(data));
            data = "";
            input_matrix.push_back(line_data);
            line_data.erase(line_data.begin(), line_data.end());
        }
    }
    dataFile.close();
}