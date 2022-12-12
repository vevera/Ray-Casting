#include "Vector3d.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../matrix/matrix.h"
#include <Eigen/Dense>
using std::vector;

Vector3d::Vector3d(double x, double y, double z) : x_(x), y_(y), z_(z), w_(1){};

Vector3d::Vector3d(double x, double y, double z, double w)
    : x_(x), y_(y), z_(z), w_(w){};

double Vector3d::get(int el) const {
    switch (el) {
        case 0:
            return x_;
            break;
        case 1:
            return y_;
            break;
        case 2:
            return z_;
            break;
        case 3:
            return w_;
            break;
        default:
            return 0;
            break;
    }
}

void Vector3d::set(int el, double val) {
    switch (el) {
        case 0:
            x_ = val;
            break;
        case 1:
            y_ = val;
            break;
        case 2:
            z_ = val;
            break;
        case 3:
            w_ = val;
            break;
        default:
            break;
    }
}

Vector3d Vector3d::operator+(Vector3d const &op) {
    return Vector3d(x_ + op.x_, y_ + op.y_, z_ + op.z_);
};

Vector3d *Vector3d::operator+(Vector3d const *op) {
    return new Vector3d(x_ + op->x_, y_ + op->y_, z_ + op->z_);
};

Vector3d Vector3d::operator-(Vector3d const &op) {
    return Vector3d(x_ - op.x_, y_ - op.y_, z_ - op.z_);
};

Vector3d *Vector3d::operator-(Vector3d const *op) {
    return new Vector3d(x_ - op->x_, y_ - op->y_, z_ - op->z_);
};

Vector3d Vector3d::operator*(Vector3d const &op) {
    return Vector3d(x_ * op.x_, y_ * op.y_, z_ * op.z_);
};

Vector3d *Vector3d::operator*(Vector3d const *op) {
    return new Vector3d(x_ * op->x_, y_ * op->y_, z_ * op->z_);
};

Vector3d Vector3d::operator*(double const &scalar) {
    return Vector3d(x_ * scalar, y_ * scalar, z_ * scalar);
};

void Vector3d::operator*(vector<Vector3d> &m) {
    Vector3d result = this->mult_vector_matriz4d(m);

    *this = result;
}

Vector3d Vector3d::operator/(Vector3d const &op) {
    return Vector3d(x_ / op.x_, y_ / op.y_, z_ / op.z_);
};

Vector3d *Vector3d::operator/(Vector3d const *op) {
    return new Vector3d(x_ / op->x_, y_ / op->y_, z_ / op->z_);
};

Vector3d Vector3d::operator/(double const &div) {
    return Vector3d(x_ / div, y_ / div, z_ / div);
};

double Vector3d::dot(Vector3d const &vector) {
    return (x_ * vector.x_) + (y_ * vector.y_) + (z_ * vector.z_);
};

double Vector3d::dot4d(Vector3d const &vector) {

    // Eigen::Vector4d v(x_,y_,z_,w_);
    // Eigen::Vector4d v1(vector.x_,vector.y_,vector.z_,vector.w_);

    // //Eigen::Vector4d v2 = v.dot(v1);
    
    //return v.dot(v1);
    return (x_ * vector.x_) + (y_ * vector.y_) + (z_ * vector.z_) +
           (w_ * vector.w_);
};

Vector3d Vector3d::cross_product(Vector3d const &op) {
    // Eigen::Vector4d v(x_,y_,z_,w_);
    // Eigen::Vector4d v1(op.x_,op.y_,op.z_,op.w_);

    // Eigen::Vector3d v2 = v.head<3>().cross(v1.head<3>());

    // return Vector3d(v2(0), v2(1),
    //                 v2(2));

    return Vector3d(y_ * op.z_ - z_ * op.y_, z_ * op.x_ - x_ * op.z_,
                    x_ * op.y_ - y_ * op.x_);
}

std::vector<Vector3d> Vector3d::dotTr(Vector3d &vector) {
    std::vector<Vector3d> mt;

    mt.push_back(vector * x_);
    mt.push_back(vector * y_);
    mt.push_back(vector * z_);

    return mt;
}

std::vector<Vector3d> Vector3d::subtraction(std::vector<Vector3d> &m1,
                                            std::vector<Vector3d> &m2) {
    std::vector<Vector3d> mt;

    mt.push_back(m1.at(0) - m2.at(0));
    mt.push_back(m1.at(1) - m2.at(1));
    mt.push_back(m1.at(2) - m2.at(2));

    return mt;
};

Vector3d Vector3d::mult_vector_matriz(std::vector<Vector3d> &matriz) {
    double x, y, z;

    x = this->dot(matriz.at(0));
    y = this->dot(matriz.at(1));
    z = this->dot(matriz.at(2));

    return Vector3d(x, y, z);
}

Vector3d Vector3d::mult_vector_matriz4d(std::vector<Vector3d> &matriz) {
    double x, y, z;

    x = this->dot4d(matriz.at(0));
    y = this->dot4d(matriz.at(1));
    z = this->dot4d(matriz.at(2));

    return Vector3d(x, y, z, 1.0);
}

double Vector3d::length() {
    double sum = dot(*this);
    return std::pow(sum, 1.0/2.0);
};

double Vector3d::length4d() {
    double sum = dot4d(*this);
    return std::sqrt(sum);
};

Vector3d Vector3d::normalize() {
    //*this = *this / this->length();

    // Eigen::Vector3d v1(x_,y_,z_);
    // v1 = v1.normalized();

    // return Vector3d(v1(0), v1(1),
    //                 v1(2));

    return *this / this->length();
};

Vector3d Vector3d::normalize4d() {
    //*this = *this / this->length();
    return *this / this->length4d();
};

std::string Vector3d::toStr() {
    std::string out = "";

    out += std::to_string(x_) + "/";
    out += std::to_string(y_) + "/";
    out += std::to_string(z_) + "/";
    out += std::to_string(w_) + "/";
    return out;
}
