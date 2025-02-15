cmake_minimum_required(VERSION 3.25)
project(raycasting VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "/O3 /Wall")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(SDL2 REQUIRED)

message("${SDL2_LIBRARIES}")
message("${EIGEN3_INCLUDE_DIR}")

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${CMAKE_CURRENT_LIST_DIR}
  # ${OpenCV_INCLUDE_DIRS}
)

add_executable(raycasting
  main.cpp
)

target_link_libraries(
  raycasting
  Eigen3::Eigen
  ${SDL2_LIBRARIES}
)

add_definitions(-DSDL_MAIN_HANDLED)

set_target_properties(raycasting PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

  # matrix/matrix.cpp
  # shapes/shape.cpp
  # shapes/plane/plane.cpp
  # shapes/sphere/sphere.cpp
  # shapes/cylinder/cylinder.cpp
  # shapes/cone/cone.cpp
  # shapes/mesh/mesh.cpp
  # shapes/complex/complex_object.cpp
  # scene/scene.cpp
  # canvas/canvas.cpp
  # light/light.cpp
  # light/point/point_light.cpp
  # light/ambient/ambient.cpp
  # light/directional/directional.cpp
  # light/spot/spot.cpp
  # traceray/traceray.cpp