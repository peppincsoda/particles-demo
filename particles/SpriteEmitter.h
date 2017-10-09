#ifndef SPRITEEMITTER_H
#define SPRITEEMITTER_H

#include "gfx/GfxMath.h"
#include "ScriptScope.h"

#include <cstdint>
#include <list>

namespace gfx {
    class SpriteMesh;
}

namespace particles {

    class SpriteEmitterType;

    class SpriteEmitter
    {
    public:
        SpriteEmitter(const SpriteEmitterType& type, uint32_t random_seed);

        void Update(int64_t current_time, int time_delta);
        void WriteMesh(gfx::SpriteMesh& mesh);

    private:
        const SpriteEmitterType& type_;
        int age_;
        uint32_t random_seed_;

        struct Particle
        {
            int      life_time;
            int      time_remaining;
            uint32_t random_seed;

            gfx::Vector3 position;               //  without emitter transform
            gfx::Vector3 transformed_position;   //  with emitter transform
            gfx::Vector3 velocity;
            gfx::Vector3 rotation;
            gfx::Vector2 size;
            gfx::Color   color;
        };

        gfx::Vector3 position_;
        gfx::Vector3 rotation_;
        gfx::Vector3 scale_;
        gfx::Color   color_;

        int     unprocessed_time_;

        float   frequency_;
        int     count_;

        int     particle_life_time_;

        std::list<Particle>   particles_;

        ScriptScope scope_;
    };

}

#endif // SPRITEEMITTER_H
