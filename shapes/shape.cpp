#include "shape.h"

#include <iostream>
Shape::Shape(Reflexivity reflexivity, std::string texture_path)
    : reflexivity_(reflexivity), texture_path_(texture_path) {
    if (!texture_path.empty()) {
        // img = imread(texture_path, cv::IMREAD_COLOR);
        // img_w = img.cols;
        // img_h = img.rows;
        // cv::Vec3b bgrPixel = img.at<cv::Vec3b>(30, 30);
        // std::cout << bgrPixel << std::endl;
        // std::cout << img_w << std::endl;
        // std::cout << img_h << std::endl;
    }
};

Vector4d* Shape::kd(int x, int y) {
    if (this->has_texture()) {
        return this->get_pixel(x, y);
    }
    return reflexivity_.kd;
};

Vector4d* Shape::ke(int x, int y) {
    if (this->has_texture()) {
        return this->get_pixel(x, y);
    }
    return reflexivity_.ke;
};

Vector4d* Shape::ka(int x, int y) {
    if (this->has_texture()) {
        return this->get_pixel(x, y);
    }
    return reflexivity_.ka;
};

double Shape::m() { return reflexivity_.m; };

bool Shape::has_texture() { return !texture_path_.empty(); };

Vector4d* Shape::get_pixel(double x, double z) {
    double fx = (x - (-200.0)) / (200.0 - (-200.0));
    double fz = (z - (-400.0)) / (0.0 - (-400.0));

    int map_x = 0.0 + fx * (img_w - 1);
    int map_z = 0.0 + fz * (img_h - 1);

    // cv::Vec3b bgrPixel = img.at<cv::Vec3b>(map_x, map_z);

    if (color)
        delete color;

    // color = new Vector4d(bgrPixel[2] / 255.0, bgrPixel[1] / 255.0,
    //                      bgrPixel[0] / 255.0, 1);
    return color;
}
