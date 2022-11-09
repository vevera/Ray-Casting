#include "canvas.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>

Canvas::Canvas(int width, int height, int n_col, int n_row)
    : width_(width), height_(height), n_col_(n_col), n_row_(n_row) {
    this->pixels =
        (unsigned char *) malloc(sizeof(unsigned char) * width * height * 3);

    // if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
    //     this->window = SDL_CreateWindow("Cena", SDL_WINDOWPOS_UNDEFINED,
    //                                     SDL_WINDOWPOS_UNDEFINED, width,
    //                                     height, SDL_WINDOW_ALLOW_HIGHDPI);

    //     if (window != nullptr) {
    //         this->screen = SDL_GetWindowSurface(this->window);
    //     }
    // }
}

// Canvas::~Canvas() {
//     if (screen != nullptr)
//         SDL_FreeSurface(screen);
//     if (surf != nullptr)
//         SDL_FreeSurface(surf);
//     if (window != nullptr)
//         SDL_DestroyWindow(window);

//     SDL_Quit();

//     if (pixels != nullptr)
//         delete[] pixels;
// }

int Canvas::n_cols() { return n_col_; }

int Canvas::n_rows() { return n_row_; }

void Canvas::add_pixel(Vector3d row) {
    pixels[cur_index] = row.x_ * 255.0;
    pixels[cur_index + 1] = row.y_ * 255.0;
    pixels[cur_index + 2] = row.z_ * 255.0;

    cur_index += 3;
}

// void Canvas::update_window() {
//     SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(
//         (void *) this->pixels, width_, height_, 24, 3 * width_, 0x000000ff,
//         0x0000ff00, 0x00ff0000, 0xff000000);

//     SDL_Rect offset;

//     // Give the offsets to the rectangle
//     offset.x = 0;
//     offset.y = 0;

//     // Blit the surface
//     SDL_BlitSurface(surf, NULL, this->screen, &offset);
//     SDL_FreeSurface(surf);
//     SDL_UpdateWindowSurface(window);

//     if (NULL == surf) {
//         std::cout << "Could not create window: " << SDL_GetError() <<
//         std::endl; return;
//     }
// }

// void Canvas::wait_event() {
//     std::thread wait_event_thread([]() {
//         SDL_Event windowEvent;

//         while (true) {
//             std::cout << "Ite" << std::endl;
//             if (SDL_PollEvent(&windowEvent)) {
//                 if (SDL_QUIT == windowEvent.type) {
//                     break;
//                 }
//             }
//         }
//     });
// }