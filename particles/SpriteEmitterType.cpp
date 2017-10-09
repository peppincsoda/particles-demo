#include "SpriteEmitterType.h"
#include "MathScriptProperty.h"

namespace particles {

    SpriteEmitterType::SpriteEmitterType()
        : frequency_(30.0f)
        , count_(1)
        , particle_life_time_(3000)
        , apply_emitter_transform_(false)
        , use_velocity_(false)
        , texture_file_("/textures/white-ink-spot-md.png")

        , emitter_position_x_("0")
        , emitter_position_y_("0")
        , emitter_position_z_("0")

        , emitter_rotation_x_("0")
        , emitter_rotation_y_("0")
        , emitter_rotation_z_("0")

        , emitter_scale_x_("1")
        , emitter_scale_y_("1")
        , emitter_scale_z_("1")

        , emitter_color_r_("1")
        , emitter_color_g_("1")
        , emitter_color_b_("1")
        , emitter_color_a_("1")

        , particle_position_x_("rand1()")
        , particle_position_y_("rand1()")
        , particle_position_z_("rand1()")

        , particle_velocity_x_("1")
        , particle_velocity_y_("1")
        , particle_velocity_z_("rand() * 0.5")

        , particle_acceleration_x_("0")
        , particle_acceleration_y_("-1")
        , particle_acceleration_z_("0")

        , particle_rotation_x_("0")
        , particle_rotation_y_("0")
        , particle_rotation_z_("0")

        , particle_scale_x_("0.1")
        , particle_scale_y_("0.1")
        , particle_scale_z_("1")

        , particle_color_r_("rand1()")
        , particle_color_g_("rand1()")
        , particle_color_b_("rand1()")
        , particle_color_a_("1 - lifeline")
    {
    }

    std::vector<std::unique_ptr<PropertyInterface>> SpriteEmitterType::Properties()
    {
        std::vector<std::unique_ptr<PropertyInterface>> r;

        #define ADD_PROPERTY(name) \
            r.push_back(std::make_unique<Property<decltype(name##_)>>(#name, SpriteEmitterType::name##_))

            ADD_PROPERTY(frequency);
            ADD_PROPERTY(count);
            ADD_PROPERTY(particle_life_time);
            ADD_PROPERTY(apply_emitter_transform);
            ADD_PROPERTY(use_velocity);
            ADD_PROPERTY(texture_file);

        #undef ADD_PROPERTY

        #define ADD_PROPERTY(name) \
            r.push_back(std::make_unique<MathScriptProperty>(#name, name##_))

            ADD_PROPERTY(emitter_position_x);
            ADD_PROPERTY(emitter_position_y);
            ADD_PROPERTY(emitter_position_z);

            ADD_PROPERTY(emitter_rotation_x);
            ADD_PROPERTY(emitter_rotation_y);
            ADD_PROPERTY(emitter_rotation_z);

            ADD_PROPERTY(emitter_scale_x);
            ADD_PROPERTY(emitter_scale_y);
            ADD_PROPERTY(emitter_scale_z);

            ADD_PROPERTY(emitter_color_r);
            ADD_PROPERTY(emitter_color_g);
            ADD_PROPERTY(emitter_color_b);
            ADD_PROPERTY(emitter_color_a);

            ADD_PROPERTY(particle_position_x);
            ADD_PROPERTY(particle_position_y);
            ADD_PROPERTY(particle_position_z);

            ADD_PROPERTY(particle_velocity_x);
            ADD_PROPERTY(particle_velocity_y);
            ADD_PROPERTY(particle_velocity_z);

            ADD_PROPERTY(particle_acceleration_x);
            ADD_PROPERTY(particle_acceleration_y);
            ADD_PROPERTY(particle_acceleration_z);

            ADD_PROPERTY(particle_rotation_x);
            ADD_PROPERTY(particle_rotation_y);
            ADD_PROPERTY(particle_rotation_z);

            ADD_PROPERTY(particle_scale_x);
            ADD_PROPERTY(particle_scale_y);
            ADD_PROPERTY(particle_scale_z);

            ADD_PROPERTY(particle_color_r);
            ADD_PROPERTY(particle_color_g);
            ADD_PROPERTY(particle_color_b);
            ADD_PROPERTY(particle_color_a);

        #undef ADD_PROPERTY

        return r;
    }

}
