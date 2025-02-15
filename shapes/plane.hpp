#ifndef PLANE_HPP
#define PLANE_HPP

#include <Eigen/Core>

#include "types.hpp"

using Eigen::Vector3d;

class Plane {
   public:
    Plane(const Vector3d& center, double radius)
        : center{center}, radius{radius}, mcolor{0.2, 0.3, 0.5} {}
    ~Plane() {}

   inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        double t1, t2, a, b, c, delta;

        Vector3d w = p0 - center;
        a = dr.dot(dr);
        b = 2 * w.dot(dr);
        c = w.dot(w) - (radius * radius);

        delta = (b * b) - 4 * a * c;

        if (delta < 0)
            return INFINITY;

        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        return std::min(t1, t2);
    }

    inline Vector3d normal(const Vector3d& pi) const {
        return (pi - center) / radius;
    }

    inline Vector3d light_intensity() const { return Vector3d(.4, .2, .3); };

    inline ObjectTypes type() const { return ObjectTypes::PLANE; }

    inline const Vector3d& color() const { return mcolor; }

   private:
    Vector3d center;
    Vector3d mcolor;
    double radius;
};

#endif