#ifndef SHAPE_H
#define SHAPE_H

#include "../Vector3d/Vector3d.h"
#include <memory>
#include <cmath>

#include <opencv2/opencv.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

/*#define eps 0.0001*/

enum Axis
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

enum ReflectionPlane
{
    XY_PLANE,
    YZ_PLANE,
    XZ_PLANE
};

enum ShearingTypes
{
    XZ,
    ZX,
    YZ,
    ZY,
    XY,
    YX
};

struct Reflexivity
{
    Vector3d *kd;
    Vector3d *ke;
    Vector3d *ka;
    double m;

    Reflexivity()
    {
        kd = new Vector3d(1, 1, 1);
        ke = new Vector3d(1, 1, 1);
        ka = new Vector3d(1, 1, 1);
        m = 1;
    }

    Reflexivity(Vector3d *kd_, Vector3d *ke_, Vector3d *ka_, double m_)
    {
        kd = kd_;
        ke = ke_;
        ka = ka_;
        m = m_;
    }
};

class Shape
{

public:
    Shape(Reflexivity reflexivity, std::string texture_path);
    ~Shape(){};

    virtual double intersect(Vector3d p_0, Vector3d dr) = 0;
    virtual Vector3d normal(Vector3d p_i) = 0;

    Vector3d *kd(int x, int y);
    Vector3d *ke(int x, int y);
    Vector3d *ka(int x, int y);
    double m();

    bool has_texture();
    Vector3d *get_pixel(double x, double z);

    // transformations

    // virtual void scaleX(double scale_factor) = 0;
    // virtual void scaleY(double scale_factor) = 0;
    // virtual void scaleZ(double scale_factor) = 0;
    // virtual void translate(Vector3d target_position) = 0;
    // virtual void rotate(Axis rotation_axis, double angle) = 0;
    // virtual void shearing(Axis shearing_axis, double sh_1, double sh_2) = 0;
    // virtual void reflection(ReflectionPlane r_plane) = 0;

private:
    Reflexivity reflexivity_;
    std::string texture_path_ = "";
    cv::Mat img;
    Vector3d *color = nullptr;
    int img_w = 0;
    int img_h = 0;
};

#endif