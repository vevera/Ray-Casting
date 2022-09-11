#include "Vector3d.h"
#include <cmath>

using std::vector;

Vector3d::Vector3d(double x, double y, double z) : x_(x), y_(y), z_(z){};

Vector3d Vector3d::operator+(Vector3d const &op)
{

    return Vector3d(x_ + op.x_, y_ + op.y_, z_ + op.z_);
};

Vector3d Vector3d::operator-(Vector3d const &op)
{

    return Vector3d(x_ - op.x_, y_ - op.y_, z_ - op.z_);
};

Vector3d Vector3d::operator*(Vector3d const &op)
{

    return Vector3d(x_ * op.x_, y_ * op.y_, z_ * op.z_);
};

Vector3d Vector3d::operator*(double const &scalar)
{

    return Vector3d(x_ * scalar, y_ * scalar, z_ * scalar);
};

Vector3d Vector3d::operator/(Vector3d const &op)
{

    return Vector3d(x_ / op.x_, y_ / op.y_, z_ / op.z_);
};

Vector3d Vector3d::operator/(double const &div)
{
    return Vector3d(x_ / div, y_ / div, z_ / div);
};

double Vector3d::dot(Vector3d const &vector)
{

    return (x_ * vector.x_) + (y_ * vector.y_) + (z_ * vector.z_);
};

double Vector3d::length()
{
    double sum = dot(*this);
    return std::sqrt(sum);
};

Vector3d Vector3d::normalize()
{
    return *this / this->length();
};

std::string Vector3d::toStr()
{

    std::string out = "";

    out += std::to_string(x_) + "/";
    out += std::to_string(y_) + "/";
    out += std::to_string(z_) + "/";
    return out;
}