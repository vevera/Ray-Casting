#include "matrix.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../Vector3d/Vector3d.h"
AccMatrix gMatrix::operator*(gMatrix const &m) {
    shared_ptr<AccMatrix> acc = std::make_shared<AccMatrix>();

    acc->acc_t->push_back(transform_matrix);
    acc->acc_n->push_back(n_fix);

    acc->acc_t->push_back(m.transform_matrix);
    acc->acc_n->push_back(m.n_fix);

    return *acc.get();
};

AccMatrix gMatrix::operator*(AccMatrix &acc) {
    shared_ptr<AccMatrix> acc_shared =
        std::make_shared<AccMatrix>(std::move(acc));

    // acc_shared->acc_t->insert(acc_shared->acc_t->begin(), transform_matrix);
    // acc_shared->acc_n->insert(acc_shared->acc_n->begin(), n_fix);

    return *acc_shared.get();
};

AccMatrix AccMatrix::operator*(gMatrix m) {
    shared_ptr<AccMatrix> acc = std::make_shared<AccMatrix>();
    acc->acc_t = acc_t;
    acc->acc_n = acc_n;

    acc->acc_t->push_back(m.transform_matrix);
    acc->acc_n->push_back(m.n_fix);

    return *acc.get();
};

AccMatrix AccMatrix::operator*(AccMatrix &acc) {
    shared_ptr<AccMatrix> acc_shared =
        std::make_shared<AccMatrix>(std::move(acc));

    std::for_each(acc_t->end(), acc_t->begin(), [&](auto &e) {
        std::cout << "HERE \n";
        acc_shared->acc_t->insert(acc_shared->acc_t->begin(), e);
    });
    // acc_shared->acc_t->insert(acc_shared->acc_t->end(), acc_t->begin(),
    //                           acc_t->end());
    // acc_shared->acc_n->insert(acc_shared->acc_n->begin(), acc_n->begin(),
    //                           acc_n->end());

    return *acc_shared.get();
};

gMatrix Matrix::scale(Vector3d scale_factor) {
    matrix_t matrix_scale;
    matrix_scale = {Vector3d(scale_factor.x_, 0, 0, 0),
                    Vector3d(0, scale_factor.y_, 0, 0),
                    Vector3d(0, 0, scale_factor.z_, 0), Vector3d(0, 0, 0, 1)};

    matrix_t fixing_matrix;
    fixing_matrix = {Vector3d(1 / scale_factor.x_, 0, 0, 0),
                     Vector3d(0, 1 / scale_factor.y_, 0, 0),
                     Vector3d(0, 0, 1 / scale_factor.z_, 0),
                     Vector3d(0, 0, 0, 1)};

    return gMatrix(matrix_scale, fixing_matrix, TransformType::SCALE);
};

gMatrix Matrix::translate(Vector3d target_position) {
    matrix_t translate_matrix;
    translate_matrix = {Vector3d(1, 0, 0, target_position.x_),
                        Vector3d(0, 1, 0, target_position.y_),
                        Vector3d(0, 0, 1, target_position.z_),
                        Vector3d(0, 0, 0, 1)};

    return gMatrix(translate_matrix, TransformType::TRANSLATE);
};
gMatrix Matrix::rotate(TAxis rotation_axis, double angle) {
    angle = (angle * M_PI) / 180;

    matrix_t rotate_matrix;

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
    matrix_t shear_matrix;
    matrix_t inverse_t;

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
    matrix_t mirroring_matrix;

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
    return gMatrix(mirroring_matrix, TransformType::REFLECTION);
};