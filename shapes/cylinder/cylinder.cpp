#include "cylinder.h"

#include <math.h>

#include <iostream>
Cylinder::Cylinder(Reflexivity reflexivity, Vector4d base_center,
                   Vector4d top_center, double radius, std::string texture_path)
    : Shape(reflexivity, texture_path),
      base_center_(base_center),
      top_center_(top_center),
      radius_(radius),
      last_dr(nullptr) {
    Vector4d Cb_Ct = (top_center - base_center);
    height = Cb_Ct.norm();
    cylinder_direction = Cb_Ct.normalized();
    // cylinder_direction.set(3, 0);

    // Eigen::Matrix3d identity;
    // identity << 1, 0, 0, 0, 1, 0, 0, 0, 1;
    // = {Vector3d(1, 0, 0), Vector3d(0, 1, 0),
    //                              Vector3d(0, 0, 1)};

    rebuild_M();
};

Cylinder::Cylinder(Reflexivity reflexivity, Vector4d base_center, double height,
                   Vector4d cylinder_direction, double radius,
                   std::string texture_path)
    : Shape(reflexivity, texture_path),
      base_center_(base_center),
      height(height),
      radius_(radius),
      cylinder_direction(cylinder_direction),
      last_dr(nullptr)

{
    // cylinder_direction.set(3, 0);
    top_center_ = base_center_ + cylinder_direction * height;

    rebuild_M();
}

double Cylinder::intersect(Vector4d &p_0, Vector4d &dr) {
    last_dr = &dr;

    double t1, t2;

    Vector4d w = p_0 - base_center_;

    double a = (M * dr.head<3>()).dot(dr.head<3>());

    double b = (M * w.head<3>()).dot(dr.head<3>()) * 2;

    double c = (M * w.head<3>()).dot(w.head<3>()) - pow(radius_, 2);

    double delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);

    double min = t2 < t1 ? t2 : t1;
    double max = t2 < t1 ? t1 : t2;

    bool min_valid = in_cylinder_surface(p_0, dr, min);
    bool max_valid = in_cylinder_surface(p_0, dr, max);

    double t_base = -((p_0 - base_center_).dot(cylinder_direction)) /
                    (dr.dot(cylinder_direction));

    double t_top = -((p_0 - top_center_).dot(cylinder_direction)) /
                   (dr.dot(cylinder_direction));

    bool t_base_valid = in_lid_surface(p_0, dr, t_base, base_center_);
    bool t_top_valid = in_lid_surface(p_0, dr, t_top, top_center_);

    t_top = !t_top_valid ? INFINITY : t_top;
    t_base = !t_base_valid ? INFINITY : t_base;

    double min_cylinder = min_valid ? min : max_valid ? max : INFINITY;

    double min_lid = t_base_valid && t_base < t_top  ? t_base
                     : t_top_valid && t_top < t_base ? t_top
                                                     : INFINITY;

    if (min_cylinder < min_lid) {
        type = INTERSECTION_TYPE::CYLINDER_SURFACE;
        return min_cylinder;
    }

    if (t_top < t_base && t_top_valid) {
        type = INTERSECTION_TYPE::TOP_SURFACE;
        return t_top;
    }

    if (t_top >= t_base && t_base_valid) {
        type = INTERSECTION_TYPE::BASE_SURFACE;
        return t_base;
    }
    return INFINITY;
};

Vector4d Cylinder::normal(Vector4d &p_i) {
    if (type == INTERSECTION_TYPE::BASE_SURFACE)
        return cylinder_direction * -1;

    if (type == INTERSECTION_TYPE::TOP_SURFACE) {
        return cylinder_direction;
    }

    Vector4d d = p_i - base_center_;
    Vector4d N(0, 0, 0, 0);
    N.head<3>() = M * d.head<3>();
    Vector4d normal = N.normalized();

    return normal;
};

bool Cylinder::in_cylinder_surface(Vector4d &p0, Vector4d &dr, double &t) {
    Vector4d p_i = p0 + (dr * t);
    Vector4d cb_pi = p_i - base_center_;

    double h = cb_pi.dot(cylinder_direction);
    return h >= 0.0 && h <= height;
}

bool Cylinder::in_lid_surface(Vector4d &p0, Vector4d &dr, double &t,
                              Vector4d &lid_center) {
    if (t == INFINITY)
        return false;

    Vector4d p_i = p0 + (dr * t);
    Vector4d cb_pi = p_i - lid_center;

    double h = cb_pi.norm();
    return h <= radius_;
}

void Cylinder::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Cylinder::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::SCALE:
            radius_ = radius_ * m.transform_matrix(0, 0);
            height = height * m.transform_matrix(1, 1);
            top_center_ = base_center_ + (cylinder_direction * height);
            break;
        case TransformType::SHEARING:
            break;
        case TransformType::TRANSLATE:
            base_center_ = m.transform_matrix * base_center_;
            top_center_ = base_center_ + (cylinder_direction * height);
            break;
        default:
            base_center_ = m.transform_matrix * base_center_;
            top_center_ = m.transform_matrix * top_center_;
            // cylinder_direction.set(3, 0);
            cylinder_direction = (m.n_fix * cylinder_direction).normalized();
            rebuild_M();
            break;
    }
};

void Cylinder::rebuild_M() {
    Eigen::Matrix3d dc_dot_dct =
        cylinder_direction.head<3>() * cylinder_direction.head<3>().transpose();

    M = Eigen::Matrix<double, 3, 3>::Identity() - dc_dot_dct;
};
