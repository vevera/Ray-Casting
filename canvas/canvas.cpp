#include "canvas.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>

#include "../scene/scene.h"
#include "../shapes/shape.h"

Canvas::Canvas(int width, int height, int n_col, int n_row)
    : width_(width), height_(height), n_col_(n_col), n_row_(n_row) {
    this->pixels =
        (unsigned char *) malloc(sizeof(unsigned char) * width * height * 3);

    //td::cout << "PIXELS MALLOC" << sizeof(pixels) << std::endl;
}

void Canvas::init_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        this->window = SDL_CreateWindow("Cena", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width_,
                                        height_, SDL_WINDOW_ALLOW_HIGHDPI);

        if (window != nullptr) {
            this->screen = SDL_GetWindowSurface(this->window);
        }
    }
}

Canvas::~Canvas() {
    if (screen != nullptr)
        SDL_FreeSurface(screen);
    if (surf != nullptr)
        SDL_FreeSurface(surf);
    if (window != nullptr)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

int Canvas::n_cols() { return n_col_; }

int Canvas::n_rows() { return n_row_; }

void Canvas::add_pixel(Vector3d row) {
    pixels[cur_index] = row.x_ * 255.0;
    pixels[cur_index + 1] = row.y_ * 255.0;
    pixels[cur_index + 2] = row.z_ * 255.0;

    cur_index += 3;
}
void Canvas::reset_count() { cur_index = 0; };
void Canvas::update_window() {

    SDL_Rect offset;
    // Give the offsets to the rectangle
    offset.x = 0;
    offset.y = 0;

    surf = SDL_CreateRGBSurfaceFrom((void *) pixels, width_, height_, 24,
                                    3 * width_, 0x000000ff, 0x0000ff00,
                                    0x00ff0000, 0xff000000);
    // Blit the surface
    SDL_BlitSurface(surf, NULL, screen, &offset);
    SDL_FreeSurface(surf);
    SDL_UpdateWindowSurface(window);
}

void Canvas::wait_event(Shape **pick_shape, Scene &scene, Vector3d &camera,
                        double &dx, double &dy, double &dJanela, ViewPort &vp, Vector3d **clicked_point) {
    Vector3d direction, p_start;
    double xj, yj;
    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
            if (SDL_MOUSEBUTTONDOWN == windowEvent.type) {
                yj = (vp.height / 2.0) - (dy / 2.0) -
                     (windowEvent.motion.y * dy);
                xj = (-vp.width / 2.0) + (dx / 2.0) +
                     (windowEvent.motion.x * dx);

               //std::cout << "X: " << xj << "Y: " << yj << "h: " << (*vp)->height << "w: " << (*vp)->width;     

                p_start = Vector3d(xj, yj, -dJanela);

                direction = (p_start - camera).normalize();

                *pick_shape = scene.picking(camera, xj, yj, dJanela, clicked_point);

                if (*pick_shape != nullptr) {
                    std::cout << "PICKING CONCLUIDO: "
                          << (*pick_shape)->ka(1, 1).toStr() << std::endl;
                }
                
            }
        }
    }
}