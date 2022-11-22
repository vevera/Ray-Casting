#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "../Vector3d/Vector3d.h"
#include "../canvas/canvas.h"
#include "../light/light.h"
#include "../shapes/shape.h"

using std::string;

enum class Projection {

    PERSPECTIVE,
    ORTHOGRAPHIC

};

struct ViewPort {
    int width;
    int height;
    double z;

    ViewPort(int width_, int height_, double &z_) {
        width = width_;
        height = height_;
        z = z_;
    }
};

class Scene {
   public:
    Scene(std::vector<Shape *> shapes, Canvas canvas,
          std::vector<Light *> lights, gMatrix wc);
    void take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor);
    Shape *picking(Vector3d &camera, double x, double y, double t_min, Vector3d **clicked_point);
    void set_projection(Projection projection_);

   private:
    std::vector<Shape *> shapes_;
    Canvas canvas_;
    std::vector<Light *> lights_;
    Projection projection;
};

#endif