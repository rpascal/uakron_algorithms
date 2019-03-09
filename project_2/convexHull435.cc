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
#include "Point.hh"
#include "graham-scan.hh"
#include "jarvis-march.hh"
#include "quick-hull.hh"

using std::function;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

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
        std::cout << temp.x << "  " << temp.y << std::endl;
        data.push_back(temp);
    });

    return data;
}

vector<Point> GrahamScan(vector<Point> data, int n);
vector<Point> JarvisMarch(vector<Point> data, int n);
vector<Point> Quickhull(vector<Point> data, int n);

int main(int argc, char *argv[])
{
    //Second project starts here
    if (argc < 3)
        std::cout << "wrong format! should be \"a.exe algType dataFile\"";
    else
    {
        std::string algType = argv[1];
        std::string dataFilename = argv[2];
        std::string outputFile = "";
        //read your data points from dataFile (see class example for the format)

        vector<Point> data = getInputData(dataFilename);

        vector<Point> sortedResult;
        if (data.size() == 0)
        {
            std::cout << "No data could be loaded from input file or input file is empty";
            return 0;
        }

        int n = data.size();

        if (algType[0] == 'G')
        {
            //call your Graham Scan algorithm to solve the problem
            sortedResult = GrahamScan(data, n);

            outputFile = "hull_G.txt";
        }
        else if (algType[0] == 'J')
        {
            //call your Javis March algorithm to solve the problem
            sortedResult = JarvisMarch(data, n);
            outputFile = "hull_J.txt";
        }
        else
        { //default
            //call your Quickhull algorithm to solve the problem
            sortedResult = Quickhull(data, n);
            outputFile = "hull_Q.txt";
        }
        std::cout << std::endl;

        for (Point i : sortedResult)
        {
            std::cout << "(" << i.x << "," << i.y << ")" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Original Size: " << data.size() << " Sorted size:" << sortedResult.size() << std::endl;

        std::cout << outputFile << std::endl;

        //write your convex hull to the outputFile (see class example for the format)
        //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.

        return 0;
    }
}

vector<Point> GrahamScan(vector<Point> data, int n)
{
    vector<Point> sortedResult = grahamScanConvexHull(data, n);
    return sortedResult;
}

vector<Point> JarvisMarch(vector<Point> data, int n)
{
    vector<Point> sortedResult = jarvisMatchConvexHull(data, n);
    return sortedResult;
}

vector<Point> Quickhull(vector<Point> data, int n)
{
    vector<Point> sortedResult = quickHullConvexHull(data, n);
    return sortedResult;
}
