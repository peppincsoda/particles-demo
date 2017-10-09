#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

namespace particles {

  // Source: http://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
  inline static uint32_t next_random(uint32_t& seed)
  {
      seed = seed * 1664525U + 1013904223U;
      return seed;
  }

  // 0 <= _ <= 1
  inline static double next_random_01(uint32_t& seed)
  {
      return static_cast<double>(next_random(seed)) / UINT32_MAX;
  }

  // -1 <= _ <= 1
  inline static double next_random_11(uint32_t& seed)
  {
      return 2.0 * next_random_01(seed) - 1.0;
  }

}

#endif // RANDOM_H
