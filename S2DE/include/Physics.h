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
        static hitinfo Raycast(ray2f ray);
		static hitinfo Raycast(ray2f ray, const mask& layers);
		static hitinfo Raycast(ray2f ray, const mask& layers, bool ignoreTriggers);
		// ADD RaycastAll functions

    };

}

#endif