#include <iostream>

template <typename T>
struct Light {
    Light(const T&& actual) : actual{actual} {}
	inline void work() { actual.work();}

	private:
        T actual;
};


struct PointLight {
    PointLight() = default;
    inline void work() {/* std::cout << "PointLight!\n";*/}
};

struct AmbientLight {
    AmbientLight() = default;

    inline void work() { /*std::cout << "AmbientLight!\n";*/ }
};