# RayCasting Implementation using C++ and SDL

This project is an implementation of RayCasting in C++ using the SDL (Simple DirectMedia Layer) library. RayCasting is a rendering technique that serves as a simplified version of RayTracing, commonly used in computer graphics for 3D solid modeling and image rendering.

## About Ray Casting

Ray casting is the methodological basis for 3D CAD/CAM solid modeling and image rendering. It is essentially the same as ray tracing for computer graphics, where virtual light rays are "cast" or "traced" on their path from the focal point of a camera through each pixel in the camera sensor to determine what is visible along the ray in the 3D scene.

For more information about Ray Casting, you can refer to the [Wikipedia page](https://en.wikipedia.org/wiki/Ray_casting).

## Features

In this project, it is possible to create scenarios using RayCasting as the rendering method and benefit from the following features:

- Basic geometric objects: Cylinder, Cone, Sphere, Plane, and Meshes.
- Transformations of objects in space: Translation, Rotation, Scaling, and Shearing.
- Efficiency optimizations, such as clustering and backface culling (in the case of meshes).
- Addition of various types of light sources, such as Point, Ambient, Spot, and Directional lights.

## Requirements

Before executing the project, you need to have the following installed on your system:

- C++ compiler
- SDL (Simple DirectMedia Layer) library
