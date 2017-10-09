#include "Camera.h"

namespace gfx {

    CameraLens::CameraLens()
        : screen_width_(800)
        , screen_height_(600)
        , vertical_fov_(M_PI_4)
        , near_z_(1)
        , far_z_(1000)
    {
    }

    void CameraLens::set_screen_width(float screen_width)
    {
        screen_width_ = screen_width;
    }

    void CameraLens::set_screen_height(float screen_height)
    {
        screen_height_ = screen_height;
    }

    Matrix4x4 CameraLens::GetProj() const
    {
        const float aspect_ratio = screen_width_ / screen_height_;
        return Matrix4x4::PerspectiveProj(vertical_fov_, aspect_ratio, near_z_, far_z_);
    }

    Camera::Camera()
        : lookat_(0, 0, 0)
        , eye_distance_(4)
        , horizontal_angle_(M_PI_4)
        , vertical_angle_(-M_PI / 6)
    {
    }

    void Camera::AddEyeDistance(float distance)
    {
        eye_distance_ = Clamp<decltype(eye_distance_)>(eye_distance_ + distance, 2, 20);
    }

    void Camera::AddHorizontalAngle(float angle)
    {
        horizontal_angle_ += angle;
        if (horizontal_angle_ < 0) {
            horizontal_angle_ = 2*M_PI + horizontal_angle_;
        } else if (horizontal_angle_ > 2*M_PI) {
            horizontal_angle_ -= 2*M_PI;
        }
    }

    void Camera::AddVerticalAngle(float angle)
    {
        vertical_angle_ = Clamp<decltype(vertical_angle_)>(vertical_angle_ + angle, -M_PI_2 + 0.001, M_PI_2 - 0.001);
    }

    Matrix4x4 Camera::GetView() const
    {
        return Matrix4x4::LookAt(eye_position(), lookat_, Vector3(0, 1, 0));
    }

    Vector3 Camera::eye_position() const
    {
        Vector3 eye( Matrix4x4::Translation(lookat_)
                   * Matrix4x4::RotationY(horizontal_angle_)
                   * Matrix4x4::RotationX(vertical_angle_)
                   * Vector3(0, 0, eye_distance_) );

        return eye;
    }

    float Camera::eye_distance() const
    {
        return eye_distance_;
    }

    float Camera::horizontal_angle() const
    {
        return horizontal_angle_;
    }

    float Camera::vertical_angle() const
    {
        return vertical_angle_;
    }

    CameraLens& Camera::lens()
    {
        return lens_;
    }

}
