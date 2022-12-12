#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../Vector3d/Vector3d.h"
#include <Eigen/Dense>


AccMatrix gMatrix::operator*(gMatrix const &m) {
    shared_ptr<AccMatrix> acc = std::make_shared<AccMatrix>();
    acc->acc->push_back(*this);
    acc->acc->push_back(m);

    return *acc.get();
};

AccMatrix gMatrix::operator*(AccMatrix &acc) {
    shared_ptr<AccMatrix> acc_shared =
        std::make_shared<AccMatrix>(std::move(acc));

    acc_shared->acc->insert(acc_shared->acc->begin(), *this);
    return *acc_shared.get();
};

void AccMatrix::operator=(const gMatrix &m){
    acc->push_back(m);
}

AccMatrix AccMatrix::operator*(gMatrix m) {
    shared_ptr<AccMatrix> accm = std::make_shared<AccMatrix>();

    accm->acc = acc;
    accm->acc->push_back(m);

    return *accm.get();
};

AccMatrix AccMatrix::operator*(AccMatrix &acc_o) {
    shared_ptr<AccMatrix> acc_shared =
        std::make_shared<AccMatrix>(std::move(acc_o));
    acc_shared->acc->insert(acc_shared->acc->begin(), acc->begin(), acc->end());

    return *acc_shared.get();
};

gMatrix Matrix::scale(Vector3d scale_factor) {
    matrix_tr matrix_scale;
    matrix_scale = {Vector3d(scale_factor.x_, 0, 0, 0),
                    Vector3d(0, scale_factor.y_, 0, 0),
                    Vector3d(0, 0, scale_factor.z_, 0), Vector3d(0, 0, 0, 1)};

    matrix_tr fixing_matrix;
    fixing_matrix = {Vector3d(1 / scale_factor.x_, 0, 0, 0),
                     Vector3d(0, 1 / scale_factor.y_, 0, 0),
                     Vector3d(0, 0, 1 / scale_factor.z_, 0),
                     Vector3d(0, 0, 0, 1)};

    return gMatrix(matrix_scale, fixing_matrix, TransformType::SCALE);
};

gMatrix Matrix::translate(Vector3d target_position) {
    matrix_tr translate_matrix;
    translate_matrix = {Vector3d(1, 0, 0, target_position.x_),
                        Vector3d(0, 1, 0, target_position.y_),
                        Vector3d(0, 0, 1, target_position.z_),
                        Vector3d(0, 0, 0, 1)};

    return gMatrix(translate_matrix, TransformType::TRANSLATE);
};
gMatrix Matrix::rotate(TAxis rotation_axis, double angle) {
    angle = (angle * M_PI) / 180;

    matrix_tr rotate_matrix;

    double cos_t = cos(angle);
    double sin_t = sin(angle);

    switch (rotation_axis) {
        case TAxis::X_AXIS:
            rotate_matrix = {
                Vector3d(1, 0, 0, 0), Vector3d(0, cos_t, -sin_t, 0),
                Vector3d(0, sin_t, cos_t, 0), Vector3d(0, 0, 0, 1)};
            break;
        case TAxis::Y_AXIS:
            rotate_matrix = {Vector3d(cos_t, 0, sin_t, 0), Vector3d(0, 1, 0, 0),
                             Vector3d(-sin_t, 0, cos_t, 0),
                             Vector3d(0, 0, 0, 1)};
            break;
        case TAxis::Z_AXIS:
            rotate_matrix = {Vector3d(cos_t, -sin_t, 0, 0),
                             Vector3d(sin_t, cos_t, 0, 0), Vector3d(0, 0, 1, 0),
                             Vector3d(0, 0, 0, 1)};
            break;
    }
    return gMatrix(rotate_matrix, rotate_matrix, TransformType::ROTATE);
};
gMatrix Matrix::shearing(ShearTypes shearing_axis, double angle) {
    angle = (angle * M_PI) / 180;
    matrix_tr shear_matrix;
    matrix_tr inverse_t;

    double tg_t = tan(angle);

    switch (shearing_axis) {
        case ShearTypes::XZ:
            shear_matrix = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(tg_t, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            inverse_t = {Vector3d(1, 0, -tg_t, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            break;
        case ShearTypes::ZX:
            shear_matrix = {Vector3d(1, 0, tg_t, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};

            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(-tg_t, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearTypes::YZ:
            shear_matrix = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, tg_t, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, -tg_t, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearTypes::ZY:
            shear_matrix = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, tg_t, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, -tg_t, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearTypes::XY:
            shear_matrix = {Vector3d(1, 0, 0, 0), Vector3d(tg_t, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, -tg_t, 0, 0), Vector3d(0, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case ShearTypes::YX:
            shear_matrix = {Vector3d(1, tg_t, 0, 0), Vector3d(0, 1, 0, 0),
                            Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            inverse_t = {Vector3d(1, 0, 0, 0), Vector3d(-tg_t, 1, 0, 0),
                         Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
    }
    return gMatrix(shear_matrix, inverse_t, TransformType::SHEARING);
};
gMatrix Matrix::reflection(RPlane r_plane) {
    matrix_tr mirroring_matrix;

    switch (r_plane) {
        case RPlane::XY_PLANE:
            mirroring_matrix = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                                Vector3d(0, 0, -1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case RPlane::YZ_PLANE:
            mirroring_matrix = {Vector3d(-1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                                Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
        case RPlane::XZ_PLANE:
            mirroring_matrix = {Vector3d(1, 0, 0, 0), Vector3d(0, -1, 0, 0),
                                Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};
            break;
    }
    return gMatrix(mirroring_matrix, mirroring_matrix,
                   TransformType::REFLECTION);
};


gMatrix Matrix::world_camera(Vector3d eye, Vector3d at, Vector3d up){

    Vector3d vup = up - eye;

    Vector3d k_c = (eye - at).normalize();     // z da camera
    Vector3d i_c = (vup.cross_product(k_c));   // x da camera
    Vector3d j_c = (k_c.cross_product(i_c));   // y da camera

    k_c = k_c.normalize();
    i_c = i_c.normalize();
    j_c = j_c.normalize();

    // matriz que vai converter para as coordenadas de camera

    std::vector<Vector3d> t_c = {
        Vector3d(i_c.get(0), i_c.get(1), i_c.get(2), -(i_c.dot(eye))),
        Vector3d(j_c.get(0), j_c.get(1), j_c.get(2), -(j_c.dot(eye))),
        Vector3d(k_c.get(0), k_c.get(1), k_c.get(2), -(k_c.dot(eye))),
        Vector3d(0, 0, 0, 1)};

    return gMatrix(t_c, t_c, TransformType::CAMERA);
};
gMatrix Matrix::camera_world(Vector3d eye, Vector3d at, Vector3d up){
    
    Vector3d vup = up - eye;

    Vector3d k_c = (eye - at).normalize();     // z da camera
    Vector3d i_c = (vup.cross_product(k_c));   // x da camera
    Vector3d j_c = (k_c.cross_product(i_c));   // y da camera

    k_c = k_c.normalize();
    i_c = i_c.normalize();
    j_c = j_c.normalize();

    Eigen::Matrix4d e_tc;
    e_tc << i_c.get(0), i_c.get(1), i_c.get(2), -(i_c.dot(eye)), 
            j_c.get(0), j_c.get(1), j_c.get(2), -(j_c.dot(eye)),
            k_c.get(0), k_c.get(1), k_c.get(2), -(k_c.dot(eye)),
            0.0, 0.0, 0.0, 1.0;

    e_tc = e_tc.inverse().eval();
    
    std::vector<Vector3d> t_m = {
        Vector3d(e_tc(0,0), e_tc(0,1), e_tc(0,2), e_tc(0,3)),
        Vector3d(e_tc(1,0), e_tc(1,1), e_tc(1,2), e_tc(1,3)),
        Vector3d(e_tc(2,0), e_tc(2,1), e_tc(2,2), e_tc(2,3)),
        Vector3d(e_tc(3,0), e_tc(3,1), e_tc(3,2), e_tc(3,3))};

    return gMatrix(t_m, t_m, TransformType::CAMERA);

};