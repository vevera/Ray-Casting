#ifndef SHAPE_H
#define SHAPE_H

#include "../Vector3d/Vector3d.h"
#include <memory>
#include <cmath>

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
    Shape(Vector3d color, Reflexivity reflexivity);
    virtual double intersect(Vector3d p_0, Vector3d dr) = 0;
    virtual Vector3d normal(Vector3d p_i) = 0;
    Vector3d *kd();
    Vector3d *ke();
    Vector3d *ka();
    double m();
    Vector3d *color();

private:
    Vector3d color_;
    Reflexivity reflexivity_;
};

#endif