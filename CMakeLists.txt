cmake_minimum_required(VERSION 3.0.0)
project(raycasting VERSION 0.1.0)

include(CTest)
enable_testing()

list(APPEND CMAKE_PREFIX_PATH src/lib/cmake/SDL2/)
find_package(SDL2 REQUIRED)
find_package(OpenCV REQUIRED)

#find_package(ImageMagick COMPONENTS Magick++ MagickCore)
#find_package(ImageMagick REQUIRED COMPONENTS Magick++)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/include")
set(SDL2_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
set(OpenCV_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/opencv/include")
#set(MAGICK_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/magic/include")
#set(MAGICK_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/magic/lib")

include_directories( 
    ${SDL2_INCLUDE_DIRS}
    #${MAGICK_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    )

add_executable(raycasting Vector3d/Vector3d.cpp shapes/shape.cpp shapes/plane/plane.cpp shapes/sphere/sphere.cpp shapes/cylinder/cylinder.cpp shapes/cone/cone.cpp shapes/mesh/mesh.cpp scene/scene.cpp canvas/canvas.cpp traceray/traceray.cpp main.cpp)

# target_compile_definitions(raycasting PRIVATE
#   MAGICKCORE_QUANTUM_DEPTH=16
#   MAGICKCORE_HDRI_ENABLE=0
# )

message(" a aaa ${ImageMagick_INCLUDE_DIRS}")
target_link_libraries( 
    raycasting 
    ${OpenCV_LIBS}
    # ${MAGICK_LIB_DIR}/CORE_RL_Magick++_.lib
    # ${MAGICK_LIB_DIR}/CORE_RL_MagickCore_.lib
    # ${MAGICK_LIB_DIR}/CORE_RL_MagickWand_.lib
    ${SDL_LIBRARIES} 
    ${SDL2_LIB_DIR}/libSDL2.dll.a 
    ${SDL2_LIB_DIR}/libSDL2main.a
    )

add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties( raycasting PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/" )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
