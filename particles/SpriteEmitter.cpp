#include "SpriteEmitter.h"
#include "SpriteEmitterType.h"
#include "Random.h"

#include "gfx/SpriteMesh.h"

#include <algorithm>

namespace particles {

    SpriteEmitter::SpriteEmitter(const SpriteEmitterType& type, uint32_t random_seed)
        : type_(type)
        , age_(0)
        , random_seed_(random_seed)
        , unprocessed_time_(0)
        , frequency_(type.frequency_)
        , count_(type.count_)
        , particle_life_time_(type.particle_life_time_)
    {
    }

    void SpriteEmitter::Update(int64_t, int time_delta)
    {
        age_ += time_delta;

        scope_.set_time(age_ / 1000.0);
        scope_.set_random_seed(random_seed_);
        scope_.set_lifeline(0);

        // Update emitter properties
        position_.x = type_.emitter_position_x_.Run(scope_);
        position_.y = type_.emitter_position_y_.Run(scope_);
        position_.z = type_.emitter_position_z_.Run(scope_);

        rotation_.x = type_.emitter_rotation_x_.Run(scope_);
        rotation_.y = type_.emitter_rotation_y_.Run(scope_);
        rotation_.z = type_.emitter_rotation_z_.Run(scope_);

        scale_.x = type_.emitter_scale_x_.Run(scope_);
        scale_.y = type_.emitter_scale_y_.Run(scope_);
        scale_.z = type_.emitter_scale_z_.Run(scope_);

        color_.r = type_.emitter_color_r_.Run(scope_);
        color_.g = type_.emitter_color_g_.Run(scope_);
        color_.b = type_.emitter_color_b_.Run(scope_);
        color_.a = type_.emitter_color_a_.Run(scope_);

        const gfx::Matrix4x4 emitter_transform(gfx::Matrix4x4::SRT(scale_, rotation_, position_));

        // Spawn new particles
        if (frequency_ != 0.0f) {
            const auto period = static_cast<int>(1000.0f / frequency_);

            unprocessed_time_ += time_delta;
            const auto particles_to_emit = (unprocessed_time_ / period) * count_;
            unprocessed_time_ = unprocessed_time_ % period;

            for (int i = 0; i < particles_to_emit; ++i) {
                particles_.push_back(Particle());
                auto& particle = particles_.back();

                particle.life_time = particle_life_time_;
                particle.time_remaining = particle.life_time;

                particle.random_seed = next_random(random_seed_);

                if (type_.use_velocity_) {
                    // Compute initial position and velocity in the context of the emitter
                    particle.position.x = type_.particle_position_x_.Run(scope_);
                    particle.position.y = type_.particle_position_y_.Run(scope_);
                    particle.position.z = type_.particle_position_z_.Run(scope_);
                    particle.position = gfx::Vector3(emitter_transform * particle.position);

                    particle.velocity.x = type_.particle_velocity_x_.Run(scope_);
                    particle.velocity.y = type_.particle_velocity_y_.Run(scope_);
                    particle.velocity.z = type_.particle_velocity_z_.Run(scope_);
                    particle.velocity = gfx::Vector3(emitter_transform * particle.velocity);
                }
            }
        }

        // Process particles
        for (auto& particle : particles_) {
            scope_.set_time(particle.life_time - particle.time_remaining);
            scope_.set_random_seed(particle.random_seed);
            scope_.set_lifeline(1.0 - static_cast<double>(particle.time_remaining) / particle.life_time);

            if (type_.use_velocity_) {
                // Compute position from acceleration
                gfx::Vector3 acceleration;
                acceleration.x = type_.particle_acceleration_x_.Run(scope_);
                acceleration.y = type_.particle_acceleration_y_.Run(scope_);
                acceleration.z = type_.particle_acceleration_z_.Run(scope_);

                particle.velocity = particle.velocity + acceleration * (static_cast<double>(time_delta) / 1000.0f);

                particle.position = particle.position + particle.velocity * (static_cast<double>(time_delta) / 1000.0f);
            } else {
                // Set position directly
                particle.position.x = type_.particle_position_x_.Run(scope_);
                particle.position.y = type_.particle_position_y_.Run(scope_);
                particle.position.z = type_.particle_position_z_.Run(scope_);
            }

            if (type_.apply_emitter_transform_) {
                particle.transformed_position = gfx::Vector3(emitter_transform * particle.position);
            } else {
                particle.transformed_position = particle.position;
            }

            particle.rotation.x = type_.particle_rotation_x_.Run(scope_);
            particle.rotation.y = type_.particle_rotation_y_.Run(scope_);
            particle.rotation.z = type_.particle_rotation_z_.Run(scope_);

            particle.size.x = type_.particle_scale_x_.Run(scope_);
            particle.size.y = type_.particle_scale_y_.Run(scope_);

            particle.color.r = type_.particle_color_r_.Run(scope_);
            particle.color.g = type_.particle_color_g_.Run(scope_);
            particle.color.b = type_.particle_color_b_.Run(scope_);
            particle.color.a = type_.particle_color_a_.Run(scope_);

            particle.color = color_ * particle.color;

            particle.time_remaining -= time_delta;
        }

        // Remove expired particles
        particles_.remove_if([](const auto& particle) { return particle.time_remaining <= 0; });
    }

    void SpriteEmitter::WriteMesh(gfx::SpriteMesh& mesh)
    {
        if (particles_.empty())
            return;

        auto it = mesh.BeginAppend(particles_.size());

        for (const auto& p : particles_)
        {
            it->position = p.transformed_position;
            it->rotation = p.rotation;
            it->size     = p.size;
            it->color    = p.color.ToRGBA();
            ++it;
        }

        mesh.EndAppend();
    }

}
