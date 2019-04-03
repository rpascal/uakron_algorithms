// You need to complete this program for your second project.

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

#include "Point.hh"
#include "graham-scan.hh"
#include "jarvis-march.hh"
#include "quick-hull.hh"

using std::function;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

struct HullSortResult
{
    double runtime;
    vector<Point> sortedData;
    string outputFileName;
};

double runtime(clock_t start, clock_t stop);
void testRuntimes();
HullSortResult runHullSort(string algType, vector<Point> data);
void writeSorted(string name, vector<Point> data);

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

vector<Point> getInputData(string fileName)
{
    vector<Point> data;

    readData(fileName, [&](string &line) {
        Point temp;
        std::istringstream iss(line);
        std::string s;
        iss >> s;
        temp.x = std::stoi(s);
        iss >> s;
        temp.y = std::stoi(s);
        data.push_back(temp);
    });

    return data;
}

int main(int argc, char *argv[])
{
    std::string str1("testRuntimes");

    if (argc == 2 && str1.compare(argv[1]) == 0)
    {
        testRuntimes();
        return 0;
    }
    else if (argc < 3)
        std::cout << "wrong format! should be \"a.exe algType dataFile\"";
    else
    {
        std::string algType = argv[1];
        std::string dataFilename = argv[2];

        vector<Point> data = getInputData(dataFilename);

        if (data.size() == 0)
        {
            std::cout << "No data could be loaded from input file or input file is empty";
            return 0;
        }
        HullSortResult res = runHullSort(algType, data);
        writeSorted(res.outputFileName, res.sortedData);
        return 0;
    }
}

/*
    Calculate runtime
*/
double runtime(clock_t start, clock_t stop)
{
    return double(stop - start) / double(CLOCKS_PER_SEC);
}

/*
    Function to run the convex hull with a parameter to specify what algorithm type to use
*/
HullSortResult runHullSort(string algType, vector<Point> data)
{
    clock_t start, stop;

    vector<Point> sortedResult;
    std::string outputFile = "";

    int n = data.size();
    start = clock();

    if (algType[0] == 'G')
    {
        //call your Graham Scan algorithm to solve the problem
        sortedResult = grahamScanConvexHull(data, n);
        outputFile = "hull_G.txt";
    }
    else if (algType[0] == 'J')
    {
        //call your Javis March algorithm to solve the problem
        sortedResult = jarvisMatchConvexHull(data, n);
        outputFile = "hull_J.txt";
    }
    else
    {
        //call your Quickhull algorithm to solve the problem
        sortedResult = quickHullConvexHull(data, n);
        outputFile = "hull_Q.txt";
    }

    stop = clock();
    double rt = runtime(start, stop);

    HullSortResult res;
    res.outputFileName = outputFile;
    res.runtime = rt;
    res.sortedData = sortedResult;
    return res;
}

/*
    Function used to test all the different cases in one go and
    output the runtimes to a text file. To utilize this function all the 
    input data files must be pre-generated to be pulled from.
*/
void testRuntimes()
{
    string algTypes[3] = {"G", "J", "Q"};
    string types[4] = {"circle", "onCircle", "rectangle", "triangle"};
    string points[5] = {"10", "1000", "10000", "100000", "1000000"};

    int i, j, k;

    std::ofstream outFile;
    outFile.open("runtimeResults.txt");

    for (k = 0; k < 3; ++k)
    {
        string algType = algTypes[k];
        outFile << "Algo Type: " << algType << "\n";
        for (i = 0; i < 4; ++i)
        {
            string type = types[i];
            outFile << "    Type: " << type << "\n";

            for (j = 0; j < 5; ++j)
            {
                string point = points[j];
                string dataFilename = "./GUI4ConvexHall/data/" + type + "_" + point + ".txt";
                vector<Point> data = getInputData(dataFilename);
                HullSortResult res = runHullSort(algType, data);
                outFile << "        Points: " << point << " runtime: " << res.runtime << "\n";
                writeSorted("./GUI4ConvexHall/data/sorted/_sorted_" + algType + "_" + type + "_" + point + ".txt", res.sortedData);
            }
        }
    }

    outFile.close();
}

/*
    Wrties the sorted data to a text file
*/
void writeSorted(string name, vector<Point> data)
{

    std::ofstream outFile;
    outFile.open(name);

    std::size_t i;
    std::size_t size = data.size();
    for (i = 0; i < size; ++i)
    {
        Point point = data[i];
        outFile << point.x << " " << point.y;
        if (i != size - 1)
        {
            outFile << "\n";
        }
    }

    outFile.close();
}