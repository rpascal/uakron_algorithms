#ifndef QUICKHULL_H
#define QUICKHULL_H

#include "Point.hh"
#include <vector>

using std::vector;


bool sort_by_x(Point a, Point b);
Point vector_sum(Point a, Point b);
Point scalar_product(double l, Point a);
double cross_product(Point a, Point b);
double dot_product(Point a, Point b);
double norm(Point a);
double euclidean_distance(Point a, Point b);
double line_distance(Point a, Point p1, Point p2);
int set_local(Point a, Point p1, Point p2);
Point farthest_point(vector<Point> S, Point p1, Point p2);
void find_left_set(vector<Point> P, vector<Point> &S, Point p1, Point p2);
void find_hull_quick(vector<Point> &CH, vector<Point> S, Point p1, Point p2);
void quick_hull(vector<Point> &CH, vector<Point> P);
vector<Point> quickHullConvexHull(vector<Point> a, int n);

#endif
