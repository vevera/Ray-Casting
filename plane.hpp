#ifndef PLANE_HPP
#define PLANE_HPP

#include <Eigen/Core>

#include "object.hpp"
#include "reflexivity.hpp"
#include "types.hpp"

using Eigen::Vector3d;

class Plane {
   public:
    Plane(const Vector3d& pi, const Vector3d& normal, const Reflexivity& rfx,
          const LightInteraction& li_type)
        : m_Normal{normal}, m_Reflexivity{rfx}, m_LiType{li_type} {
        m_Pi << pi, 1;
    }
    ~Plane() {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        Vector3d w = p0 - m_Pi.head<3>();

        double den = dr.dot(m_Normal);

        if (den == 0)
            return INFINITY;

        return (w * -1).dot(m_Normal) / den;
    }

    inline Vector3d normal(const Vector3d& pi) const { return m_Normal; }

    inline ObjectTypes type() const { return ObjectTypes::PLANE; }

    inline LightInteraction light_interation() const { return m_LiType; };

    inline const Reflexivity& color() const { return m_Reflexivity; }

    inline bool move_towards(const Vector3d& target, double step,
                             double threshold) {
        return object::move_towards(m_Pi, target, step, threshold);
    }

   private:
    Vector4d m_Pi;
    Vector3d m_Normal;
    Reflexivity m_Reflexivity;
    LightInteraction m_LiType;
};

#endif