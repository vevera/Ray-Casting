#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <Eigen/Core>

#include "object.hpp"
#include "reflexivity.hpp"
#include "types.hpp"

using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

class Sphere {
   public:
    Sphere(const Vector3d& center, double radius, const Reflexivity& rfx,
           const LightInteraction& li_type)
        : m_Radius{radius}, m_Reflexivity{rfx}, m_LiType{li_type} {
        m_Center << center, 1;
    }
    ~Sphere() {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        double t1, t2, a, b, c, delta;

        Vector3d w = p0 - m_Center.head<3>();
        a = dr.dot(dr);
        b = 2 * w.dot(dr);
        c = w.dot(w) - (m_Radius * m_Radius);

        delta = (b * b) - 4 * a * c;

        if (delta < 0)
            return INFINITY;

        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);

        return std::min<double>(t1, t2);
    }

    inline Vector3d normal(const Vector3d& pi) const {
        return (pi - m_Center.head<3>()) / m_Radius;
    }

    inline ObjectTypes type() const { return ObjectTypes::SPHERE; }

    inline LightInteraction light_interation() const { return m_LiType; };

    inline const Reflexivity& color() const { return m_Reflexivity; }

    inline void set_color(const Reflexivity& relex) { m_Reflexivity = relex; }

    inline void affine_transform(const Matrix4d& transformation) {
        m_Center = transformation * m_Center;
    }

    inline bool move_towards(const Vector3d& target, double step,
                             double threshold) {
        return object::move_towards(m_Center, target, step, threshold);
    }

   private:
    Vector4d m_Center;
    Reflexivity m_Reflexivity;
    double m_Radius;
    LightInteraction m_LiType;
};

#endif