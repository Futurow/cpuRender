#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>
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
    Point3DN a = Point3DN(-1.0, 1.0, -2.0, 1.0);
    Point3DN b = Point3DN(1.0, 1.0, -2.0, 1.0);
    Point3DN c = Point3DN(0.0, -1.0, -2.0, 1.0);
    Point3DN a0 = Point3DN(0.0, 0.0, 0.0, 1.0);
    Point3DN b0 = Point3DN(0.0, -1.0, -2.0, 1.0);
    Point3DN c0 = Point3DN(0.0, 1.0, -2.0, 1.0);
    // Point3DN a0 = Point3DN(-1.0, -1.0, -2.0, 1.0);
    // Point3DN b0 = Point3DN(1.0, -1.0, -2.0, 1.0);
    // Point3DN c0 = Point3DN(0.0, 1.0, -2.0, 1.0);
    vector<Point3DN> t, t0;
    t.push_back(a);
    t.push_back(b);
    t.push_back(c);
    t0.push_back(a0);
    t0.push_back(b0);
    t0.push_back(c0);
    float angle = 0.0;
    while (1)
    {
        Mat4 rotation = Mat4::RotationY(angle);
        Mat4 translation1 = Mat4::Translation(0.0, 0.0, 2.0);
        Mat4 translation2 = Mat4::Translation(0.0, 0.0, -4.0);
        // Mat4 srt = Mat4::dot(rotation, translation1);
        Mat4 srt = Mat4::dot(translation2, rotation);
        // srt = Mat4::dot(translation2, srt);
        this->render->draw_triangle(t, srt, GREEN);
        this->render->draw_triangle(t0, srt, RED);
        getch();
        // Sleep(100);
        this->render->clear(BLACK);
        angle += 2.0;
    }
}
void Window::close()
{
    closegraph();
    delete this->render;
}
#endif