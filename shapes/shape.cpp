#include "shape.h"
#include <iostream>
Shape::Shape(Reflexivity reflexivity, std::string texture_path)
    : reflexivity_(reflexivity), texture_path_(texture_path)
{

    if (!texture_path.empty())
    {
        img = imread(texture_path, cv::IMREAD_COLOR);
        cv::resize(img, img, cv::Size(200, 200), cv::INTER_LINEAR);

        img_w = img.cols;
        img_h = img.rows;
        cv::Vec3b bgrPixel = img.at<cv::Vec3b>(30, 30);
        std::cout << bgrPixel << std::endl;
        std::cout << img_w << std::endl;
        std::cout << img_h << std::endl;
    }
};

Vector3d *Shape::kd(int x, int y)
{
    if (this->has_texture())
    {
        return this->get_pixel(x, y);
    }
    return reflexivity_.kd;
};

Vector3d *Shape::ke(int x, int y)
{

    if (this->has_texture())
    {
        return this->get_pixel(x, y);
    }
    return reflexivity_.ke;
};

Vector3d *Shape::ka(int x, int y)
{
    if (this->has_texture())
    {
        return this->get_pixel(x, y);
    }
    return reflexivity_.ka;
};

double Shape::m()
{
    return reflexivity_.m;
};

bool Shape::has_texture()
{
    return !texture_path_.empty();
};

Vector3d *Shape::get_pixel(int x, int y)
{

    int map_x = x % img_h;
    int map_y = y % img_w;
    cv::Vec3b bgrPixel = img.at<cv::Vec3b>(map_x, map_y);

    return new Vector3d(bgrPixel[2] / 255.0, bgrPixel[1] / 255.0, bgrPixel[0] / 255.0);
}