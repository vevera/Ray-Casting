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
    Vector3d *intensity;
    Vector3d *position;
    string type;

    Light()
    {
        intensity = new Vector3d(1, 1, 1);
        position = new Vector3d(0, 0, 0);
        type = "point";
    }

    Light(Vector3d *intensity_, Vector3d *position_, string type_)
    {
        intensity = intensity_;
        position = position_;
        type = type_;
    }

    Light(Vector3d *intensity_)
    {
        intensity = intensity_;
        position = new Vector3d(0, 0, 0);
        type = "ambient";
    }
};

struct ViewPort
{
    int width;
    int height;
    double z;

    ViewPort(int width_, int height_, int z_)
    {
        width = width_;
        height = height_;
        z = z_;
    }
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