#include "canvas.h"

#include <algorithm>
#include <iostream>
#include <cmath>
Canvas::Canvas(int width, int height,
               int n_col, int n_row) : width_(width), height_(height),
                                       n_col_(n_col), n_row_(n_row)
{
    pixels = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
};

int Canvas::n_cols()
{
    return n_col_;
}

int Canvas::n_rows()
{
    return n_row_;
}

void Canvas::add_pixel(Vector3d row)
{

    // pixels[cur_index] = row.x_ > 0 ? std::min(row.x_ * 255.0, 255.0) : std::max(0.0, row.x_);
    // pixels[cur_index + 1] = row.y_ > 0 ? std::min(row.y_ * 255.0, 255.0) : std::max(0.0, row.y_);
    // pixels[cur_index + 2] = row.z_ > 0 ? std::min(row.z_ * 255.0, 255.0) : std::max(0.0, row.z_);

    // pixels[cur_index] = std::max(row.x_ * 255.0, 0.0);
    // pixels[cur_index + 1] = std::max(row.y_ * 255.0, 0.0);
    // pixels[cur_index + 2] = std::max(row.z_ * 255.0, 0.0);

    pixels[cur_index] = row.x_ * 255.0;
    pixels[cur_index + 1] = row.y_ * 255.0;
    pixels[cur_index + 2] = row.z_ * 255.0;

    cur_index += 3;
}