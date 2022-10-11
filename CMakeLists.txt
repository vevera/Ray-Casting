cmake_minimum_required(VERSION 3.0.0)
project(raycasting VERSION 0.1.0)

include(CTest)
enable_testing()

# SET(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/src/include")
# SET(SDL2_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/SDL2.dll")

# find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
# find_library(SDL2_LIBRARY NAME SDL2)

list(APPEND CMAKE_PREFIX_PATH src/lib/cmake/SDL2/)
find_package(SDL2 REQUIRED)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/include")
set(SDL2_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
include_directories( ${SDL2_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(raycasting Vector3d/Vector3d.cpp shapes/shape.cpp shapes/plane/plane.cpp shapes/sphere/sphere.cpp shapes/cylinder/cylinder.cpp shapes/cone/cone.cpp shapes/mesh/mesh.cpp scene/scene.cpp canvas/canvas.cpp traceray/traceray.cpp main.cpp)

target_link_libraries( raycasting ${MINGW32_LIBRARY} ${OpenCV_LIBS}  ${SDL_LIBRARIES} ${SDL2_LIB_DIR}/libSDL2.dll.a ${SDL2_LIB_DIR}/libSDL2main.a)
add_definitions(-DSDL_MAIN_HANDLED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
