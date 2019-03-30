#ifndef QUICKHULL_H
#define QUICKHULL_H

#include "Point.hh"
#include <vector>

using std::vector;

int findSide(Point p1, Point p2, Point p);
int lineDist(Point p1, Point p2, Point p);
void quickHull(vector<Point> a, int n, Point p1, Point p2, int side);
vector<Point> quickHullConvexHull(vector<Point> a, int n);
bool existsInHull(Point p1, vector<Point> a);

#endif
