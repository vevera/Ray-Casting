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
        //Vector3d r = l.dot(normal) * normal * 2 - l;

        // Vector3d i_d = ((intensity * kd) * std::max(l.dot(n), 0.0));

        Vector3d s =
            intensity.cwiseProduct(rfx.kd) * std::max(l.dot(normal), 0.0) +
            intensity.cwiseProduct(rfx.ke) *
                std::pow(std::max(v.dot(l.dot(normal) * normal * 2 - l), 0.0),
                                  rfx.shininess);

        //+intensity.cwiseProduct(rfx.ke) *
        //    std::max(
        //        std::pow(v.dot(l.dot(normal) * normal * 2 - l), rfx.shininess),
        //        0.0)

        //double max = s.maxCoeff();

        return s;
    }
};

struct AmbientLight {
    Vector3d intensity;

    AmbientLight(const Vector3d& intensity) : intensity{intensity} {};

    inline Direction get_direction_from_p(const Vector3d& pi) const {
        return {Vector3d(0, 0, 0), -1.0};
    };

    inline Vector3d get_light_contribution(const Vector3d& l, const Vector3d& v,
                                           const Vector3d& normal,
                                           const Reflexivity& rfx) const {
        return rfx.ka.cwiseProduct(intensity);
    }
};

#endif   // ! LIGHT_HPP
