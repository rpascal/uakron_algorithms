

#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include <iostream>
#include <stack>
#include <stdlib.h>
#include "Point.hh"
#include <vector>

Point nextToTop(std::stack<Point> &S);
void swap(Point &p1, Point &p2);
int distSq(Point p1, Point p2);
int orientationGraham(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);
std::vector<Point> grahamScanConvexHull(std::vector<Point> points, int n);

#endif
