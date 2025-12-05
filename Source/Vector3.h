#pragma once
#include <cmath>
#include <iostream>

struct vec3 {
    float x, y, z;

    // -------------------------
    // Constructors
    // -------------------------
    vec3() : x(0), y(0), z(0) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Unary minus
    vec3 operator-() const { return vec3(-x, -y, -z); }

    // Access
    float operator[](int i) const { return (&x)[i]; }
    float& operator[](int i) { return (&x)[i]; }

    // -------------------------
    // Vector arithmetic
    // -------------------------
    vec3& operator+=(const vec3& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    vec3& operator*=(float t) {
        x *= t; y *= t; z *= t;
        return *this;
    }

    vec3& operator/=(float t) {
        return *this *= 1.0f / t;
    }


    vec3 operator/(float t) const {
        if (fabs(t) < 1e-6f)
            return vec3(0, 0, 0);
        return vec3(x / t, y / t, z / t);
    }

    // -------------------------
    // Length
    // -------------------------
    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float LengthSquared() const {
        return x * x + y * y + z * z;
    }

    // -------------------------
    // Normalized
    // -------------------------
    vec3 Normalized() const {
        float len = Length();
        if (len < 1e-6f)
            return vec3(0.0f, 0.0f, 0.0f);

        return *this / len;
    }
};

// -------------------------
// Operator Overloads
// -------------------------

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t * v.x, t * v.y, t * v.z);
}

inline vec3 operator*(const vec3& v, float t) {
    return vec3(v.x * t, v.y * t, v.z * t);
}


// -------------------------
// Dot & Cross
// -------------------------

inline float Dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 Cross(const vec3& a, const vec3& b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}