#ifndef MATH_H
#define MATH_H
#include <iostream>
using namespace std;
class Point2D
{
private:
    int x;
    int y;

public:
    Point2D(int x, int y);
    Point2D();
    int get_x() { return this->x; };
    int get_y() { return this->y; };
    void set_x(int x) { this->x = x; };
    void set_y(int y) { this->y = y; };
};
Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
}
class Point3DN
{
private:
    int p[4];

public:
    Point3DN(float x, float y, float z, float w);
    void printxyzw();
    float get_withIdx(int idx);
    void set_withIdx(int idx, float val);
    float get_x() { return this->p[0]; };
    float get_y() { return this->p[1]; };
    float get_z() { return this->p[1]; };
    float get_w() { return this->p[3]; };
};

Point3DN::Point3DN(float x, float y, float z, float w)
{
    this->p[0] = x;
    this->p[1] = y;
    this->p[2] = z;
    this->p[3] = w;
}
void Point3DN::printxyzw()
{
    cout << "point3dn:";
    for (int i = 0; i < 4; i++)
    {
        cout << this->p[i] << ',';
    }
    cout << endl;
}
inline float Point3DN::get_withIdx(int idx)
{
    return this->p[idx];
}
inline void Point3DN::set_withIdx(int idx, float val)
{
    this->p[idx] = val;
}
class Mat4
{
private:
    float matrix[4][4] = {0};

public:
    void Identity();
    void PrintMat();
    void Scaled(float Sx, float Sy, float Sz);
    void dotPoint3DN(Point3DN &point);
};

inline void Mat4::Identity()
{
    for (int i = 0; i < 4; i++)
        this->matrix[i][i] = 1;
}
void Mat4::Scaled(float Sx, float Sy, float Sz)
{
    this->matrix[0][0] *= Sx;
    this->matrix[1][1] *= Sy;
    this->matrix[2][2] *= Sz;
}
void Mat4::PrintMat()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << this->matrix[i][j] << ',';
        }
        cout << endl;
    }
}
void Mat4::dotPoint3DN(Point3DN &point)
{
    float t[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i] += this->matrix[i][j] * point.get_withIdx(j);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        point.set_withIdx(i, t[i]);
    }
}
#endif