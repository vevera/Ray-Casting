#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SDL2/SDL.h>

#include <Eigen\Core>
#include <chrono>
#include <memory>
#include <vector>

using Eigen::Vector3d;

constexpr uint8_t c_ColorMax = 255;
constexpr int32_t c_RenderEvent = 69;

inline Eigen::Vector3d ACESFilm(const Vector3d &x) {
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

struct Tile {
    Tile(uint64_t c0, uint64_t c1, uint64_t l0, uint64_t l1)
        : c0{c0}, c1{c1}, l0{l0}, l1{l1} {}
    uint64_t c0, c1, l0, l1;
};

class Canvas {
    using time_point = std::chrono::steady_clock::time_point;

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

        return Canvas({buffer, 0, window, screen, 0,
                       std::chrono::steady_clock::now(), width, height,
                       collumn_count, row_count});
    }

    enum Event { NONE=1, Quit, ReadyToRender, Reload };

    ~Canvas() {
        if (m.screen != nullptr)
            SDL_FreeSurface(m.screen);
        if (m.window != nullptr)
            SDL_DestroyWindow(m.window);

        SDL_Quit();
    }

    void update_window() {
        auto now = std::chrono::steady_clock::now();
        m.deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                          now - m.lastRenderTime)
                          .count() /
                      1000.0;
        m.lastRenderTime = now;

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

        surface_buffer_is_ready();
    }

    Event poll_event() {
        SDL_Event windowEvent;
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                return Event::Quit;
            }

            if (SDL_KEYDOWN == windowEvent.type) {
                if (windowEvent.key.keysym.sym == SDLK_r) {
                    return Event::Reload;
                }
            }

            if (SDL_USEREVENT == windowEvent.type &&
                windowEvent.user.code == c_RenderEvent) {
                return Event::ReadyToRender;
            }
        }
        return Event::NONE;
    }

    inline void set_pixel(uint64_t x, uint64_t y, Vector3d &&color) {
        color = ACESFilm(color) * c_ColorMax;

        const size_t i = (x * m.collumn_count * 3) + (y * 3);

        m.buffer[i] = static_cast<uint8_t>(color(0));
        m.buffer[i + 1] = static_cast<uint8_t>(color(1));
        m.buffer[i + 2] = static_cast<uint8_t>(color(2));
    }

    inline std::vector<Tile> get_tiles() {
        std::vector<Tile> tiles;

        constexpr uint64_t c_TileSize = 50;

        uint64_t c0 = 0;
        uint64_t l0 = 0;
        uint64_t l = 0;
        uint64_t c = 0;
        for (l = 0; l <= m.row_count; l += c_TileSize) {
            for (c = 0; c <= m.collumn_count; c += c_TileSize) {
                tiles.emplace_back(c0, c, l0, l);
                c0 = c;
            }
            l0 = l;
        }

        return tiles;
    }

    void reset_count() { m.current = 0; }

    void resize(size_t) {
        // TODO: Create resize method
        // m.buffer.resize(size);
    }

    const uint32_t collumn_count() const { return m.collumn_count; }
    const uint32_t row_count() const { return m.row_count; }
    const uint32_t width() const { return m.width; }
    const double delta_time() const { return m.deltaTime; }

   private:
    struct M {
        std::vector<uint8_t> buffer;
        size_t current;
        SDL_Window *window;
        SDL_Surface *screen;
        double deltaTime;
        time_point lastRenderTime;
        uint32_t width;
        uint32_t height;
        uint32_t collumn_count;
        uint32_t row_count;
    } m;

    void surface_buffer_is_ready() {
        SDL_Event event = {0};
        memset(&event, 0, sizeof(event));

        event.user.type = SDL_USEREVENT;
        event.user.code = c_RenderEvent;

        SDL_PushEvent(&event);
    }

    Canvas(M m) : m{std::move(m)} { surface_buffer_is_ready(); }
};

#endif