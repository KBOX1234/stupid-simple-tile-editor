#include <cstdint>
#include <string.h>


void float_to_bytes(float f, uint8_t out[4]) {
    uint32_t temp;
    memcpy(&temp, &f, sizeof(temp));  // safe bit copy

    // convert to big-endian (network order)
    out[0] = (temp >> 24) & 0xFF;
    out[1] = (temp >> 16) & 0xFF;
    out[2] = (temp >> 8) & 0xFF;
    out[3] = temp & 0xFF;
}

float bytes_to_float(const uint8_t in[4]) {
    uint32_t temp =
        ((uint32_t)in[0] << 24) |
        ((uint32_t)in[1] << 16) |
        ((uint32_t)in[2] << 8)  |
        ((uint32_t)in[3]);

    float f;
    memcpy(&f, &temp, sizeof(f));
    return f;
}
