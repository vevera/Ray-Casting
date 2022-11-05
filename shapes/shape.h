#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include <memory>
// #include <opencv2/core.hpp>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/opencv.hpp>

// #include "../Vector3d/Vector3d.h"
#include <Eigen/Dense>

#include "../matrix/matrix.h"

using Eigen::Vector4d;

enum Axis { X_AXIS, Y_AXIS, Z_AXIS };

enum ReflectionPlane { XY_PLANE, YZ_PLANE, XZ_PLANE };

enum ShearingTypes { XZ, ZX, YZ, ZY, XY, YX };

struct Reflexivity {
    Vector4d *kd;
    Vector4d *ke;
    Vector4d *ka;
    double m;

    Reflexivity() {
        kd = new Vector4d(1, 1, 1, 1);
        ke = new Vector4d(1, 1, 1, 1);
        ka = new Vector4d(1, 1, 1, 1);
        m = 1;
    }

    Reflexivity(Vector4d *kd_, Vector4d *ke_, Vector4d *ka_, double m_) {
        kd = kd_;
        ke = ke_;
        ka = ka_;
        m = m_;
    }
};

class Shape {
   public:
    Shape(Reflexivity reflexivity, std::string texture_path);
    ~Shape(){};

    virtual double intersect(Vector4d &p_0, Vector4d &dr) = 0;
    virtual Vector4d normal(Vector4d &p_i) = 0;

    Vector4d *kd(int x, int y);
    Vector4d *ke(int x, int y);
    Vector4d *ka(int x, int y);
    double m();

    bool has_texture();
    Vector4d *get_pixel(double x, double z);
    virtual void operator*(AccMatrix m) = 0;
    virtual void operator*(gMatrix m) = 0;
    // virtual void operator*(gMatrix &m);

   private:
    Reflexivity reflexivity_;
    std::string texture_path_ = "";
    // cv::Mat img;
    Vector4d *color = nullptr;
    int img_w = 0;
    int img_h = 0;
};

#endif