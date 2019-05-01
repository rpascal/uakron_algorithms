/*
    Project 3 for Algorithms
    Ryan Pascal
    2932732
    May 1st, 2019
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
#include <bits/stdc++.h>

using std::function;
using std::getline;
using std::ifstream;
using std::pair;
using std::string;
using std::vector;
string firstRelevantLineText, secondRelevantLineText;

vector<vector<int>> energyData(vector<vector<int>> matrix);
vector<vector<int>> minEnergyM(vector<vector<int>> matrix);
void resizeMatrix(vector<vector<int>> &matix, int width, int height);
void printMatrix(vector<vector<int>> &matrix);
void transpose(vector<vector<int>> &matrix);
pair<int, int> getMinCoordFromAbove(vector<vector<int>> &cumulative, int h, int w);
void getPath(vector<pair<int, int>> &path, vector<vector<int>> &cumulativeMatrix);
void removePath(vector<vector<int>> &matrix, vector<vector<int>> &cumulativeMatrix);
void addPath(vector<vector<int>> &matrix, vector<vector<int>> &cumulativeMatrix);
void alterSeams(vector<vector<int>> &matrix, int seamsToRemove, bool isAdd);
void readData(string fileName, function<void(string &)> lineCallback);
vector<vector<int>> getInputData(string fileName);
void writeMatrixToFile(vector<vector<int>> matix, string fileName, int vertical, int horizontal);

int main(int argc, char *argv[])
{
    if (argc < 4)
        std::cout << "wrong format! should be \"a.exe image.pgm 10 5\"";
    else
    {
        std::string image = argv[1];
        int vertical = std::stoi(argv[2]);
        int horizontal = std::stoi(argv[3]);
        bool isAdd = false;
        if (argc > 4)
        {
            std::string isAddStr = argv[4];
            isAdd = (isAddStr == "a");
        }

        vector<vector<int>> matrix = getInputData(image);

        alterSeams(matrix, vertical, isAdd);
        transpose(matrix);
        alterSeams(matrix, horizontal, isAdd);
        transpose(matrix);

        std::string outputFilename = image.substr(0, image.size() - 4) + "_processed.pgm";

        writeMatrixToFile(matrix, outputFilename, vertical, horizontal);

        return 0;
    }
}

void writeMatrixToFile(vector<vector<int>> matrix, string fileName, int vertical, int horizontal)
{

    std::ofstream outfile;
    outfile.open(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);

    // Generate First 4 lines of information
    outfile << firstRelevantLineText << "\n";
    outfile << "# Generated output " << fileName << ": Removed " << vertical << " vertical and " << horizontal << " horizontal seams" << std::endl;
    outfile << matrix[0].size() << " " << matrix.size() << "\n";
    outfile << secondRelevantLineText << "\n";

    // print the matrix to file
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            outfile << matrix[i][j] << " ";
        }
        outfile << "\n";
    }
    outfile.close();
}

vector<vector<int>> energyData(vector<vector<int>> matrix)
{
    vector<vector<int>> newMatrix;
    int height = matrix.size();
    int width = matrix[0].size();
    resizeMatrix(newMatrix, width, height);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int left = 0, right = 0, top = 0, bottom = 0;
            int curValue = matrix[h][w];
            // e(i,j) = |v(i,j)-v(i-1,j)|+ |v(i,j)-v(i+1,j)|+ |v(i,j)-v(i,j-1)|+ |v(i,j)-v(i,j+1)|,

            if (h - 1 >= 0) // Top
            {
                top = abs(curValue - matrix[h - 1][w]);
            }
            if (h + 1 < height) // Bottom
            {
                bottom = abs(curValue - matrix[h + 1][w]);
            }

            if (w - 1 >= 0) // Left
            {
                left = abs(curValue - matrix[h][w - 1]);
            }
            if (w + 1 < width) // Right
            {
                right = abs(curValue - matrix[h][w + 1]);
            }

            newMatrix[h][w] = left + right + top + bottom;
        }
    }
    return newMatrix;
}

vector<vector<int>> minEnergyM(vector<vector<int>> matrix)
{

    vector<vector<int>> newMatrix;
    int height = matrix.size();
    int width = matrix[0].size();
    resizeMatrix(newMatrix, width, height);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int curValue = matrix[h][w];
            // M(i,j) = e(i,j) + min( M(i-1,j-1), M(i-1,j), M(i-1,j+1) )

            if (h - 1 >= 0) // Top
            {
                int left = INT_MAX, right = INT_MAX, middle = newMatrix[h - 1][w];

                if (w - 1 >= 0) // Left
                {
                    left = newMatrix[h - 1][w - 1];
                }
                if (w + 1 < width) // Right
                {
                    right = newMatrix[h - 1][w + 1];
                }

                curValue += std::min({left, right, middle});
            }

            newMatrix[h][w] = curValue;
        }
    }
    return newMatrix;
}

void resizeMatrix(vector<vector<int>> &matix, int width, int height)
{
    matix.resize(height);
    for (int i = 0; i < height; i++)
    {
        matix[i].resize(width);
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

void transpose(vector<vector<int>> &matrix)
{
    int width = matrix[0].size();
    int height = matrix.size();
    vector<vector<int>> transposedMatrix;
    resizeMatrix(transposedMatrix, height, width);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    matrix = transposedMatrix;
}

pair<int, int> getMinCoordFromAbove(vector<vector<int>> &cumulative, int i, int j)
{
    std::pair<int, int> min;
    min.first = i - 1;
    min.second = j;
    if (j != 0)
    {
        //Left
        min.second = j - 1;
    }
    if (cumulative[min.first][j] < cumulative[min.first][min.second])
    {
        //Middle
        min.second = j;
    }
    if (j != cumulative[i].size() - 1 && cumulative[min.first][j + 1] < cumulative[min.first][min.second])
    {
        //Right
        min.second = j + 1;
    }

    return min;
}

void getPath(vector<pair<int, int>> &path, vector<vector<int>> &cumulativeMatrix)
{
    int height = cumulativeMatrix.size();

    // Find the indexes of the bottom row
    pair<int, int> minInLastRow;
    minInLastRow.first = height - 1;
    minInLastRow.second = 0;
    for (int j = 1; j < cumulativeMatrix[0].size(); j++)
    {
        if (cumulativeMatrix[0][j] < cumulativeMatrix[0][minInLastRow.second])
        {
            minInLastRow.second = j;
        }
    }

    // Find the path from bottom up to remove
    path.push_back(minInLastRow);
    for (int i = height - 1; i > 0; i--)
    {
        path.push_back(getMinCoordFromAbove(cumulativeMatrix, path.back().first, path.back().second));
    }
}

void removePath(vector<vector<int>> &matrix, vector<vector<int>> &cumulativeMatrix)
{
    vector<pair<int, int>> minPath;

    getPath(minPath, cumulativeMatrix);

    // Remove the path
    for (int i = 0; i < minPath.size(); i++)
    {
        int x = minPath[i].first;
        int y = minPath[i].second;
        matrix[x].erase(matrix[x].begin() + y);
    }
}

void addPath(vector<vector<int>> &matrix, vector<vector<int>> &cumulativeMatrix)
{

    int height = matrix.size();
    int width = matrix[0].size();

    vector<pair<int, int>> minPath;

    getPath(minPath, cumulativeMatrix);

    // Remove the path
    for (int i = 0; i < minPath.size(); i++)
    {
        int h = minPath[i].first;
        int w = minPath[i].second;

        int count = 0;
        int left = 0, right = 0, top = 0, bottom = 0;

        if (h - 1 >= 0) // Top
        {
            top = matrix[h - 1][w];
            count++;
        }
        if (h + 1 < height) // Bottom
        {
            bottom = matrix[h + 1][w];
            count++;
        }

        if (w - 1 >= 0) // Left
        {
            left = matrix[h][w - 1];
            count++;
        }
        if (w + 1 < width) // Right
        {
            right = matrix[h][w + 1];
            count++;
        }

        int average = (top + bottom + left + right) / count;
        matrix[h].insert(matrix[h].begin() + w, average);
    }
}

void alterSeams(vector<vector<int>> &matrix, int seamsToRemove, bool isAdd)
{
    vector<vector<int>> energyMatrix, cumulativeMatrix;

    for (int count = 0; count < seamsToRemove; count++)
    {
        energyMatrix = energyData(matrix);
        cumulativeMatrix = minEnergyM(energyMatrix);
        if (!isAdd)
        {
            removePath(matrix, cumulativeMatrix);
        }
        else
        {
            addPath(matrix, cumulativeMatrix);
        }
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

vector<vector<int>> getInputData(string fileName)
{
    int height;
    int width;
    int lineNumber = 1;

    std::list<int> dataPoints;

    readData(fileName, [&](string &line) {
        if (line[0] == '#')
        {
            return;
        }
        if (lineNumber == 1)
        {
            firstRelevantLineText = line;
        }
        else if (lineNumber == 2)
        {
            std::istringstream iss(line);
            std::string s;
            iss >> s;
            width = std::stoi(s);
            iss >> s;
            height = std::stoi(s);
        }
        else if (lineNumber == 3)
        {
            secondRelevantLineText = line;
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

    vector<vector<int>> matrix;

    resizeMatrix(matrix, width, height);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            matrix[h][w] = dataPoints.front();
            dataPoints.pop_front();
        }
    }

    return matrix;
}