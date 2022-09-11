#include "canvas.h"

#include <algorithm>
#include <iostream>
Canvas::Canvas(int width, int height,
               int n_col, int n_row) : width_(width), height_(height),
                                       n_col_(n_col), n_row_(n_row){
                                        pixels = (unsigned char *) malloc (sizeof(unsigned char) * width * height * 3);
                                       };

int Canvas::n_cols()
{
    return n_col_;
}

int Canvas::n_rows()
{
    return n_row_;
}

void Canvas::add_row(std::vector<Vector3d> row)
{

    color_matrix.push_back(row);
}

void Canvas::print_vector()
{
    std::cout << "print vector: " << color_matrix.size() << std::endl;
    std::for_each(begin(color_matrix), end(color_matrix),
                  [](auto &row)
                  {
                      std::for_each(begin(row), end(row), [](auto &element)
                                    { std::cout << element.toStr() << " | "; });

                      std::cout << std::endl;
                  });
}

void Canvas::add_pixel(Vector3d row) {
    
    pixels[cur_index] = row.x_;
    pixels[cur_index + 1] = row.y_;
    pixels[cur_index + 2] = row.z_;

    cur_index += 3;

}