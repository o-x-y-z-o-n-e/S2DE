#ifndef S2DE_PHYSICS_H
#define S2DE_PHYSICS_H

#include "Types.h"

namespace S2DE {

    typedef struct mask {
        uint32_t bitmask;

        static mask GetMask(int n, ...);

        static inline mask all() { return {0xFFFF}; }

    } mask;

    class Physics {
        
    public:
        bool Raycast(const ray2f& ray);
        bool Raycast(const ray2f& ray, const mask& layers);
        bool Raycast(const ray2f& ray, const mask& layers, bool ignoreTriggers);

    };

}

#endif