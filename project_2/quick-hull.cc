// C++ program to implement Quick Hull algorithm
// to find convex hull.
// #include <bits/stdc++.h>
// using namespace std;

// // iPair is integer pairs
// #define iPair pair<int, int>

// // Stores the result (points of convex hull)
// set<iPair> hull;


#include "Point.hh"
#include <vector>
#include <stdlib.h>
#include "quick-hull.hh"

using std::vector;


vector<Point> hull;



// Returns the side of point p with respect to line
// joining points p1 and p2.
int findSide(Point p1, Point p2, Point p)
{
    int val = (p.y - p1.y) * (p2.x - p1.x) -
              (p2.y - p1.y) * (p.x - p1.x);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

// returns a value proportional to the distance
// between the point p and the line joining the
// points p1 and p2
int lineDist(Point p1, Point p2, Point p)
{
    return abs((p.y - p1.y) * (p2.x - p1.x) -
               (p2.y - p1.y) * (p.x - p1.x));
}

// End points of line L are p1 and p2.  side can have value
// 1 or -1 specifying each of the parts made by the line L
void quickHull(vector<Point> a, int n, Point p1, Point p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i = 0; i < n; i++)
    {
        int temp = lineDist(p1, p2, a[i]);
        if (findSide(p1, p2, a[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.push_back(p1);
        hull.push_back(p2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

vector<Point> quickHullConvexHull(vector<Point> a, int n)
{
    // a[i].y -> y-coordinate of the ith point
    if (n < 3)
    {
        throw "Not Possible";
    }

    // Finding the point with minimum and
    // maximum x-coordinate
    int min_x = 0, max_x = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i].x < a[min_x].x)
            min_x = i;
        if (a[i].x > a[max_x].x)
            max_x = i;
    }

    // Recursively find convex hull points on
    // one side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], 1);

    // Recursively find convex hull points on
    // other side of line joining a[min_x] and
    // a[max_x]
    quickHull(a, n, a[min_x], a[max_x], -1);

    return hull;
}
