# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daniel/repos/Ray-Casting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/repos/Ray-Casting

# Include any dependencies generated for this target.
include CMakeFiles/raycasting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raycasting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raycasting.dir/flags.make

CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o: Vector3d/Vector3d.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o -c /home/daniel/repos/Ray-Casting/Vector3d/Vector3d.cpp

CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/Vector3d/Vector3d.cpp > CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.i

CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/Vector3d/Vector3d.cpp -o CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.s

CMakeFiles/raycasting.dir/matrix/matrix.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/matrix/matrix.cpp.o: matrix/matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raycasting.dir/matrix/matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/matrix/matrix.cpp.o -c /home/daniel/repos/Ray-Casting/matrix/matrix.cpp

CMakeFiles/raycasting.dir/matrix/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/matrix/matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/matrix/matrix.cpp > CMakeFiles/raycasting.dir/matrix/matrix.cpp.i

CMakeFiles/raycasting.dir/matrix/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/matrix/matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/matrix/matrix.cpp -o CMakeFiles/raycasting.dir/matrix/matrix.cpp.s

CMakeFiles/raycasting.dir/shapes/shape.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/shape.cpp.o: shapes/shape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/raycasting.dir/shapes/shape.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/shape.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/shape.cpp

CMakeFiles/raycasting.dir/shapes/shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/shape.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/shape.cpp > CMakeFiles/raycasting.dir/shapes/shape.cpp.i

CMakeFiles/raycasting.dir/shapes/shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/shape.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/shape.cpp -o CMakeFiles/raycasting.dir/shapes/shape.cpp.s

CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o: shapes/plane/plane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/plane/plane.cpp

CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/plane/plane.cpp > CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.i

CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/plane/plane.cpp -o CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.s

CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o: shapes/sphere/sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/sphere/sphere.cpp

CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/sphere/sphere.cpp > CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.i

CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/sphere/sphere.cpp -o CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.s

CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o: shapes/cylinder/cylinder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/cylinder/cylinder.cpp

CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/cylinder/cylinder.cpp > CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.i

CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/cylinder/cylinder.cpp -o CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.s

CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o: shapes/cone/cone.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/cone/cone.cpp

CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/cone/cone.cpp > CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.i

CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/cone/cone.cpp -o CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.s

CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o: shapes/mesh/mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o -c /home/daniel/repos/Ray-Casting/shapes/mesh/mesh.cpp

CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/shapes/mesh/mesh.cpp > CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.i

CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/shapes/mesh/mesh.cpp -o CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.s

CMakeFiles/raycasting.dir/scene/scene.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/scene/scene.cpp.o: scene/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/raycasting.dir/scene/scene.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/scene/scene.cpp.o -c /home/daniel/repos/Ray-Casting/scene/scene.cpp

CMakeFiles/raycasting.dir/scene/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/scene/scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/scene/scene.cpp > CMakeFiles/raycasting.dir/scene/scene.cpp.i

CMakeFiles/raycasting.dir/scene/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/scene/scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/scene/scene.cpp -o CMakeFiles/raycasting.dir/scene/scene.cpp.s

CMakeFiles/raycasting.dir/canvas/canvas.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/canvas/canvas.cpp.o: canvas/canvas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/raycasting.dir/canvas/canvas.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/canvas/canvas.cpp.o -c /home/daniel/repos/Ray-Casting/canvas/canvas.cpp

CMakeFiles/raycasting.dir/canvas/canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/canvas/canvas.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/canvas/canvas.cpp > CMakeFiles/raycasting.dir/canvas/canvas.cpp.i

CMakeFiles/raycasting.dir/canvas/canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/canvas/canvas.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/canvas/canvas.cpp -o CMakeFiles/raycasting.dir/canvas/canvas.cpp.s

CMakeFiles/raycasting.dir/light/light.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/light/light.cpp.o: light/light.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/raycasting.dir/light/light.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/light/light.cpp.o -c /home/daniel/repos/Ray-Casting/light/light.cpp

CMakeFiles/raycasting.dir/light/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/light/light.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/light/light.cpp > CMakeFiles/raycasting.dir/light/light.cpp.i

CMakeFiles/raycasting.dir/light/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/light/light.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/light/light.cpp -o CMakeFiles/raycasting.dir/light/light.cpp.s

CMakeFiles/raycasting.dir/light/point/point_light.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/light/point/point_light.cpp.o: light/point/point_light.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/raycasting.dir/light/point/point_light.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/light/point/point_light.cpp.o -c /home/daniel/repos/Ray-Casting/light/point/point_light.cpp

CMakeFiles/raycasting.dir/light/point/point_light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/light/point/point_light.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/light/point/point_light.cpp > CMakeFiles/raycasting.dir/light/point/point_light.cpp.i

CMakeFiles/raycasting.dir/light/point/point_light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/light/point/point_light.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/light/point/point_light.cpp -o CMakeFiles/raycasting.dir/light/point/point_light.cpp.s

CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o: light/ambient/ambient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o -c /home/daniel/repos/Ray-Casting/light/ambient/ambient.cpp

CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/light/ambient/ambient.cpp > CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.i

CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/light/ambient/ambient.cpp -o CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.s

CMakeFiles/raycasting.dir/light/directional/directional.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/light/directional/directional.cpp.o: light/directional/directional.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/raycasting.dir/light/directional/directional.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/light/directional/directional.cpp.o -c /home/daniel/repos/Ray-Casting/light/directional/directional.cpp

CMakeFiles/raycasting.dir/light/directional/directional.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/light/directional/directional.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/light/directional/directional.cpp > CMakeFiles/raycasting.dir/light/directional/directional.cpp.i

CMakeFiles/raycasting.dir/light/directional/directional.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/light/directional/directional.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/light/directional/directional.cpp -o CMakeFiles/raycasting.dir/light/directional/directional.cpp.s

CMakeFiles/raycasting.dir/light/spot/spot.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/light/spot/spot.cpp.o: light/spot/spot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/raycasting.dir/light/spot/spot.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/light/spot/spot.cpp.o -c /home/daniel/repos/Ray-Casting/light/spot/spot.cpp

CMakeFiles/raycasting.dir/light/spot/spot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/light/spot/spot.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/light/spot/spot.cpp > CMakeFiles/raycasting.dir/light/spot/spot.cpp.i

CMakeFiles/raycasting.dir/light/spot/spot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/light/spot/spot.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/light/spot/spot.cpp -o CMakeFiles/raycasting.dir/light/spot/spot.cpp.s

CMakeFiles/raycasting.dir/traceray/traceray.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/traceray/traceray.cpp.o: traceray/traceray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/raycasting.dir/traceray/traceray.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/traceray/traceray.cpp.o -c /home/daniel/repos/Ray-Casting/traceray/traceray.cpp

CMakeFiles/raycasting.dir/traceray/traceray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/traceray/traceray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/traceray/traceray.cpp > CMakeFiles/raycasting.dir/traceray/traceray.cpp.i

CMakeFiles/raycasting.dir/traceray/traceray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/traceray/traceray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/traceray/traceray.cpp -o CMakeFiles/raycasting.dir/traceray/traceray.cpp.s

CMakeFiles/raycasting.dir/main.cpp.o: CMakeFiles/raycasting.dir/flags.make
CMakeFiles/raycasting.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/raycasting.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raycasting.dir/main.cpp.o -c /home/daniel/repos/Ray-Casting/main.cpp

CMakeFiles/raycasting.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raycasting.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/repos/Ray-Casting/main.cpp > CMakeFiles/raycasting.dir/main.cpp.i

CMakeFiles/raycasting.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raycasting.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/repos/Ray-Casting/main.cpp -o CMakeFiles/raycasting.dir/main.cpp.s

# Object files for target raycasting
raycasting_OBJECTS = \
"CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o" \
"CMakeFiles/raycasting.dir/matrix/matrix.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/shape.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o" \
"CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o" \
"CMakeFiles/raycasting.dir/scene/scene.cpp.o" \
"CMakeFiles/raycasting.dir/canvas/canvas.cpp.o" \
"CMakeFiles/raycasting.dir/light/light.cpp.o" \
"CMakeFiles/raycasting.dir/light/point/point_light.cpp.o" \
"CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o" \
"CMakeFiles/raycasting.dir/light/directional/directional.cpp.o" \
"CMakeFiles/raycasting.dir/light/spot/spot.cpp.o" \
"CMakeFiles/raycasting.dir/traceray/traceray.cpp.o" \
"CMakeFiles/raycasting.dir/main.cpp.o"

# External object files for target raycasting
raycasting_EXTERNAL_OBJECTS =

raycasting: CMakeFiles/raycasting.dir/Vector3d/Vector3d.cpp.o
raycasting: CMakeFiles/raycasting.dir/matrix/matrix.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/shape.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/plane/plane.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/sphere/sphere.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/cylinder/cylinder.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/cone/cone.cpp.o
raycasting: CMakeFiles/raycasting.dir/shapes/mesh/mesh.cpp.o
raycasting: CMakeFiles/raycasting.dir/scene/scene.cpp.o
raycasting: CMakeFiles/raycasting.dir/canvas/canvas.cpp.o
raycasting: CMakeFiles/raycasting.dir/light/light.cpp.o
raycasting: CMakeFiles/raycasting.dir/light/point/point_light.cpp.o
raycasting: CMakeFiles/raycasting.dir/light/ambient/ambient.cpp.o
raycasting: CMakeFiles/raycasting.dir/light/directional/directional.cpp.o
raycasting: CMakeFiles/raycasting.dir/light/spot/spot.cpp.o
raycasting: CMakeFiles/raycasting.dir/traceray/traceray.cpp.o
raycasting: CMakeFiles/raycasting.dir/main.cpp.o
raycasting: CMakeFiles/raycasting.dir/build.make
raycasting: CMakeFiles/raycasting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniel/repos/Ray-Casting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable raycasting"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raycasting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raycasting.dir/build: raycasting

.PHONY : CMakeFiles/raycasting.dir/build

CMakeFiles/raycasting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raycasting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raycasting.dir/clean

CMakeFiles/raycasting.dir/depend:
	cd /home/daniel/repos/Ray-Casting && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/repos/Ray-Casting /home/daniel/repos/Ray-Casting /home/daniel/repos/Ray-Casting /home/daniel/repos/Ray-Casting /home/daniel/repos/Ray-Casting/CMakeFiles/raycasting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/raycasting.dir/depend
