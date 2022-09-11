#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <vector>
#include <string>

using std::vector;

class Vector3d
{

public:
    Vector3d() = default;
    Vector3d(double x, double y, double z);
    Vector3d operator+(Vector3d const &op);
    Vector3d operator-(Vector3d const &op);
    Vector3d operator*(Vector3d const &op);
    Vector3d operator*(double const &scalar);
    Vector3d operator/(Vector3d const &op);
    Vector3d operator/(double const &div);
    Vector3d normalize();
    double length();
    double dot(Vector3d const &vector);
    std::string toStr();

private:
    double x_;
    double y_;
    double z_;
};

#endif