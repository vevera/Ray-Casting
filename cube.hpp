#ifndef CUBE_HPP
#define CUBE_HPP

#include <Eigen/Core>

#include "reflexivity.hpp"
#include "types.hpp"

using Eigen::Vector3d;

struct Face {
    Vector3d n;
    Vector3d pi;
    double width;
    double height;
};

class Cube {
   public:
    Cube(const Face& f1, const Face& f2, const Face& f3, const Reflexivity& rfx,
         const LightInteraction& li_type)
        : m_F1{f1},
          m_F2{f2},
          m_F3{f3},
          m_Reflexivity{rfx}, m_LiType{li_type} {}
    ~Cube() {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        Vector3d w = p0 - m_Pi;

        double den = dr.dot(m_Normal);

        if (den == 0)
            return INFINITY;

        return (w * -1).dot(m_Normal) / den;
    }

    inline Vector3d normal(const Vector3d& pi) const { return m_Normal; }

    inline ObjectTypes type() const { return ObjectTypes::PLANE; }

    inline LightInteraction light_interation() const { return m_LiType; };

    inline const Reflexivity& color() const { return m_Reflexivity; }

   private:
    Face m_F1;
    Face m_F2;
    Face m_F3;

    Reflexivity m_Reflexivity;
    LightInteraction m_LiType;
};

#endif