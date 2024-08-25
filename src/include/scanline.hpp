#ifndef SCANLINE_H
#define SCANLINE_H
#include <vector>
#include <algorithm>
#include "MyMath.hpp"
class Edge
{
private:
    Point2D v1;
    Point2D v2;

public:
    Edge(Point2D a, Point2D b) : v1(a), v2(b) {};
};
class Trapezoid
{
private:
    int top, bottom;
    Edge left, right;

public:
    static vector<Trapezoid> from_Triangle(vector<Point2D> vertices);
};
vector<Trapezoid> Trapezoid::from_Triangle(vector<Point2D> vertices)
{
    std::sort(vertices.begin(), vertices.end(), [](Point2D &a, Point2D &b)
              { return a.get_y() > b.get_y(); });
    // 判断是否退化成直线
    Point2D &a = vertices[0];
    Point2D &b = vertices[1];
    Point2D &c = vertices[2];
    vector<Trapezoid> res;
    res.clear();
    if ((a.get_y() - b.get_y()) * (a.get_x() - b.get_x) == (a.get_y() - c.get_y()) * (a.get_x() - c.get_x))
        return res;
    return res;
}
#endif