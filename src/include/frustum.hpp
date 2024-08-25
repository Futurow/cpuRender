#ifndef FRUSTUM_H
#define FRUSTUM_H
#include <cmath>
#include "scanline.hpp"

class Frustum
{
private:
    float nearPlane;
    float aspect;
    float fovy;
    Mat4 mat;

public:
    Frustum(float nearPlane, float aspect, float fovy);
    Mat4 &get_mat();
};

Frustum::Frustum(float nearPlane, float aspect, float fovy)
{
    this->nearPlane = nearPlane;
    this->aspect = aspect;
    this->fovy = fovy;
    float a = 1.0 / (nearPlane * tan(fovy));
    mat.InitMat4(
        {{a, 0.0f, 0.0f, 0.0f},
         {0.0f, aspect * a, 0.0f, 0.0f},
         {0.0f, 0.0f, 1.0f, 0.0f},
         {0.0f, 0.0f, -1.0f / nearPlane, 0.0f}});
}
inline Mat4 &Frustum::get_mat()
{
    return this->mat;
}
class Camera
{
private:
    Frustum frustum;

public:
    Camera(float nearPlane, float aspect, float fovy)
        : frustum(nearPlane, aspect, fovy) {}
    Frustum &get_frustum() { return this->frustum; };
};

#endif