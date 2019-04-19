/*
    Project 2 for Algorithms
    Ryan Pascal
    2932732
    April 3rd, 2019
*/

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <list>
#include <cstdlib>
#include <algorithm>

using std::function;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

struct DataStruct
{
    vector<vector<int>> data;
    int height;
    int width;
};

DataStruct energyData(DataStruct data);
DataStruct minEnergyM(DataStruct e);

void resizeVector(vector<vector<int>> &m, int width, int height)
{
    m.resize(height);
    for (int i = 0; i < height; i++)
    {
        m[i].resize(width);
    }
}

void printMatrix(vector<vector<int>> &matrix)
{
    int height = matrix.size();
    int width = matrix[0].size();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void transpose(DataStruct &data)
{
    vector<vector<int>> transposedMatrix;
    resizeVector(transposedMatrix, data.width, data.height);
    for (int i = 0; i < data.height; i++)
        for (int j = 0; j < data.width; j++)
            transposedMatrix[j][i] = data.data[i][j];\

    data.data = transposedMatrix;
}

// Returns the coordinates in the cumulative energy matrix of the minimum value in one row
std::pair<int, int> minCoords(std::vector<std::vector<int> > &cumulative, int i) {
    std::pair<int, int> min;
    min.first = i;
    min.second = 0;
    for (int j = 1; j < cumulative[i].size(); j++)
        if (cumulative[i][j] < cumulative[i][min.second])
            min.second = j;

    return min;
}

// Returns the coordinates in the cumulative energy matrix of the least of the 3 entries above the number at i, j
std::pair<int, int> minCoodsFromAbove(std::vector<std::vector<int> > &cumulative, int i, int j) {
    std::pair<int, int> min;
    min.first = i - 1;
    // There will always be an element above this one, so default min j to it just in case
    min.second = j;
    if (j != 0)
        min.second = j - 1;
    if (cumulative[i-1][j] < cumulative[min.first][min.second])
        min.second = j;
    if (j != cumulative[i].size() - 1)
        if (cumulative[i-1][j+1] < cumulative[min.first][min.second])
            min.second = j + 1;

    return min;
}

// Trace up from bottom and find the path of the lowest numbers
std::vector<std::pair<int, int> > findMinPath(std::vector<std::vector<int> > &cumulativeMatrix) {
    int height = cumulativeMatrix.size();
    std::vector<std::pair<int, int> > path;
    path.push_back(minCoords(cumulativeMatrix, height - 1));
    for (int i = height - 1; i > 0; i--)
        path.push_back(minCoodsFromAbove(cumulativeMatrix, path.back().first, path.back().second));

    return path;
}

// Removes the elements specified in the minPath
void removeMinPath(std::vector<std::vector<int> > &matrix, std::vector<std::pair<int, int> > &minPath) {
    for (int i = 0; i < minPath.size(); i++)
        matrix[minPath[i].first].erase(matrix[minPath[i].first].begin() + minPath[i].second);
}



// Main function to consolidate seam-removal functions
void removeSeams(DataStruct &data, int seams) {
    DataStruct energyMatrix, cumulativeMatrix;
    vector<std::pair<int, int> > minPath;

    // remove "seams" amount of seams 
    for (int count = 0; count < seams; count++) {
        energyMatrix = energyData(data);
        cumulativeMatrix = minEnergyM(energyMatrix);
        minPath = findMinPath(cumulativeMatrix.data);
        removeMinPath(data.data, minPath);
    }
}

void readData(string fileName, function<void(string &)> lineCallback)
{
    ifstream input;
    input.open(fileName);
    string line;

    //Loop over each line in input
    while (getline(input, line))
    {
        lineCallback(line);
    }
}

DataStruct getInputData(string fileName)
{
    int height;
    int width;
    int lineNumber = 1;

    std::cout << "Line NUmber: " << lineNumber << "  fileName: " << fileName << std::endl;

    std::list<int> dataPoints;

    readData(fileName, [&](string &line) {
        if (lineNumber == 1)
        {
        }
        else if (lineNumber == 2)
        {
        }
        else if (lineNumber == 3)
        {
            std::istringstream iss(line);
            std::string s;
            iss >> s;
            width = std::stoi(s);
            iss >> s;
            height = std::stoi(s);
            std::cout << "Width:" << width << "  Height:" << height << std::endl;
        }
        else if (lineNumber == 4)
        {
        }
        else
        {
            std::istringstream iss(line);
            std::string s;
            while (iss >> s)
            {
                dataPoints.push_back(std::stoi(s));
            }
        }

        lineNumber++;
    });

    std::cout << "Data Points: " << dataPoints.size() << std::endl;

    vector<vector<int>> data;

    resizeVector(data, width, height);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            data[h][w] = dataPoints.front();
            dataPoints.pop_front();
        }
    }

    DataStruct ret;
    ret.data = data;
    ret.height = height;
    ret.width = width;

    return ret;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
        std::cout << "wrong format! should be \"a.exe image.pgm 10 5\"";
    else
    {
        std::string image = argv[1];
        int vertical = std::stoi(argv[2]);
        int horizontal = std::stoi(argv[3]);

        DataStruct data = getInputData(image);

        printMatrix(data.data);

        std::cout << "----------------------------------------------------" << std::endl;

        DataStruct enData = energyData(data);

        printMatrix(enData.data);

        std::cout << "----------------------------------------------------" << std::endl;

        DataStruct mData = minEnergyM(enData);

        printMatrix(mData.data);

        std::cout << "hello world " << image << "  " << vertical << "   " << horizontal << std::endl;
        return 0;
    }
}

DataStruct energyData(DataStruct oldData)
{
    vector<vector<int>> data;
    resizeVector(data, oldData.width, oldData.height);

    for (int h = 0; h < oldData.height; h++)
    {
        for (int w = 0; w < oldData.width; w++)
        {
            int left = 0, right = 0, top = 0, bottom = 0;
            int curValue = oldData.data[h][w];
            // e(i,j) = |v(i,j)-v(i-1,j)|+ |v(i,j)-v(i+1,j)|+ |v(i,j)-v(i,j-1)|+ |v(i,j)-v(i,j+1)|,

            if (h - 1 >= 0) // Top
            {
                top = abs(curValue - oldData.data[h - 1][w]);
            }
            if (h + 1 < oldData.height) // Bottom
            {
                bottom = abs(curValue - oldData.data[h + 1][w]);
            }

            if (w - 1 >= 0) // Left
            {
                left = abs(curValue - oldData.data[h][w - 1]);
            }
            if (w + 1 < oldData.width) // Right
            {
                right = abs(curValue - oldData.data[h][w + 1]);
            }

            data[h][w] = left + right + top + bottom;
        }
    }

    DataStruct ret;
    ret.data = data;
    ret.height = oldData.height;
    ret.width = oldData.width;

    return ret;
}

DataStruct minEnergyM(DataStruct e)
{

    vector<vector<int>> M;
    resizeVector(M, e.width, e.height);

    for (int h = 0; h < e.height; h++)
    {
        for (int w = 0; w < e.width; w++)
        {
            int curValue = e.data[h][w];
            // M(i,j) = e(i,j) + min( M(i-1,j-1), M(i-1,j), M(i-1,j+1) )

            if (h - 1 >= 0) // Top
            {
                int left = 9999999, right = 9999999, middle = M[h - 1][w];

                if (w - 1 >= 0) // Left
                {
                    left = M[h - 1][w - 1];
                }
                if (w + 1 < e.width) // Right
                {
                    right = M[h - 1][w + 1];
                }

                curValue += std::min({left, right, middle});
            }

            M[h][w] = curValue;
        }
    }

    DataStruct ret;
    ret.data = M;
    ret.height = e.height;
    ret.width = e.width;

    return ret;
}