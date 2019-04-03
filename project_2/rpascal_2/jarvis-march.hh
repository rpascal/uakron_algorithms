#ifndef JARVISMARCH_H
#define JARVISMARCH_H

#include "Point.hh"
#include <vector>
using std::vector;

int orientationJarvis(Point p, Point q, Point r);
vector<Point> jarvisMatchConvexHull(vector<Point> points, int n);

#endif
