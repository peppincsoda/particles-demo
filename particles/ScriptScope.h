#ifndef SCRIPTSCOPE_H
#define SCRIPTSCOPE_H

#include "mathscript/RuntimeScope.h"

namespace particles {

    class ScriptScope : public mathscript::RuntimeScope
    {
    public:
        ScriptScope();

        void set_time(double time);
        void set_random_seed(uint32_t random_seed);
        void set_lifeline(double lifeline);

    private:
        double time_;
        uint32_t random_seed_;
        double lifeline_;
    };

}

#endif // SCRIPTSCOPE_H
