#ifndef RENDER_H
#define RENDER_H
#include "graphics.h"
#include "Frustum.hpp"
#include <iostream>
#include <vector>
using namespace std;
enum POINTPOS
{
    TOP = 0b1000,
    BOTTOM = 0b0100,
    LEFT = 0b0001,
    RIGHT = 0b0010,
};

class Render
{
private:
    int x;
    int y;
    int width;
    int height;
    Camera *camera;

public:
    Render(int x, int y, int width, int height);
    ~Render();
    void clear(color_t color);
    void draw_line(Point2D &a, Point2D &b, color_t color);
    void draw_triangle(vector<Point3DN> vertices, Mat4 &model, color_t color);
    int get_code(Point2D &p);
    int get_x() { return this->x; }
    int get_y() { return this->y; }
    int get_width() { return this->width; }
    int get_height() { return this->height; }
};
int Render::get_code(Point2D &p)
{
    int code = 0b0000;
    float top = this->y + this->height;
    float bottom = this->y;
    float left = this->x;
    float right = this->x + this->width;
    if (p.get_x() < left)
    {
        code = code | POINTPOS::LEFT;
    }
    if (p.get_x() > right)
    {
        code = code | POINTPOS::RIGHT;
    }
    if (p.get_y() > top)
    {
        code = code | POINTPOS::TOP;
    }
    if (p.get_y() < bottom)
    {
        code = code | POINTPOS::BOTTOM;
    }
    return code;
}
Render::Render(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->camera = new Camera(1.0, width / height, angleToRadian(30.0f));
}

Render::~Render()
{
}
void Render::clear(color_t color)
{
    setbkcolor_f(color);
    cleardevice();
}
void Render::draw_line(Point2D &a, Point2D &b, color_t color)
{
    int code1 = get_code(a);
    int code2 = get_code(b);
    if ((code1 & code2) != 0)
    {
        return;
    }
    while ((code1 != 0) || (code2 != 0))
    {
        float x = -1.0;
        float y = -1.0;
        float x1 = a.get_x();
        float y1 = a.get_y();
        float x2 = b.get_x();
        float y2 = b.get_y();

        int code = code1;
        if ((code1 == 0))
        {
            code = code2;
        }
        if ((code & POINTPOS::LEFT) != 0)
        {
            x = this->x;
            y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        }
        else if ((code & POINTPOS::RIGHT) != 0)
        {
            x = this->x + this->width;
            y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        }
        else if ((code & POINTPOS::TOP) != 0)
        {
            y = this->y + this->height;
            x = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        }
        else if ((code & POINTPOS::BOTTOM) != 0)
        {
            y = this->y;
            x = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        }
        if (code == code1)
        {
            a.set_x((int)x);
            a.set_y((int)y);
            code1 = this->get_code(a);
        }
        else if (code == code2)
        {
            b.set_x((int)x);
            b.set_y((int)y);
            code2 = this->get_code(b);
        }
    }
    setcolor(color);
    ege_line(a.get_x(), a.get_y(), b.get_x(), b.get_y());
}
void Render::draw_triangle(vector<Point3DN> vertices, Mat4 &model, color_t color)
{
    Mat4 &projection = this->camera->get_frustum().get_mat();
    for (auto &point3dn : vertices)
    {
        // point3dn.printxyzw();
        model.dotPoint3DN(point3dn);
        projection.dotPoint3DN(point3dn);
        point3dn.divByW();
        // point3dn.printxyzw();
        float x = (point3dn.get_x() + 1.0) * 0.5 * this->width + this->x - 1.0;
        float y = this->height - (point3dn.get_y() + 1.0) * 0.5 * this->height + this->y + 1.0;
        point3dn.set_withIdx(0, x);
        point3dn.set_withIdx(1, y);
    }
    vector<Point2D> v2D;
    for (int i = 0; i < 3; i++)
    {
        // vertices[i].printxyzw();
        // vertices[(i + 1) % 3].printxyzw();
        Point2D a = Point2D(vertices[i].get_x(), vertices[i].get_y());
        Point2D b = Point2D(vertices[(i + 1) % 3].get_x(), vertices[(i + 1) % 3].get_y());
        draw_line(a, b, color);
        v2D.push_back(a);
    }
    Trapezoid::from_Triangle(v2D);
}
#endif