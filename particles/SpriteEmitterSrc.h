#ifndef SPRITEEMITTERSRC_H
#define SPRITEEMITTERSRC_H


#include "Properties.h"


namespace particles {

    class SpriteEmitterType;

    class SpriteEmitterSrc : public HasProperties
    {
    public:
        SpriteEmitterSrc();

        SpriteEmitterSrc(const SpriteEmitterSrc&) = default;
        SpriteEmitterSrc& operator=(const SpriteEmitterSrc&) = default;

        SpriteEmitterSrc(SpriteEmitterSrc&&) = default;
        SpriteEmitterSrc& operator=(SpriteEmitterSrc&&) = default;

        std::vector<std::unique_ptr<PropertyInterface>> Properties() override;

        std::unique_ptr<SpriteEmitterType> Build() const;

    private:
        float frequency_;
        int   count_;

        int   particle_life_time_;

        bool  apply_emitter_transform_;
        bool  use_velocity_;

        std::string texture_file_;

        std::string emitter_position_x_;
        std::string emitter_position_y_;
        std::string emitter_position_z_;

        std::string emitter_rotation_x_;
        std::string emitter_rotation_y_;
        std::string emitter_rotation_z_;

        std::string emitter_scale_x_;
        std::string emitter_scale_y_;
        std::string emitter_scale_z_;

        std::string emitter_color_r_;
        std::string emitter_color_g_;
        std::string emitter_color_b_;
        std::string emitter_color_a_;

        std::string particle_position_x_;
        std::string particle_position_y_;
        std::string particle_position_z_;

        std::string particle_velocity_x_;
        std::string particle_velocity_y_;
        std::string particle_velocity_z_;

        std::string particle_acceleration_x_;
        std::string particle_acceleration_y_;
        std::string particle_acceleration_z_;

        std::string particle_rotation_x_;
        std::string particle_rotation_y_;
        std::string particle_rotation_z_;

        std::string particle_scale_x_;
        std::string particle_scale_y_;
        std::string particle_scale_z_;

        std::string particle_color_r_;
        std::string particle_color_g_;
        std::string particle_color_b_;
        std::string particle_color_a_;
    };
}


#endif // SPRITEEMITTERSRC_H
