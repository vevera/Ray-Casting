#ifndef REFLEXIVITY_HPP
#define REFLEXIVITY_HPP

#include <Eigen/Core>

using Eigen::Vector3d;

struct Reflexivity {
    Reflexivity(const Vector3d& kd, const Vector3d& ke, const Vector3d& ka,
                double shininess)
        : kd{kd}, ke{ke}, ka{ka}, shininess{shininess} {}
    Reflexivity(const Vector3d& k) : kd{k}, ke{k}, ka{k}, shininess{1} {}
    Reflexivity(const Vector3d& k, const double shininess)
        : kd{k}, ke{k}, ka{k}, shininess{shininess} {}


    Vector3d kd;
    Vector3d ke;
    Vector3d ka;
    double shininess;
};

#endif   // ! REFLEXIVITY_HPP


