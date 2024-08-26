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
    Edge() {};
    Edge(Point2D &a, Point2D &b)
    {
        this->v1 = Point2D(a.get_x(), a.get_y());
        this->v2 = Point2D(b.get_x(), b.get_y());
    };
    void printEdge()
    {
        cout << "Edge:{";
        this->v1.printPoint2D();
        this->v2.printPoint2D();
        cout << "}" << endl;
    }
    Point2D &get_v1() { return this->v1; };
    Point2D &get_v2() { return this->v2; };
};
class Trapezoid
{
private:
    int top, bottom;
    Edge left, right;

public:
    Trapezoid() {};
    int get_top() { return this->top; };
    int get_bottom() { return this->bottom; };
    void set_top(int top) { this->top = top; };
    void set_bottom(int bottom) { this->bottom = bottom; };
    void set_left(Edge left) { this->left = left; };
    void set_right(Edge right) { this->right = right; };
    void cal_point(Point2D &a, Point2D &b, int y);
    static vector<Trapezoid> from_Triangle(vector<Point2D> vertices);
};
void Trapezoid::cal_point(Point2D &a, Point2D &b, int y)
{
    int yc = this->left.get_v2().get_y();
    int xa = this->left.get_v1().get_x();
    int xc = this->left.get_v2().get_x();

    int xd = this->right.get_v2().get_x();
    int yd = this->right.get_v2().get_y();
    int xb = this->right.get_v1().get_x();

    int x1 = xc + float(y - yc) * (xa - xc) / (this->top - this->bottom);
    int x2 = xd - float(y - yd) * (xd - xb) / (this->top - this->bottom);

    a.set_x(x1);
    b.set_x(x2);
}
vector<Trapezoid> Trapezoid::from_Triangle(vector<Point2D> vertices)
{
    std::sort(vertices.begin(), vertices.end(), [](Point2D &a, Point2D &b)
              { return a.get_y() > b.get_y(); });
    // 判断是否退化成直线
    Point2D &a = vertices[0];
    Point2D &b = vertices[1];
    Point2D &c = vertices[2];
    // a.printPoint2D();
    // b.printPoint2D();
    // c.printPoint2D();
    vector<Trapezoid> res;
    res.clear();
    if ((a.get_y() - b.get_y()) * (a.get_x() - b.get_x()) == (a.get_y() - c.get_y()) * (a.get_x() - c.get_x()))
        return res;
    if (a.get_y() == b.get_y())
    {
        if (a.get_x() > b.get_x())
        {
            int tmp = a.get_x();
            a.set_x(b.get_x());
            b.set_x(tmp);
        }
        Trapezoid TopFlat;
        TopFlat.set_top(a.get_y());
        TopFlat.set_bottom(c.get_y());
        TopFlat.set_left(Edge(a, c));
        TopFlat.set_right(Edge(b, c));
        res.push_back(TopFlat);
        return res;
    }
    if (b.get_y() == c.get_y())
    {
        if (b.get_x() > c.get_x())
        {
            int tmp = b.get_x();
            b.set_x(c.get_x());
            c.set_x(tmp);
        }
        Trapezoid BottomFlat;
        BottomFlat.set_top(a.get_y());
        BottomFlat.set_bottom(c.get_y());
        BottomFlat.set_left(Edge(a, b));
        BottomFlat.set_right(Edge(a, c));
        res.push_back(BottomFlat);
        return res;
    }
    int x;
    if (a.get_x() == c.get_x())
    {
        x = a.get_x();
    }
    else
    {
        x = a.get_x() + float((b.get_y() - a.get_y()) * (c.get_x() - a.get_x())) / (c.get_y() - a.get_y());
    }
    Point2D d(x, b.get_y());
    if (x < b.get_x())
    {
        Trapezoid TopFlat, BottomFlat;
        TopFlat.set_top(a.get_y());
        TopFlat.set_bottom(b.get_y());
        TopFlat.set_left(Edge(a, d));
        TopFlat.set_right(Edge(a, b));
        res.push_back(TopFlat);
        BottomFlat.set_top(b.get_y());
        BottomFlat.set_bottom(c.get_y());
        BottomFlat.set_left(Edge(d, c));
        BottomFlat.set_right(Edge(b, c));
        res.push_back(BottomFlat);
        return res;
    }
    else
    {
        Trapezoid TopFlat, BottomFlat;
        TopFlat.set_top(a.get_y());
        TopFlat.set_bottom(b.get_y());
        TopFlat.set_left(Edge(a, b));
        TopFlat.set_right(Edge(a, d));
        res.push_back(TopFlat);
        BottomFlat.set_top(b.get_y());
        BottomFlat.set_bottom(c.get_y());
        BottomFlat.set_left(Edge(b, c));
        BottomFlat.set_right(Edge(d, c));
        res.push_back(BottomFlat);
        return res;
    }
    return res;
}
#endif