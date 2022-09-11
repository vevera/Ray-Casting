#ifndef SCENE_H
#define SCENE_H

#include "../Vector3d/Vector3d.h"
#include <vector>
#include <string>
#include "../shapes/shape.h"
#include "../canvas/canvas.h"

using std::string;

struct Light
{
    Vector3d *intensity = new Vector3d(1, 1, 1);
    Vector3d *position = new Vector3d(0, 0, 0);
    string type = "point";
};

struct ViewPort
{
    int width;
    int height;
    double z;
};

class Scene
{

public:
    Scene(std::vector<Shape *> shapes, Canvas canvas, Light light, Light ambient_light);
    void take_a_picture(Vector3d camera, ViewPort vp, Vector3d bgColor);

private:
    std::vector<Shape *> shapes_;
    Canvas canvas_;
    Light light_;
    Light ambient_light_;
};

#endif