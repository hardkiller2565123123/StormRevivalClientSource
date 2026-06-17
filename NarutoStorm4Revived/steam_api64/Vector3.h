#pragma once
#include <cmath>

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
    {
        return Vector3(
            a.x + t * (b.x - a.x),
            a.y + t * (b.y - a.y),
            a.z + t * (b.z - a.z)
        );
    }

    Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
    Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
    Vector3 operator * (float m) const { return Vector3(x * m, y * m, z * m); }
    Vector3 operator / (float m) const { return Vector3(x / m, y / m, z / m); }

    bool operator == (const Vector3& b) const { return x == b.x && y == b.y && z == b.z; }
    bool operator != (const Vector3& b) const { return !(*this == b); }

    //  
    float Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    //  ,   
    float Magnitude() const
    {
        return Length();
    }

    //        (0,0,0)
    Vector3 Normalize() const
    {
        float m = Length();
        if (m <= 1e-6f) return Vector3(0.0f, 0.0f, 0.0f);
        return (*this) / m;
    }

    static float Distance(const Vector3& a, const Vector3& b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        float dz = a.z - b.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

class Vector2
{
public:
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a, float b) : x(a), y(b) {}
};

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
