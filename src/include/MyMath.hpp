#ifndef MATH_H
#define MATH_H
#include <iostream>
using namespace std;
inline float angleToRadian(float angle)
{
    return angle * M_PI / 180.0f;
}
class Point2D
{
private:
    int x;
    int y;

public:
    Point2D() {};
    Point2D(int x, int y);
    int get_x() { return this->x; };
    int get_y() { return this->y; };
    void set_x(int x) { this->x = x; };
    void set_y(int y) { this->y = y; };
    void printPoint2D() { cout << "Point2D:" << this->x << "," << this->y << endl; }
};
inline Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
}
class Point3DN
{
private:
    float p[4];

public:
    Point3DN(float x, float y, float z, float w);
    void printxyzw();
    float get_withIdx(int idx);
    void set_withIdx(int idx, float val);
    void divByW();
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
void Point3DN::divByW()
{
    this->p[0] /= this->p[3];
    this->p[1] /= this->p[3];
    this->p[2] /= this->p[3];
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
    void InitMat4(const float (&array)[4][4]);
    void Identity();
    void PrintMat();
    void setVal(int i, int j, float val);
    void dotPoint3DN(Point3DN &point);
    static Mat4 dot(const Mat4 &a, const Mat4 &b);
    static Mat4 Translation(float Tx, float Ty, float Tz);
    static Mat4 Scaled(float Sx, float Sy, float Sz);
    static Mat4 RotationX(float angle);
    static Mat4 RotationY(float angle);
    static Mat4 RotationZ(float angle);
};
void Mat4::InitMat4(const float (&array)[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            this->matrix[i][j] = array[i][j];
        }
    }
}
inline void Mat4::Identity()
{
    for (int i = 0; i < 4; i++)
        this->matrix[i][i] = 1;
}
Mat4 Mat4::Translation(float Tx, float Ty, float Tz)
{
    Mat4 result;
    result.Identity();
    result.matrix[0][3] = Tx;
    result.matrix[1][3] = Ty;
    result.matrix[2][3] = Tz;
    return result;
}
Mat4 Mat4::Scaled(float Sx, float Sy, float Sz)
{
    Mat4 result;
    result.matrix[0][0] *= Sx;
    result.matrix[1][1] *= Sy;
    result.matrix[2][2] *= Sz;
    return result;
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
inline void Mat4::setVal(int i, int j, float val)
{
    this->matrix[i][j] = val;
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
Mat4 Mat4::dot(const Mat4 &a, const Mat4 &b)
{
    Mat4 result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }
    return result;
}
Mat4 Mat4::RotationX(float angle)
{
    float a = angleToRadian(angle);
    float c = cos(a);
    float s = sin(a);
    Mat4 result;
    result.InitMat4({{1.0, 0.0, 0.0, 0.0},
                     {0.0, c, -s, 0.0},
                     {0.0, s, c, 0.0},
                     {0.0, 0.0, 0.0, 1.0}});
    return result;
}
Mat4 Mat4::RotationY(float angle)
{
    float a = angleToRadian(angle);
    float c = cos(a);
    float s = sin(a);
    Mat4 result;
    result.InitMat4({{c, 0.0, s, 0.0},
                     {0.0, 1.0, 0.0, 0.0},
                     {-s, 0.0, c, 0.0},
                     {0.0, 0.0, 0.0, 1.0}});
    return result;
}
Mat4 Mat4::RotationZ(float angle)
{
    float a = angleToRadian(angle);
    float c = cos(a);
    float s = sin(a);
    Mat4 result;
    result.InitMat4({{c, -s, 0.0, 0.0},
                     {s, c, 0.0, 0.0},
                     {0.0, 0.0, 1.0, 0.0},
                     {0.0, 0.0, 0.0, 1.0}});
    return result;
}
#endif