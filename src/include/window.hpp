#ifndef WINDOW_H
#define WINDOW_H
#include "render.hpp"
#include "graphics.h"
class Window
{
private:
    int width;
    int height;
    Render *render;

public:
    Window(int width, int height);
    ~Window();
    void open();
    void play();
    void close();
};

Window::Window(int width, int height)
{
    this->width = width;
    this->height = height;
    this->render = new Render(50, 50, width - 100, height - 100);
}

Window::~Window()
{
}
void Window::open()
{
    initgraph(this->width, this->height);
}
void Window::play()
{
    circle(320, 240, 120);
    // this->render->clear(WHITE);
    Point3DN a = Point3DN(-1.0, 1.0, -2.0, 1.0);
    Point3DN b = Point3DN(1.0, 1.0, -2.0, 1.0);
    Point3DN c = Point3DN(0.0, -1.0, -2.0, 1.0);
    vector<Point3DN> t;
    t.push_back(a);
    t.push_back(b);
    t.push_back(c);
    Mat4 model;
    model.Identity();
    this->render->draw_triangle(t, model, GREEN);
    getch();
}
void Window::close()
{
    closegraph();
    delete this->render;
}
#endif