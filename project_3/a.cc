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
    int **data;
    int height;
    int width;
};

DataStruct energyData(DataStruct data);
DataStruct minEnergyM(DataStruct e);

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

    int **data = 0;
    data = new int *[height];

    for (int h = 0; h < height; h++)
    {
        data[h] = new int[width];

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
        int **my2DArray = data.data;

        for (int h = 0; h < data.height; h++)
        {
            for (int w = 0; w < data.width; w++)
            {
                printf("%i ", my2DArray[h][w]);
            }
            printf("\n");
        }

        std::cout << "----------------------------------------------------" << std::endl;

        DataStruct enData = energyData(data);
        for (int h = 0; h < enData.height; h++)
        {
            for (int w = 0; w < enData.width; w++)
            {
                printf("%i ", enData.data[h][w]);
            }
            printf("\n");
        }

        std::cout << "----------------------------------------------------" << std::endl;

        DataStruct mData = minEnergyM(enData);
        for (int h = 0; h < mData.height; h++)
        {
            for (int w = 0; w < mData.width; w++)
            {
                printf("%i ", mData.data[h][w]);
            }
            printf("\n");
        }

        std::cout << "hello world " << image << "  " << vertical << "   " << horizontal << std::endl;
        return 0;
    }
}

DataStruct energyData(DataStruct oldData)
{
    int **data = 0;
    data = new int *[oldData.height];

    for (int h = 0; h < oldData.height; h++)
    {
        data[h] = new int[oldData.width];

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
    int **M = 0;
    M = new int *[e.height];

    for (int h = 0; h < e.height; h++)
    {
        M[h] = new int[e.width];

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