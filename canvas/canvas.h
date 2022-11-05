#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

// #include "../Vector3d/Vector3d.h"

#include <Eigen/Dense>

using Eigen::Vector4d;

class Canvas {
   public:
    Canvas(int width, int height, int n_col, int n_row);
    int n_cols();
    int n_rows();
    void add_pixel(Vector4d row);
    unsigned char *pixels;

   private:
    int width_;
    int height_;
    int n_col_;
    int n_row_;
    int cur_index = 0;
};

#endif