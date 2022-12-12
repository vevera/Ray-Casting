#include "cone.h"

#include <functional>
#include <iostream>
Cone::Cone(Reflexivity reflexivity, Vector3d base_center, Vector3d vertex,
           double radius)
    : Shape(reflexivity, base_center),
      base_center_(base_center),
      vertex_(vertex),
      radius_(radius) {
    Vector3d vertex_center = (vertex - base_center_);
    height_ = vertex_center.length();
    cone_direction_ = vertex_center.normalize();
}

Cone::Cone(Reflexivity reflexivity, Vector3d base_center, double height,
           Vector3d cone_direction, double radius)
    : Shape(reflexivity, base_center),
      base_center_(base_center),
      height_(height),
      cone_direction_(cone_direction),
      radius_(radius) {
    vertex_ = base_center_ + (cone_direction_ * height_);
}

double Cone::intersect(Vector3d &p_0, Vector3d &dr) {
    last_dr = &dr;

    double t1, t2 = 0;

    double height_2 = pow(height_, 2);

    Vector3d w = (vertex_ - p_0);

    double cos_2 = height_2 / (pow(radius_, 2) + height_2);

    double dr_dot_dc = dr.dot(cone_direction_);

    double w_dot_dc = w.dot(cone_direction_);

    double a = pow(dr_dot_dc, 2) - dr.dot(dr) * cos_2;

    double b = 2 * (w.dot(dr) * cos_2 - w_dot_dc * dr_dot_dc);

    double c = pow(w_dot_dc, 2) - w.dot(w) * cos_2;

    double delta = pow(b, 2) - 4 * a * c;

    if (delta < 0.0) {
        return INFINITY;
    }
    if (a == 0.0) {
        t1 = t2 = -c / b;
    } else {
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);
    }

    double min = t2 <= t1 ? t2 : t1;
    double max = t2 <= t1 ? t1 : t2;

    bool min_valid = in_cone_surface(p_0, dr, min);
    bool max_valid = in_cone_surface(p_0, dr, max);
    
    double t_base =
        ((base_center_ - p_0).dot(cone_direction_)) / (dr.dot(cone_direction_));

    bool t_base_valid = in_base_surface(p_0, dr, t_base, base_center_);

    double min_cone = min_valid ? min : max_valid ? max : INFINITY;

    if ((min_valid || max_valid || t_base_valid)) {
        if (t_base_valid) {
            if ((t_base <= min_cone) && t_base > 0.0001) {
                type = INTERSECTION_CONE_TYPE::BASE_CONE_SURFACE;
                return t_base;
            }
        }
        if ((min_valid || max_valid) && min_cone > 0.0001) {
            type = INTERSECTION_CONE_TYPE::CONE_SURFACE;
            return min_cone;
        }
    } else {
        if (t_base_valid) {
            type = INTERSECTION_CONE_TYPE::BASE_CONE_SURFACE;
            return t_base;
        }
    }

    return INFINITY;
};

Vector3d Cone::normal(Vector3d &p_i) {
    if (type == INTERSECTION_CONE_TYPE::BASE_CONE_SURFACE)
        return cone_direction_ * -1.0;

    Vector3d v_pi = (vertex_ - p_i);
    Vector3d N_ = v_pi.cross_product(cone_direction_);
    Vector3d N = N_.cross_product(v_pi);
    Vector3d n = N.normalize();

    return n;
};

bool Cone::in_cone_surface(Vector3d &p0, Vector3d &dr, double &t) {
    Vector3d p_i = (p0 + dr * t);
    double h = (vertex_ - p_i).dot(cone_direction_);
    return h >= 0.0000 && h <= height_;
};

bool Cone::in_base_surface(Vector3d &p0, Vector3d &dr, double &t,
                           Vector3d &base_center_) {
    if (t == INFINITY)
        return false;

    Vector3d p_i = p0 + (dr * t);
    Vector3d cb_pi = p_i - base_center_;

    double h = cb_pi.length();
    return h <= radius_;
};

void Cone::operator*(AccMatrix m) {
    std::for_each(m.acc->begin(), m.acc->end(), [&](gMatrix &m) { *this *m; });
};
void Cone::operator*(gMatrix m) {
    switch (m.t_type) {
        case TransformType::SHEARING:
            break;
        case TransformType::SCALE:
            radius_ = radius_ * m.transform_matrix.at(0).get(0)/2;
            height_ = height_ * m.transform_matrix.at(1).get(1);
            vertex_ = base_center_ + (cone_direction_ * height_);
            break;
        case TransformType::TRANSLATE:
            shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
            base_center_ =
                base_center_.mult_vector_matriz4d(m.transform_matrix);
            vertex_ = base_center_ + (cone_direction_ * height_);
            break;
        default:
            shape_center = shape_center.mult_vector_matriz4d(m.transform_matrix);
            vertex_ = vertex_.mult_vector_matriz4d(m.transform_matrix);
            base_center_ =
                base_center_.mult_vector_matriz4d(m.transform_matrix);

            cone_direction_.set(3, 0);
            cone_direction_ =
                cone_direction_.mult_vector_matriz4d(m.n_fix).normalize();
            break;
    }
};

Shape * Cone::Copy(){
    return new Cone(*this);
};