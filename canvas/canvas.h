#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>

#include <vector>

#include "../Vector3d/Vector3d.h"

class Canvas {
   public:
    Canvas(int width, int height, int n_col, int n_row);
    //~Canvas();
    int n_cols();
    int n_rows();
    void add_pixel(Vector3d row);
    unsigned char *pixels = nullptr;
    // void update_window();
    // void wait_event();

   private:
    int width_;
    int height_;
    int n_col_;
    int n_row_;
    int cur_index = 0;
    // SDL_Window *window = nullptr;
    // SDL_Surface *screen = nullptr;
    // SDL_Surface *surf = nullptr;
    // int error = SDL_Init(SDL_INIT_EVERYTHING);
};

#endif