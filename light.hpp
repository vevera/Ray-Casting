#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Eigen/Core>

#include "reflexivity.hpp"

struct Direction {
    Vector3d dr;
    double distance;
};

struct PointLight {
    Vector3d position;
    Vector3d intensity;

    PointLight(const Vector3d& position, const Vector3d& intensity)
        : position{position}, intensity{intensity} {}

    inline Direction get_direction_from_p(const Vector3d& pi) const {
        Vector3d dr = (position - pi);
        double distance = dr.norm();
        dr.normalize();
        return {dr, distance};
    };

    inline Vector3d get_light_contribution(const Vector3d& l, const Vector3d& v,
                                           const Vector3d& normal,
                                           const Reflexivity& rfx) const {
        return (intensity.cwiseProduct(rfx.k) * std::max<double>(l.dot(normal), 0.0)) +
               (intensity.cwiseProduct(rfx.k) *
                std::pow(std::max<double>(v.dot(l.dot(normal) * normal * 2.0 - l), 0.0),
                         rfx.shininess));
    }
};

#endif   // ! LIGHT_HPP
