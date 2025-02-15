#ifndef OBJECT_TYPES
#define OBJECT_TYPES

enum ObjectTypes {
    SPHERE,
    PLANE,
};

template <typename T>
struct Object {
    Object(const T&& actual) : actual {actual} {}

    inline double intersect(const Vector3d& p0, const Vector3d& dr) const {
        return actual.intersect(p0, dr);
    }
    inline Vector3d normal(const Vector3d& pi) const {
        return actual.normal(pi);
    }
    inline ObjectTypes type() const { return actual.type(); }

    inline const Vector3d& color() const { return actual.color(); }

   private:
    T actual;
};

#endif