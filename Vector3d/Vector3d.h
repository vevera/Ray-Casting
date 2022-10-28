#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>
#include <vector>

using std::vector;

class Vector3d {
   public:
    Vector3d() = default;
    Vector3d(double x, double y, double z);
    Vector3d(double x, double y, double z, double w);
    double get(int el) const;
    void set(int el, double val);
    // Sum of vectors
    Vector3d operator+(Vector3d const &op);
    Vector3d *operator+(Vector3d const *op);
    // Subtraction of vectors
    Vector3d operator-(Vector3d const &op);
    Vector3d *operator-(Vector3d const *op);
    // Product of vectors
    Vector3d operator*(Vector3d const &op);
    Vector3d *operator*(Vector3d const *op);
    Vector3d operator*(double const &scalar);
    // Division of vectors
    Vector3d operator/(Vector3d const &op);
    Vector3d *operator/(Vector3d const *op);
    Vector3d operator/(double const &div);

    Vector3d mult_vector_matriz(std::vector<Vector3d> &matriz);
    Vector3d mult_vector_matriz4d(std::vector<Vector3d> &matriz);
    Vector3d normalize();
    Vector3d cross_product(Vector3d const &op);

    double length();
    double dot(Vector3d const &vector);
    double dot4d(Vector3d const &vector);

    std::vector<Vector3d> dotTr(Vector3d &vector);
    static std::vector<Vector3d> subtraction(std::vector<Vector3d> &m1,
                                             std::vector<Vector3d> &m2);
    std::string toStr();

    double x_;
    double y_;
    double z_;
    double w_;
};

#endif