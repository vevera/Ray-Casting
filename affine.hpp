#ifndef AFFINE_HPP
#define AFFINE_HPP

#include <Eigen/Core>
#include <Eigen/Dense>

using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

inline Matrix4d TranslationMatrix(const Vector3d& tvector) {
    Matrix4d m = Matrix4d::Identity();
    m.col(3) << tvector, 1.0;

    return m;
}

#endif   // !
