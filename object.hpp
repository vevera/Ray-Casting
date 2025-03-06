#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <Eigen/Core>

using Eigen::Vector3d;
using Eigen::Vector4d;

namespace object {
inline bool move_towards(Vector4d& pos, const Vector3d& target, double step,
                         double threshold) {
    Vector3d dr = target - pos.head<3>();
    double bnorm = dr.norm();

    if (bnorm < threshold)
        return false;

    dr.normalize();

    pos.head<3>() = pos.head<3>() + dr * step;
    double anorm = (target - pos.head<3>()).norm();

    if (anorm >= bnorm)
        return false;

    return true;
}
}   // namespace shape

#endif   // ! SHAPE_HPP
