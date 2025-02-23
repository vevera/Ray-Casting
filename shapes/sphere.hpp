#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <Eigen/Core>

#include "types.hpp"
#include "reflexivity.hpp"

using Eigen::Vector3d;

class Sphere {
   public:
    Sphere(const Vector3d& center, double radius, const Reflexivity& rfx)
        : center{center}, radius{radius}, m_Reflexivity{rfx} {}
    ~Sphere() {}

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

    inline ObjectTypes type() const { return ObjectTypes::SPHERE; }

    inline const Reflexivity& color() const { return m_Reflexivity; }

   private:
    Vector3d center;
    Reflexivity m_Reflexivity;
    double radius;
};

#endif