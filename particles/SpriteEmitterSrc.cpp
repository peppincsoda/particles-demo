#include "SpriteEmitterSrc.h"
#include "SpriteEmitterType.h"

#include "MathScriptProperty.h"

#include "mathscript/MathScript.h"
#include "gfx/Texture2D.h"
#include "core/Logger.h"

namespace particles {

    static void CompileProperty(const char* name, mathscript::Program& target, const std::string& src);

    SpriteEmitterSrc::SpriteEmitterSrc()
        : frequency_(30)
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

    std::vector<std::unique_ptr<core::PropertyInterface>> SpriteEmitterSrc::Properties()
    {
        std::vector<std::unique_ptr<core::PropertyInterface>> r;

        #define ADD_PROPERTY(name) \
            r.push_back(std::make_unique<core::Property<decltype(name##_)>>(#name, name##_))

            ADD_PROPERTY(frequency);
            ADD_PROPERTY(count);
            ADD_PROPERTY(particle_life_time);
            ADD_PROPERTY(apply_emitter_transform);
            ADD_PROPERTY(use_velocity);

        #undef ADD_PROPERTY

            r.push_back(std::make_unique<core::Property<decltype(texture_file_),
                        core::PropertyType::ImagePath>>("texture_file", texture_file_));

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

    static void CompileProperty(const char* name, mathscript::Program& target, const std::string& src)
    {
        try {
            target = mathscript::Compile(src);
        } catch (mathscript::Exception& e) {
            LOG_WARNING("Cannot compile MathScript for '%s': %s", name, src.c_str());
            target = mathscript::Compile("1");
        }
    }

    std::unique_ptr<SpriteEmitterType> SpriteEmitterSrc::Build() const
    {
        auto r = std::make_unique<SpriteEmitterType>();

        #define COPY_PROPERTY(name) \
            r->name##_ = name##_

            COPY_PROPERTY(frequency);
            COPY_PROPERTY(count);
            COPY_PROPERTY(particle_life_time);
            COPY_PROPERTY(apply_emitter_transform);
            COPY_PROPERTY(use_velocity);

        #undef COPY_PROPERTY

            gfx::Texture2D::LoadOrDefault(texture_file_, r->texture_);

        #define COMPILE_PROPERTY(name) \
            CompileProperty(#name, r->name##_, name##_);

            COMPILE_PROPERTY(emitter_position_x);
            COMPILE_PROPERTY(emitter_position_y);
            COMPILE_PROPERTY(emitter_position_z);

            COMPILE_PROPERTY(emitter_rotation_x);
            COMPILE_PROPERTY(emitter_rotation_y);
            COMPILE_PROPERTY(emitter_rotation_z);

            COMPILE_PROPERTY(emitter_scale_x);
            COMPILE_PROPERTY(emitter_scale_y);
            COMPILE_PROPERTY(emitter_scale_z);

            COMPILE_PROPERTY(emitter_color_r);
            COMPILE_PROPERTY(emitter_color_g);
            COMPILE_PROPERTY(emitter_color_b);
            COMPILE_PROPERTY(emitter_color_a);

            COMPILE_PROPERTY(particle_position_x);
            COMPILE_PROPERTY(particle_position_y);
            COMPILE_PROPERTY(particle_position_z);

            COMPILE_PROPERTY(particle_velocity_x);
            COMPILE_PROPERTY(particle_velocity_y);
            COMPILE_PROPERTY(particle_velocity_z);

            COMPILE_PROPERTY(particle_acceleration_x);
            COMPILE_PROPERTY(particle_acceleration_y);
            COMPILE_PROPERTY(particle_acceleration_z);

            COMPILE_PROPERTY(particle_rotation_x);
            COMPILE_PROPERTY(particle_rotation_y);
            COMPILE_PROPERTY(particle_rotation_z);

            COMPILE_PROPERTY(particle_scale_x);
            COMPILE_PROPERTY(particle_scale_y);
            COMPILE_PROPERTY(particle_scale_z);

            COMPILE_PROPERTY(particle_color_r);
            COMPILE_PROPERTY(particle_color_g);
            COMPILE_PROPERTY(particle_color_b);
            COMPILE_PROPERTY(particle_color_a);

        #undef COMPILE_PROPERTY

        return r;
    }

}
