#ifndef CAMERA_H
#define CAMERA_H

#include "GfxMath.h"

namespace gfx {

    class CameraLens
    {
    public:
        CameraLens();

        void set_screen_width(float screen_width);
        void set_screen_height(float screen_height);

        Matrix4x4 GetProj() const;

    private:
        float   screen_width_;
        float   screen_height_;
        float   vertical_fov_;
        float   near_z_;
        float   far_z_;
    };

    class Camera
    {
    public:
        Camera();

        void AddEyeDistance(float distance);
        void AddHorizontalAngle(float angle);
        void AddVerticalAngle(float angle);

        Matrix4x4 GetView() const;

        Vector3 eye_position() const;
        float eye_distance() const;
        float horizontal_angle() const;
        float vertical_angle() const;

        CameraLens& lens();

    private:
        Vector3 lookat_;
        float   eye_distance_;
        float   horizontal_angle_;
        float   vertical_angle_;

        CameraLens  lens_;
    };


}

#endif // CAMERA_H
