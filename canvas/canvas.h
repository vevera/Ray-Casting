#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "../Vector3d/Vector3d.h"

class Canvas
{

public:
    Canvas(int width, int height, int n_col, int n_row);
    int n_cols();
    int n_rows();
    void add_row(std::vector<Vector3d> row);
    void add_pixel(Vector3d row);
    void print_vector();
    unsigned char* pixels;

private:
    int width_;
    int height_;
    int n_col_;
    int n_row_;
    int cur_index = 0;
    std::vector<std::vector<Vector3d>> color_matrix;
};

#endif