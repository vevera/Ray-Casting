#include "cylinder.h"

#include <math.h>

#include <iostream>
Cylinder::Cylinder(Reflexivity reflexivity, Vector3d base_center,
                   Vector3d top_center, long double radius)
    : Shape(reflexivity, (base_center+top_center)/2.0),
      base_center_(base_center),
      top_center_(top_center),
      radius_(radius),
      last_dr(nullptr) {
    Vector3d Cb_Ct = (top_center - base_center);
    height = Cb_Ct.length();
    cylinder_direction = Cb_Ct.normalize();
    cylinder_direction.set(3, 0);

    vector<Vector3d> identity = {Vector3d(1, 0, 0), Vector3d(0, 1, 0),
                                 Vector3d(0, 0, 1)};

    vector<Vector3d> dc_dot_dct = cylinder_direction.dotTr(cylinder_direction);

    M = Vector3d::subtraction(identity, dc_dot_dct);
};

Cylinder::Cylinder(Reflexivity reflexivity, Vector3d base_center, long double height,
                   Vector3d cylinder_direction, long double radius)
    : Shape(reflexivity, ((base_center*2) + cylinder_direction * height)/2.0),
      base_center_(base_center),
      height(height),
      radius_(radius),
      cylinder_direction(cylinder_direction),
      last_dr(nullptr)

{
    cylinder_direction.set(3, 0);
    top_center_ = base_center_ + cylinder_direction * height;

    //shape_center = (base_center_ +top_center_)/2;

    vector<Vector3d> identity = {Vector3d(1, 0, 0), Vector3d(0, 1, 0),
                                 Vector3d(0, 0, 1)};

    vector<Vector3d> dc_dot_dct = cylinder_direction.dotTr(cylinder_direction);

    M = Vector3d::subtraction(identity, dc_dot_dct);
}

long double Cylinder::intersect(Vector3d &p_0, Vector3d &dr) {
    last_dr = &dr;

    long double t1, t2;

    Vector3d w = p_0 - base_center_;

    long double a = (dr.mult_vector_matriz(M)).dot(dr);

    long double b = (w.mult_vector_matriz(M)).dot(dr) * 2;

    long double c = (w.mult_vector_matriz(M)).dot(w) - pow(radius_, 2);

    long double delta = pow(b, 2) - 4 * a * c;

    if (delta < 0) {
        return INFINITY;
    }

    t1 = (-b + sqrt(delta)) / (2 * a);
    t2 = (-b - sqrt(delta)) / (2 * a);

    long double min = t2 < t1 ? t2 : t1;
    long double max = t2 < t1 ? t1 : t2;

    bool min_valid = in_cylinder_surface(p_0, dr, min);
    bool max_valid = in_cylinder_surface(p_0, dr, max);

    long double t_base = -((p_0 - base_center_).dot(cylinder_direction)) /
                    (dr.dot(cylinder_direction));

    long double t_top = -((p_0 - top_center_).dot(cylinder_direction)) /
                   (dr.dot(cylinder_direction));

    bool t_base_valid = in_lid_surface(p_0, dr, t_base, base_center_);
    bool t_top_valid = in_lid_surface(p_0, dr, t_top, top_center_);

    t_top = !t_top_valid ? INFINITY : t_top;
    t_base = !t_base_valid ? INFINITY : t_base;

    long double min_cylinder = min_valid ? min : max_valid ? max : INFINITY;

    long double min_lid = t_base_valid && t_base < t_top  ? t_base
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

Vector3d Cylinder::normal(Vector3d &p_i) {
    if (type == INTERSECTION_TYPE::BASE_SURFACE)
        return cylinder_direction * -1;

    if (type == INTERSECTION_TYPE::TOP_SURFACE) {
        return cylinder_direction;
    }

    Vector3d d = p_i - base_center_;
    Vector3d N = d.mult_vector_matriz(M);
    Vector3d normal = N.normalize();

    return normal;
};

bool Cylinder::in_cylinder_surface(Vector3d &p0, Vector3d &dr, long double &t) {
    Vector3d p_i = p0 + (dr * t);
    Vector3d cb_pi = p_i - base_center_;

    long double h = cb_pi.dot(cylinder_direction);
    return h >= 0.0 && h <= height;
}

bool Cylinder::in_lid_surface(Vector3d &p0, Vector3d &dr, long double &t,
                              Vector3d &lid_center) {
    if (t == INFINITY)
        return false;

    Vector3d p_i = p0 + (dr * t);
    Vector3d cb_pi = p_i - lid_center;

    long double h = cb_pi.length();
    return h <= radius_;
}

void Cylinder::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Cylinder::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::SCALE:
            radius_ = radius_ * m.transform_matrix.at(0).get(0);
            height = height * m.transform_matrix.at(1).get(1);
            top_center_ = base_center_ + (cylinder_direction * height);
            break;
        case TransformType::SHEARING:
            break;
        case TransformType::TRANSLATE:
            shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
            base_center_ = shape_center + ((cylinder_direction * -1) * height/2.0);
            //base_center_ =
            //    base_center_.mult_vector_matriz4d(m.transform_matrix);
            top_center_ = base_center_ + (cylinder_direction * height);
            break;
        default:
            shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
            base_center_ =
                base_center_.mult_vector_matriz4d(m.transform_matrix);
            top_center_ = top_center_.mult_vector_matriz4d(m.transform_matrix);
            cylinder_direction.set(3, 0);
            cylinder_direction =
                cylinder_direction.mult_vector_matriz4d(m.n_fix).normalize();
            rebuild_M();
            break;
    }
};

void Cylinder::rebuild_M() {
    vector<Vector3d> identity = {Vector3d(1, 0, 0), Vector3d(0, 1, 0),
                                 Vector3d(0, 0, 1)};

    vector<Vector3d> dc_dot_dct = cylinder_direction.dotTr(cylinder_direction);

    M = Vector3d::subtraction(identity, dc_dot_dct);
};

Shape * Cylinder::Copy(){
    return new Cylinder(*this);
};
