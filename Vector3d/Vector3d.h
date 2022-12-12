#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>
#include <vector>

class gMatrix;
using std::vector;

class Vector3d {
   public:
    Vector3d() = default;
    Vector3d(long double x, long double y, long double z);
    Vector3d(long double x, long double y, long double z, long double w);
    long double get(int el) const;
    void set(int el, long double val);
    // Sum of vectors
    Vector3d operator+(Vector3d const &op);
    Vector3d *operator+(Vector3d const *op);
    // Subtraction of vectors
    Vector3d operator-(Vector3d const &op);
    Vector3d *operator-(Vector3d const *op);
    // Product of vectors
    Vector3d operator*(Vector3d const &op);
    Vector3d *operator*(Vector3d const *op);
    Vector3d operator*(long double const &scalar);
    void operator*(std::vector<Vector3d> &m);
    // Division of vectors
    Vector3d operator/(Vector3d const &op);
    Vector3d *operator/(Vector3d const *op);
    Vector3d operator/(long double const &div);

    // Vector3d &operator=(Vector3d &&op) {
    //     *this = std::move(op);
    //     return *this;
    // };

    Vector3d mult_vector_matriz(std::vector<Vector3d> &matriz);
    Vector3d mult_vector_matriz4d(std::vector<Vector3d> &matriz);
    Vector3d normalize();
    Vector3d normalize4d();
    Vector3d cross_product(Vector3d const &op);

    long double length();
    long double length4d();
    long double dot(Vector3d const &vector);
    long double dot4d(Vector3d const &vector);

    std::vector<Vector3d> dotTr(Vector3d &vector);
    static std::vector<Vector3d> subtraction(std::vector<Vector3d> &m1,
                                             std::vector<Vector3d> &m2);
    std::string toStr();

    long double x_;
    long double y_;
    long double z_;
    long double w_;
};

#endif