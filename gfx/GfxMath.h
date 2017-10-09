#ifndef GFXMATH_H
#define GFXMATH_H

#include <cmath>
#include <cstdint>

namespace gfx {

    struct Vector4;

    struct Vector2
    {
        float x;
        float y;

        Vector2()
        {
        }

        Vector2(float x_, float y_)
            : x(x_)
            , y(y_)
        {
        }
    };

    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3()
        {
        }

        Vector3(float x_, float y_, float z_)
            : x(x_)
            , y(y_)
            , z(z_)
        {
        }

        explicit Vector3(const Vector4& v); //  drops v.w
    };

    inline static const Vector3 operator-(const Vector3& v)
    {
        return Vector3(-v.x, -v.y, -v.z);
    }

    inline static const Vector3 operator+(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    inline static const Vector3 operator-(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    inline static const Vector3 operator*(const Vector3& v, float scalar)
    {
        return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    inline static float Dot(const Vector3& v1, const Vector3& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    inline static const Vector3 Cross(const Vector3& v1, const Vector3& v2)
    {
        return Vector3( v1.y * v2.z - v2.y * v1.z
                      , v2.x * v1.z - v1.x * v2.z
                      , v1.x * v2.y - v2.x * v1.y );
    }

    inline static const Vector3 Normalize(const Vector3& v)
    {
        const auto length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);

        return Vector3(v.x / length, v.y / length, v.z / length);
    }

    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;

        Vector4()
        {
        }

        Vector4(float x_, float y_, float z_, float w_)
            : x(x_)
            , y(y_)
            , z(z_)
            , w(w_)
        {
        }

        Vector4(const Vector3& v)
            : x(v.x)
            , y(v.y)
            , z(v.z)
            , w(1)
        {
        }
    };

    inline Vector3::Vector3(const Vector4 &v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
    {
    }

    struct Matrix4x4
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;

        Matrix4x4()
        {
        }

        Matrix4x4( float m00_, float m01_, float m02_, float m03_
                 , float m10_, float m11_, float m12_, float m13_
                 , float m20_, float m21_, float m22_, float m23_
                 , float m30_, float m31_, float m32_, float m33_)
            : m00(m00_), m01(m01_), m02(m02_), m03(m03_)
            , m10(m10_), m11(m11_), m12(m12_), m13(m13_)
            , m20(m20_), m21(m21_), m22(m22_), m23(m23_)
            , m30(m30_), m31(m31_), m32(m32_), m33(m33_)
        {
        }

        friend const Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right)
        {
            return Matrix4x4( left.m00 * right.m00 + left.m01 * right.m10 + left.m02 * right.m20 + left.m03 * right.m30
                            , left.m00 * right.m01 + left.m01 * right.m11 + left.m02 * right.m21 + left.m03 * right.m31
                            , left.m00 * right.m02 + left.m01 * right.m12 + left.m02 * right.m22 + left.m03 * right.m32
                            , left.m00 * right.m03 + left.m01 * right.m13 + left.m02 * right.m23 + left.m03 * right.m33
                            , left.m10 * right.m00 + left.m11 * right.m10 + left.m12 * right.m20 + left.m13 * right.m30
                            , left.m10 * right.m01 + left.m11 * right.m11 + left.m12 * right.m21 + left.m13 * right.m31
                            , left.m10 * right.m02 + left.m11 * right.m12 + left.m12 * right.m22 + left.m13 * right.m32
                            , left.m10 * right.m03 + left.m11 * right.m13 + left.m12 * right.m23 + left.m13 * right.m33
                            , left.m20 * right.m00 + left.m21 * right.m10 + left.m22 * right.m20 + left.m23 * right.m30
                            , left.m20 * right.m01 + left.m21 * right.m11 + left.m22 * right.m21 + left.m23 * right.m31
                            , left.m20 * right.m02 + left.m21 * right.m12 + left.m22 * right.m22 + left.m23 * right.m32
                            , left.m20 * right.m03 + left.m21 * right.m13 + left.m22 * right.m23 + left.m23 * right.m33
                            , left.m30 * right.m00 + left.m31 * right.m10 + left.m32 * right.m20 + left.m33 * right.m30
                            , left.m30 * right.m01 + left.m31 * right.m11 + left.m32 * right.m21 + left.m33 * right.m31
                            , left.m30 * right.m02 + left.m31 * right.m12 + left.m32 * right.m22 + left.m33 * right.m32
                            , left.m30 * right.m03 + left.m31 * right.m13 + left.m32 * right.m23 + left.m33 * right.m33 );
        }

        static const Matrix4x4 Scale(float scale_x, float scale_y, float scale_z)
        {
            return Matrix4x4( scale_x,       0,       0, 0
                            ,       0, scale_y,       0, 0
                            ,       0,       0, scale_z, 0
                            ,       0,       0,       0, 1 );
        }

        static const Matrix4x4 Scale(const Vector3& scale)
        {
            return Scale(scale.x, scale.y, scale.z);
        }

        static const Matrix4x4 Translation(float x, float y, float z)
        {
            return Matrix4x4( 1, 0, 0, x
                            , 0, 1, 0, y
                            , 0, 0, 1, z
                            , 0, 0, 0, 1 );
        }

        static const Matrix4x4 Translation(const Vector3& translation)
        {
            return Translation(translation.x, translation.y, translation.z);
        }

        static const Matrix4x4 RotationX(float angle)
        {
            const auto s = sinf(angle);
            const auto c = cosf(angle);

            return Matrix4x4( 1, 0,  0, 0
                            , 0, c, -s, 0
                            , 0, s,  c, 0
                            , 0, 0,  0, 1 );
        }

        static const Matrix4x4 RotationY(float angle)
        {
            const auto s = sinf(angle);
            const auto c = cosf(angle);

            return Matrix4x4(  c, 0, s, 0
                            ,  0, 1, 0, 0
                            , -s, 0, c, 0
                            ,  0, 0, 0, 1 );
        }

        static const Matrix4x4 RotationZ(float angle)
        {
            const auto s = sinf(angle);
            const auto c = cosf(angle);

            return Matrix4x4( c, -s, 0, 0
                            , s,  c, 0, 0
                            , 0,  0, 1, 0
                            , 0,  0, 0, 1 );
        }

        static const Matrix4x4 Rotation(float angle_x, float angle_y, float angle_z)
        {
            return RotationZ(angle_z) * RotationY(angle_y) * RotationX(angle_x);
        }

        static const Matrix4x4 Rotation(const Vector3& rotation)
        {
            return Rotation(rotation.x, rotation.y, rotation.z);
        }

        static const Matrix4x4 SRT(const Vector3& scale, const Vector3& rotation, const Vector3& translation)
        {
            return Translation(translation) * Rotation(rotation) * Scale(scale);
        }

        static const Matrix4x4 PerspectiveProj(float vertical_fov, float aspect_ratio, float near_z, float far_z)
        {
            const auto tan_half_fov = tanf(vertical_fov / 2);

            Matrix4x4 m;
            m.m00 = 1 / (aspect_ratio * tan_half_fov);
            m.m01 = 0;
            m.m02 = 0;
            m.m03 = 0;

            m.m10 = 0;
            m.m11 = 1 / tan_half_fov;
            m.m12 = 0;
            m.m13 = 0;

            m.m20 = 0;
            m.m21 = 0;
            m.m22 = (-near_z - far_z) / (near_z - far_z);
            m.m23 = 2 * far_z * near_z / (near_z - far_z);

            m.m30 = 0;
            m.m31 = 0;
            m.m32 = 1;
            m.m33 = 0;

            return m;
        }

        static const Matrix4x4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
        {
            const Vector3 n(Normalize(at - eye)); // right-handed -> left-handed
            const Vector3 u(Normalize(Cross(n, up)));
            const Vector3 v(Cross(u, n));

            return Matrix4x4(  u.x,  u.y,  u.z, -Dot(u, eye)
                            ,  v.x,  v.y,  v.z, -Dot(v, eye)
                            ,  n.x,  n.y,  n.z, -Dot(n, eye)
                            ,    0,    0,    0,            1 );
        }

        static const Matrix4x4 Zero;
        static const Matrix4x4 Identity;
    };

    inline static const Vector4 operator*(const Matrix4x4& m, const Vector4& v)
    {
        return Vector4( m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w
                      , m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w
                      , m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w
                      , m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w );
    }

    template<class T>
    inline static T Min(T v1, T v2)
    {
        return v1 < v2 ? v1 : v2;
    }

    template<class T>
    inline static T Max(T v1, T v2)
    {
        return v1 < v2 ? v2 : v1;
    }

    template<class T>
    inline static T Clamp(T value, T minimum, T maximum)
    {
        return Min(Max(value, minimum), maximum);
    }

    struct Color
    {
        float r;
        float g;
        float b;
        float a;

        Color()
        {
        }

        Color(float r_, float g_, float b_, float a_)
            : r(r_)
            , g(g_)
            , b(b_)
            , a(a_)
        {
        }

        uint32_t ToRGBA() const
        {
            return (static_cast<uint8_t>(r * 255) <<  0)
                 | (static_cast<uint8_t>(g * 255) <<  8)
                 | (static_cast<uint8_t>(b * 255) << 16)
                 | (static_cast<uint8_t>(a * 255) << 24);
        }
    };

    inline static const Color operator*(const Color& left, const Color& right)
    {
        return Color( left.r * right.r
                    , left.g * right.g
                    , left.b * right.b
                    , left.a * right.a );
    }
}

#endif // GFXMATH_H
