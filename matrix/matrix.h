#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <tuple>
#include <vector>

#include "../Vector3d/Vector3d.h"

#define matrix_tr std::vector<Vector3d>

using std::shared_ptr;
using std::vector;

enum class TransformType {
    NONE,
    SCALE,
    TRANSLATE,
    ROTATE,
    SHEARING,
    REFLECTION,
    MIXED,
    CAMERA,
};

enum class TAxis { X_AXIS, Y_AXIS, Z_AXIS };

enum class RPlane { XY_PLANE, YZ_PLANE, XZ_PLANE };

enum class ShearTypes { XZ, ZX, YZ, ZY, XY, YX };

// struct gMatrix;
struct AccMatrix;

struct gMatrix {
    matrix_tr transform_matrix;
    matrix_tr n_fix;
    TransformType t_type;

    gMatrix() : t_type(TransformType::NONE) {}

    gMatrix(matrix_tr t, TransformType t_) {
        transform_matrix = t;
        n_fix = {Vector3d(1, 0, 0, 0), Vector3d(0, 1, 0, 0),
                 Vector3d(0, 0, 1, 0), Vector3d(0, 0, 0, 1)};

        t_type = t_;
    }

    gMatrix(matrix_tr t, matrix_tr n, TransformType t_) {
        transform_matrix = t;
        n_fix = n;
        t_type = t_;
    }

    AccMatrix operator*(gMatrix const &m);

    AccMatrix operator*(AccMatrix &acc);
};

struct AccMatrix {
    shared_ptr<vector<gMatrix>> acc = std::make_shared<vector<gMatrix>>();

    AccMatrix() {}

    void operator=(const gMatrix &m);

    AccMatrix operator*(gMatrix m);

    AccMatrix operator*(AccMatrix &acc_o);
};

class Matrix {
   public:
    Matrix() = default;
    ~Matrix(){};

    static gMatrix scale(Vector3d scale_factor);
    static gMatrix translate(Vector3d target_position);
    static gMatrix rotate(TAxis rotation_axis, long double angle);
    static gMatrix shearing(ShearTypes shearing_axis, long double angle);
    static gMatrix reflection(RPlane r_plane);
    static gMatrix world_camera(Vector3d eye, Vector3d at, Vector3d up);
    static gMatrix camera_world(Vector3d eye, Vector3d at, Vector3d up);
};

#endif