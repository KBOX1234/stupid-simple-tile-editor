#pragma once
#include <cstdint>

class util{
    public:

        static void float_to_bytes(float f, uint8_t out[4]);

        static float bytes_to_float(const uint8_t in[4]);
};
