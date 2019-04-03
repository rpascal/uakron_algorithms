#include "Point.hh"
#include <vector>
#include <stdlib.h>
#include <algorithm> // std::find
#include "quick-hull.hh"
#include<cmath> //sqrt

using std::vector;

vector<Point> hull;

bool sort_by_x(Point a, Point b)
{
    return (a.x < b.x);
}

/*--------------------- Point operations ----------------------*/
// sums two vectors
Point vector_sum(Point a, Point b)
{
    Point sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    return sum;
}

// the product of a vector by a scalar
Point scalar_product(double l, Point a)
{
    Point product;
    product.x = l * a.x;
    product.y = l * a.y;
    return product;
}

// cross product (only Z-axis value)
double cross_product(Point a, Point b)
{
    return (((a.x) * (b.y)) - ((b.x) * (a.y)));
}

// dot product
double dot_product(Point a, Point b)
{
    return (((a.x) * (b.x)) + ((a.y) * (b.y)));
}

// euclidean norm: || . ||
double norm(Point a)
{
    return (sqrt(dot_product(a, a)));
}

// euclidean distance: || b - a ||
double euclidean_distance(Point a, Point b)
{
    return (norm(vector_sum(b, scalar_product(-1, a))));
}

// the shortest distance between a point and a line (defined by two points)
// see references (1)
double line_distance(Point a, Point p1, Point p2)
{
    return (abs(((p2.y - p1.y) * a.x) - ((p2.x - p1.x) * a.y) + (p2.x * p1.y) - (p2.y * p1.x)) / euclidean_distance(p1, p2));
}
/*-------------------------------------------------------------*/

/*-------------------- auxiliary functions --------------------*/
// says if a point a is at the left side, right side or ir colinear to the oriented line p1->p2
// see references (2)
int set_local(Point a, Point p1, Point p2)
{
    //calculates:	p1->p2 x p1->a (the cross product between the vectors)
    double position = cross_product((vector_sum(p2, scalar_product(-1, p1))), (vector_sum(a, scalar_product(-1, p1))));
    if (position > 0)
    {
        return -1; //point c is at the left of the line p2->p1
    }
    else if (position < 0)
    {
        return 1; //point c is at the left of the line p1->p2
    }
    return 0; //the point c is collinear to the line p1->p2
}

//returns the farthest point from a Set of points and a line (defined by two points)
Point farthest_point(vector<Point> S, Point p1, Point p2)
{
    double max_value = 0, aux;
    Point max_point;
    //caculates and compares distance of points
    for (auto i = S.begin(); i != S.end(); ++i)
    {
        aux = line_distance((*i), p1, p2);
        if (max_value <= aux)
        {
            max_value = aux;
            max_point = (*i);
        }
    }
    return max_point;
}

//find the set of points at the left side of a line (defined by two points)
void find_left_set(vector<Point> P, vector<Point> &S, Point p1, Point p2)
{
    int flag;
    for (auto i = P.begin(); i != P.end(); ++i)
    {
        flag = set_local((*i), p1, p2);
        if (flag == 1)
        {
            S.push_back(*i);
        }
    }
}
/*-------------------------------------------------------------*/

/*-------------------- The QuickHull Algorithm Functions --------------------*/
/*---------------------------- see reference (0) ----------------------------*/
void find_hull_quick(vector<Point> &CH, vector<Point> S, Point p1, Point p2)
{
    //creates two regions
    vector<Point> S1, S2;
    //the farthest point
    Point c;

    //if S is empty there's no hull to be found
    if (S.empty())
        return;

    //finds the farthest point from the line p1->p2
    c = farthest_point(S, p1, p2);

    //separates the set S in three regions
    find_left_set(S, S1, p1, c);
    find_left_set(S, S2, c, p2);

    find_hull_quick(CH, S1, p1, c);
    CH.push_back(c); //important to be here due to printing order
    find_hull_quick(CH, S2, c, p2);
}

void quick_hull(vector<Point> &CH, vector<Point> P)
{
    //ordering the input by its x-axis coordenate
    sort(P.begin(), P.end(), sort_by_x);

    //gets the x with smallest and biggest value (left and right most)
    Point min = *(P.begin());
    Point max = *((P.end() - 1));

    vector<Point> S1, S2;

    //S1: points at the left of line min->max
    find_left_set(P, S1, min, max);
    //S2: points at the left of line max->min
    find_left_set(P, S2, max, min);

    //adds left most point to the convex hull
    CH.push_back(min); //important to be here due to printing order

    find_hull_quick(CH, S1, min, max);

    //adds right most point to the convex hull
    CH.push_back(max); //important to be here due to printing order

    find_hull_quick(CH, S2, max, min);

    CH.push_back(min); //important to be here due to printing order
}
/*-------------------------------------------------------------*/

vector<Point> quickHullConvexHull(vector<Point> a, int n)
{
    // a[i].y -> y-coordinate of the ith point
    if (n < 3)
    {
        throw "Not Possible";
    }

    vector<Point> convex_hull;
    quick_hull(convex_hull, a);

    return convex_hull;
}
