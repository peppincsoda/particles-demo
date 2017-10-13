#ifndef SPRITEEMITTERTYPE_H
#define SPRITEEMITTERTYPE_H

#include "mathscript/Program.h"

#include <memory>

namespace gfx {
    class Texture2D;
}

namespace particles {

    class SpriteEmitterSrc;

    class SpriteEmitterType
    {
    public:
        SpriteEmitterType();
        ~SpriteEmitterType();

        SpriteEmitterType(const SpriteEmitterType&) = default;
        SpriteEmitterType& operator=(const SpriteEmitterType&) = default;

        SpriteEmitterType(SpriteEmitterType&&) = default;
        SpriteEmitterType& operator=(SpriteEmitterType&&) = default;

        friend class SpriteEmitterSrc;
        friend class SpriteEmitter;

        gfx::Texture2D* texture();

    private:
        float frequency_;
        int   count_;

        int   particle_life_time_;

        bool  apply_emitter_transform_;
        bool  use_velocity_;

        std::unique_ptr<gfx::Texture2D> texture_;

        mathscript::Program emitter_position_x_;
        mathscript::Program emitter_position_y_;
        mathscript::Program emitter_position_z_;

        mathscript::Program emitter_rotation_x_;
        mathscript::Program emitter_rotation_y_;
        mathscript::Program emitter_rotation_z_;

        mathscript::Program emitter_scale_x_;
        mathscript::Program emitter_scale_y_;
        mathscript::Program emitter_scale_z_;

        mathscript::Program emitter_color_r_;
        mathscript::Program emitter_color_g_;
        mathscript::Program emitter_color_b_;
        mathscript::Program emitter_color_a_;

        mathscript::Program particle_position_x_;
        mathscript::Program particle_position_y_;
        mathscript::Program particle_position_z_;

        mathscript::Program particle_velocity_x_;
        mathscript::Program particle_velocity_y_;
        mathscript::Program particle_velocity_z_;

        mathscript::Program particle_acceleration_x_;
        mathscript::Program particle_acceleration_y_;
        mathscript::Program particle_acceleration_z_;

        mathscript::Program particle_rotation_x_;
        mathscript::Program particle_rotation_y_;
        mathscript::Program particle_rotation_z_;

        mathscript::Program particle_scale_x_;
        mathscript::Program particle_scale_y_;
        mathscript::Program particle_scale_z_;

        mathscript::Program particle_color_r_;
        mathscript::Program particle_color_g_;
        mathscript::Program particle_color_b_;
        mathscript::Program particle_color_a_;
    };

}

#endif // SPRITEEMITTERTYPE_H
