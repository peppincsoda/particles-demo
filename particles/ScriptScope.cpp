#include "ScriptScope.h"

#include "Random.h"

namespace particles {

    ScriptScope::ScriptScope()
        : time_(0)
        , random_seed_(0)
        , lifeline_(0)
    {
        SetFunc("time", [this]() { return time_; });
        SetFunc("rand", [this]() { return next_random_01(random_seed_); });
        SetFunc("rand1", [this]() { return next_random_11(random_seed_); });
        SetFunc("lifeline", [this]() { return lifeline_; });
    }

    void ScriptScope::set_time(double time)
    {
        time_ = time;
    }

    void ScriptScope::set_random_seed(uint32_t random_seed)
    {
        random_seed_ = random_seed;
    }

    void ScriptScope::set_lifeline(double lifeline)
    {
        lifeline_ = lifeline;
    }

}
