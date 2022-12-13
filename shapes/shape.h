#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include <memory>
// #include <opencv2/core.hpp>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/opencv.hpp>

#include "../Vector3d/Vector3d.h"
#include "../matrix/matrix.h"

struct Reflexivity {
    Vector3d kd;
    Vector3d ke;
    Vector3d ka;
    long double m;

    Reflexivity() {
        kd = Vector3d(1, 1, 1);
        ke = Vector3d(1, 1, 1);
        ka = Vector3d(1, 1, 1);
        m = 1;
    }

    Reflexivity(Vector3d kd_, Vector3d ke_, Vector3d ka_, long double m_) {
        kd = kd_;
        ke = ke_;
        ka = ka_;
        m = m_;
    }
};

class Shape {
   public:
    Shape(Reflexivity reflexivity, Vector3d shape_center_);
    ~Shape(){};
    virtual Shape * Copy() = 0;

    virtual long double intersect(Vector3d &p_0, Vector3d &dr) = 0;
    virtual Vector3d normal(Vector3d &p_i) = 0;

    Vector3d kd(int x, int y);
    Vector3d ke(int x, int y);
    Vector3d ka(int x, int y);

    void set_kd(Vector3d kd);
    void set_ke(Vector3d ke);
    void set_ka(Vector3d ka);
    void set_m(long double m);

    long double m();

    virtual void operator*(AccMatrix m) = 0;
    virtual void operator*(gMatrix m) = 0;

    Vector3d shape_center;
    bool ignore_shape_ = false;
    Reflexivity reflexivity_;
   private:
    //Reflexivity reflexivity_;
    std::string texture_path_ = "";
    Vector3d *color = nullptr;
    int img_w = 0;
    int img_h = 0;
};

#endif