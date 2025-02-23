#ifndef PLANE_HPP
#define PLANE_HPP

#include <Eigen/Core>

#include "types.hpp"

using Eigen::Vector3d;

class Plane {
   public:
    Plane(const Vector3d& pi, const Vector3d& normal, const Reflexivity& rfx)
        : m_Pi{pi}, m_Normal{normal}, m_Reflexivity{rfx} {}
    ~Plane() {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        Vector3d w = p0 - m_Pi;

        double den = dr.dot(m_Normal);

        if (den == 0)
            return INFINITY;

        return (w * -1).dot(m_Normal) / den;
    }

    inline Vector3d normal(const Vector3d& pi) const { return m_Normal; }

    inline Vector3d light_intensity() const { return Vector3d(.4, .2, .3); };

    inline ObjectTypes type() const { return ObjectTypes::PLANE; }

    inline const Reflexivity& color() const { return m_Reflexivity; }

   private:
    Vector3d m_Pi;
    Vector3d m_Normal;
    Reflexivity m_Reflexivity;
};

#endif