all:
	g++ -I src/include -L src/lib -o main Vector3d/Vector3d.h Vector3d/Vector3d.cpp shapes/shape.h shapes/shape.cpp shapes/plane/plane.h shapes/plane/plane.cpp shapes/sphere/sphere.h shapes/sphere/sphere.cpp shapes/cylinder/cylinder.h shapes/cylinder/cylinder.cpp shapes/cone/cone.h shapes/cone/cone.cpp shapes/mesh/mesh.h shapes/mesh/mesh.cpp scene/scene.h scene/scene.cpp canvas/canvas.h canvas/canvas.cpp traceray/traceray.h traceray/traceray.cpp main.cpp -lmingw32 -lSDL2main -lSDL2