#ifndef RAY_H
#define RAY_H

#include <Eigen\Core>
#include <vector>

#include "reflexivity.hpp"

namespace ray {

using Eigen::Vector3d;
using Eigen::Vector4d;

struct ShadingInfo {
    Reflexivity rfx;
    Vector3d normal;
    double t;
};

template <typename T>
inline ShadingInfo trace(const std::vector<T> &objects, const Vector3d &p0,
                         const Vector3d &dr, double t_max) {
    double t = 0;

    struct {
        double t = INFINITY;
        size_t i = 0;
    } closest;

    for (size_t i = 0; i < objects.size(); i++) {
        t = objects[i].intersect(p0, dr);

        if (t >= 0 && t < t_max && t < closest.t) {
            closest.t = t;
            closest.i = i;
        }
    }

    return {
        objects[closest.i].color(),
        objects[closest.i].normal(p0 + dr * closest.t),
        closest.t,
    };
}

}   // namespace ray

#endif