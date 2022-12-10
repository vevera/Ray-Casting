cmake_minimum_required(VERSION 3.7)
project(raycasting VERSION 0.1.0)

include(CTest)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


list(APPEND CMAKE_PREFIX_PATH src/lib/cmake/SDL2/)
list(APPEND CMAKE_PREFIX_PATH Eigen/)

# set(Eigen3_DIR "${CMAKE_CURRENT_LIST_DIR}/Eigen/cmake")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Eigen/build")
#set(Eigen3_DIR "${CMAKE_CURRENT_LIST_DIR}/Eigen/cmake")
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(SDL2 REQUIRED)

#list(APPEND CMAKE_PREFIX_PATH eigen-3.4.0/cmake/)
#list(APPEND CMAKE_PREFIX_PATH C:/opencv/build/x64/mingw/lib)
#find_package(SDL2 REQUIRED)
#find_package(OpenCV REQUIRED)
# set(Eigen3_DIR "eigen-3.4.0/cmake/")
# find_package (Eigen3 3.3 REQUIRED NO_MODULE)


#set(EIGEN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Eigen")
# set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/include")
# set(SDL2_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/src/lib")
# set(OpenCV_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/opencv/include")
# set(OpenCV_LIB_DIRS "${CMAKE_CURRENT_LIST_DIR}/opencv/lib")
#set(EIGEN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/eigen-3.4.0/Eigen")

set(  
      RAYCASTING_INCLUDE_FILES
      Vector3d/Vector3d.h
      matrix/matrix.h 
      shapes/shape.h 
      shapes/plane/plane.h 
      shapes/sphere/sphere.h 
      shapes/cylinder/cylinder.h 
      shapes/cone/cone.h 
      shapes/mesh/mesh.h 
      shapes/complex/complex_object.h 
      scene/scene.h 
      canvas/canvas.h
      light/light.h
      light/point/point_light.h
      light/ambient/ambient.h
      light/directional/directional.h
      light/spot/spot.h
      traceray/traceray.h
    )

message("${SDL2_LIBRARIES}")
message("${SDL2_INCLUDE_DIRS}")
include_directories( 
    ${SDL2_INCLUDE_DIRS}
    # ${OpenCV_INCLUDE_DIRS}
    )

add_executable(raycasting 
                ${RAYCASTING_INCLUDE_FILES}
                Vector3d/Vector3d.cpp
                matrix/matrix.cpp 
                shapes/shape.cpp 
                shapes/plane/plane.cpp 
                shapes/sphere/sphere.cpp 
                shapes/cylinder/cylinder.cpp 
                shapes/cone/cone.cpp 
                shapes/mesh/mesh.cpp
                shapes/complex/complex_object.cpp 
                scene/scene.cpp 
                canvas/canvas.cpp
                light/light.cpp
                light/point/point_light.cpp
                light/ambient/ambient.cpp
                light/directional/directional.cpp
                light/spot/spot.cpp
                traceray/traceray.cpp 
                main.cpp)

target_link_libraries( 
    raycasting 
    Eigen3::Eigen
    # ${OpenCV_LIB_DIRS}/libopencv_calib3d341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_core341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_dnn341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_features2d341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_flann341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_highgui341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_imgcodecs341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_imgproc341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_ml341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_objdetect341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_photo341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_shape341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_stitching341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_superres341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_video341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_videoio341.dll.a
    # ${OpenCV_LIB_DIRS}/libopencv_videostab341.dll.a
    # ${SDL_MAIN_LIBRARY}
    # ${SDL2_LIBRARIES}
    ${SDL2_LIBRARIES}
    #-L/opt/local/x86_64-w64-mingw32/lib -lSDL2main -lSDL2
    # SDL2::Main
    )

add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties( raycasting PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/" )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
