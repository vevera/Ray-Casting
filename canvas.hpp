#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SDL2/SDL.h>

#include <Eigen\Core>
#include <memory>
#include <vector>

using Eigen::Vector3d;

constexpr uint8_t c_ColorMax = 255;

inline Eigen::Vector3d ACESFilm(const Eigen::Vector3d &x) {
    constexpr double a = 2.51f;
    constexpr double b = 0.03f;
    constexpr double c = 2.43f;
    constexpr double d = 0.59f;
    constexpr double e = 0.14f;

    return ((x.array() * (a * x.array() + b)) /
            (x.array() * (c * x.array() + d) + e))
        .cwiseMin(1.0f)
        .cwiseMax(0.0f);
}

class Canvas {
   public:
    static Canvas create(const std::string &name, uint32_t width,
                         uint32_t height, uint32_t collumn_count,
                         uint32_t row_count) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            throw std::exception("Failed to create canvas! SDL_Init");
        }

        auto *window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, width, height,
                                        SDL_WINDOW_ALLOW_HIGHDPI);

        if (window == nullptr) {
            throw std::exception("Failed to create canvas! SDL_CreateWindow");
        }

        auto *screen = SDL_GetWindowSurface(window);

        std::vector<uint8_t> buffer(width * height * 3, 0);

        return Canvas({buffer, 0, window, screen, width, height, collumn_count,
                       row_count});
    }

    ~Canvas() {
        if (m.screen != nullptr)
            SDL_FreeSurface(m.screen);
        if (m.window != nullptr)
            SDL_DestroyWindow(m.window);

        SDL_Quit();
    }

    void update_window() {
        SDL_Rect offset;
        // Give the offsets to the rectangle
        offset.x = 0;
        offset.y = 0;

        auto *surf = SDL_CreateRGBSurfaceFrom(
            m.buffer.data(), m.width, m.height, 24, 3 * m.width, 0x000000ff,
            0x0000ff00, 0x00ff0000, 0xff000000);

        if (surf == nullptr)
            std::cout << "surf is null\n";
        // Blit the surface
        if (SDL_BlitSurface(surf, NULL, m.screen, &offset) != 0) {
            std::cout << "blit faild\n";
        }
        SDL_FreeSurface(surf);
        if (SDL_UpdateWindowSurface(m.window)) {
            std::cout << "update window faild\n";
        }
    }

    void wait_events() {
        SDL_Event windowEvent;
        while (true) {
            if (SDL_PollEvent(&windowEvent)) {
                if (SDL_QUIT == windowEvent.type) {
                    break;
                }
            }
        }
    }

    inline void set_pixel(const Vector3d &color) {
        Vector3d filmcolor = ACESFilm(color) * c_ColorMax;

        m.buffer[m.current++] = static_cast<uint8_t>(filmcolor(0));
        m.buffer[m.current++] = static_cast<uint8_t>(filmcolor(1));
        m.buffer[m.current++] = static_cast<uint8_t>(filmcolor(2));
    }

    void reset_count() { m.current = 0; }

    void resize(size_t) {
        // TODO: Create resize method
        // m.buffer.resize(size);
    }

    const uint32_t collumn_count() const { return m.collumn_count; }
    const uint32_t row_count() const { return m.row_count; }
    const uint32_t width() const { return m.width; }

   private:
    struct M {
        std::vector<uint8_t> buffer;
        size_t current;
        SDL_Window *window;
        SDL_Surface *screen;
        uint32_t width;
        uint32_t height;
        uint32_t collumn_count;
        uint32_t row_count;
    } m;

    Canvas(M m) : m{std::move(m)} { update_window(); }
};

#endif