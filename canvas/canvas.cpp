#include "canvas.h"

#include <algorithm>
#include <cmath>
#include <iostream>
Canvas::Canvas(int width, int height, int n_col, int n_row)
    : width_(width), height_(height), n_col_(n_col), n_row_(n_row) {
    pixels =
        (unsigned char *) malloc(sizeof(unsigned char) * width * height * 3);
};

int Canvas::n_cols() { return n_col_; }

int Canvas::n_rows() { return n_row_; }

void Canvas::add_pixel(Vector4d row) {
    pixels[cur_index] = row(0) * 255.0;
    pixels[cur_index + 1] = row(1) * 255.0;
    pixels[cur_index + 2] = row(2) * 255.0;

    cur_index += 3;
}