#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>

#include <vector>

#include "../Vector3d/Vector3d.h"

#include <memory>

class Shape;
class Scene;
struct ViewPort;
class Canvas {
   public:
    Canvas(int width, int height, int n_col, int n_row);
    ~Canvas();
    int n_cols();
    int n_rows();
    void add_pixel(Vector3d row);
    unsigned char *pixels = nullptr;
    void reset_count();
    void update_window();
    void wait_event(Shape **pick_shape, Scene &scene, Vector3d &camera,
                    long double &dx, long double &dy, long double &dJanela, ViewPort &vp, Vector3d **clicked_point);
    void init_window();

   private:
    int width_;
    int height_;
    int n_col_;
    int n_row_;
    int cur_index = 0;
    SDL_Window *window = nullptr;
    SDL_Surface *screen = nullptr;
    SDL_Surface *surf = nullptr;
    // int error = SDL_Init(SDL_INIT_EVERYTHING);
};

#endif