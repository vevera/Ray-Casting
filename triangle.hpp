#ifndef CUBE_HPP
#define CUBE_HPP

#include <Eigen/Core>
#include <Eigen/Dense>

#include "object.hpp"
#include "reflexivity.hpp"
#include "types.hpp"

using Eigen::Vector3d;

class Triangle {
   public:
    Triangle(const Vector3d& v0, const Vector3d& v1, const Vector3d& v2,
             const Reflexivity& rfx, const LightInteraction& li_type)
        : m_V0{v0}, m_V1{v1}, m_V2{v2}, m_Reflexivity{rfx}, m_LiType{li_type} {
        m_Normal = (m_V1 - m_V0).cross(m_V2 - m_V0);
        m_Normal.normalize();
    }
    ~Triangle() {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        if (dr.dot(m_Normal) < 0)
            return INFINITY;

        Vector3d w = p0 - m_V0;

        double den = dr.dot(m_Normal);

        if (den == 0)
            return INFINITY;

        double t = (w * -1).dot(m_Normal) / den;
        Vector3d p = p0 + t * dr;

        if ((m_V1 - m_V0).cross(p - m_V0).dot(m_Normal) > 0 &&
            (m_V2 - m_V1).cross(p - m_V1).dot(m_Normal) > 0 &&
            (m_V0 - m_V2).cross(p - m_V2).dot(m_Normal) > 0) {
            return t;
        }

        return INFINITY;
    }

    inline Vector3d normal(const Vector3d& pi) const { return m_Normal; }

    inline ObjectTypes type() const { return ObjectTypes::PLANE; }

    inline LightInteraction light_interation() const { return m_LiType; };

    inline const Reflexivity& color() const { return m_Reflexivity; }

    inline bool move_towards(const Vector3d& target, double step,
                             double threshold) {
        return true;
    }

   private:
    Vector3d m_V0;
    Vector3d m_V1;
    Vector3d m_V2;
    Vector3d m_Normal;
    Reflexivity m_Reflexivity;
    LightInteraction m_LiType;
};

#endif