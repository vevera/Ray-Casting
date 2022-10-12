cmake_minimum_required(VERSION 3.0.0)
project(raycasting VERSION 0.1.0)

include(CTest)
enable_testing()

list(APPEND CMAKE_PREFIX_PATH src/lib/cmake/SDL2/)
#list(APPEND CMAKE_PREFIX_PATH C:/opencv/build/x64/mingw/lib)
#find_package(SDL2 REQUIRED)
#find_package(OpenCV REQUIRED)


set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/include")
set(SDL2_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
set(OpenCV_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/opencv/include")
set(OpenCV_LIB_DIRS "${CMAKE_CURRENT_LIST_DIR}/opencv/lib")


message("${SDL2_INCLUDE_DIRS}")
message("${OpenCV_LIBS}")
include_directories( 
    ${SDL2_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    )

add_executable(raycasting 
                Vector3d/Vector3d.cpp 
                shapes/shape.cpp 
                shapes/plane/plane.cpp 
                shapes/sphere/sphere.cpp 
                shapes/cylinder/cylinder.cpp 
                shapes/cone/cone.cpp 
                shapes/mesh/mesh.cpp 
                scene/scene.cpp 
                canvas/canvas.cpp 
                traceray/traceray.cpp 
                main.cpp)


message(" a aaa ${ImageMagick_INCLUDE_DIRS}")
#target_link_directories(raycasting PUBLIC ${OpenCV_LIB_DIRS})
target_link_libraries( 
    raycasting 
    #${OpenCV_LIBS}
    
    ${OpenCV_LIB_DIRS}/libopencv_calib3d341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_core341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_dnn341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_features2d341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_flann341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_highgui341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_imgcodecs341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_imgproc341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_ml341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_objdetect341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_photo341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_shape341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_stitching341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_superres341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_video341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_videoio341.dll.a
    ${OpenCV_LIB_DIRS}/libopencv_videostab341.dll.a
    ${SDL2_LIB_DIR}/libSDL2.dll.a
    ${SDL2_LIB_DIR}/libSDL2main.a
    )

add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties( raycasting PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/" )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
