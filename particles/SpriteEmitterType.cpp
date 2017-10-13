#include "SpriteEmitterType.h"

#include "gfx/Texture2D.h"

namespace particles {

    SpriteEmitterType::SpriteEmitterType()
        : frequency_(0)
        , count_(0)
        , particle_life_time_(0)
        , apply_emitter_transform_(false)
        , use_velocity_(false)
        , texture_()

        , emitter_position_x_()
        , emitter_position_y_()
        , emitter_position_z_()

        , emitter_rotation_x_()
        , emitter_rotation_y_()
        , emitter_rotation_z_()

        , emitter_scale_x_()
        , emitter_scale_y_()
        , emitter_scale_z_()

        , emitter_color_r_()
        , emitter_color_g_()
        , emitter_color_b_()
        , emitter_color_a_()

        , particle_position_x_()
        , particle_position_y_()
        , particle_position_z_()

        , particle_velocity_x_()
        , particle_velocity_y_()
        , particle_velocity_z_()

        , particle_acceleration_x_()
        , particle_acceleration_y_()
        , particle_acceleration_z_()

        , particle_rotation_x_()
        , particle_rotation_y_()
        , particle_rotation_z_()

        , particle_scale_x_()
        , particle_scale_y_()
        , particle_scale_z_()

        , particle_color_r_()
        , particle_color_g_()
        , particle_color_b_()
        , particle_color_a_()
    {
    }

    SpriteEmitterType::~SpriteEmitterType()
    {

    }

    gfx::Texture2D* SpriteEmitterType::texture()
    {
        return texture_.get();
    }
}
