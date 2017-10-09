#ifndef SPRITEEMITTERTYPE_H
#define SPRITEEMITTERTYPE_H

#include "Properties.h"
#include "MathScriptProgram.h"

namespace particles {

    class SpriteEmitterType : public HasProperties
    {
    public:
        SpriteEmitterType();

        std::vector<std::unique_ptr<PropertyInterface>> Properties() override;

        friend class SpriteEmitter;

    private:
        float frequency_;
        int   count_;

        int   particle_life_time_;

        bool  apply_emitter_transform_;
        bool  use_velocity_;

        std::string texture_file_;

        MathScriptProgram emitter_position_x_;
        MathScriptProgram emitter_position_y_;
        MathScriptProgram emitter_position_z_;

        MathScriptProgram emitter_rotation_x_;
        MathScriptProgram emitter_rotation_y_;
        MathScriptProgram emitter_rotation_z_;

        MathScriptProgram emitter_scale_x_;
        MathScriptProgram emitter_scale_y_;
        MathScriptProgram emitter_scale_z_;

        MathScriptProgram emitter_color_r_;
        MathScriptProgram emitter_color_g_;
        MathScriptProgram emitter_color_b_;
        MathScriptProgram emitter_color_a_;

        MathScriptProgram particle_position_x_;
        MathScriptProgram particle_position_y_;
        MathScriptProgram particle_position_z_;

        MathScriptProgram particle_velocity_x_;
        MathScriptProgram particle_velocity_y_;
        MathScriptProgram particle_velocity_z_;

        MathScriptProgram particle_acceleration_x_;
        MathScriptProgram particle_acceleration_y_;
        MathScriptProgram particle_acceleration_z_;

        MathScriptProgram particle_rotation_x_;
        MathScriptProgram particle_rotation_y_;
        MathScriptProgram particle_rotation_z_;

        MathScriptProgram particle_scale_x_;
        MathScriptProgram particle_scale_y_;
        MathScriptProgram particle_scale_z_;

        MathScriptProgram particle_color_r_;
        MathScriptProgram particle_color_g_;
        MathScriptProgram particle_color_b_;
        MathScriptProgram particle_color_a_;
    };

}

#endif // SPRITEEMITTERTYPE_H
