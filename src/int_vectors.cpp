#include "../include/int_vectors.hpp"
#include <raylib.h>
#include <cmath>

int_vector2 int_ops::convert_fv2_iv2(Vector2 v2){
    int_vector2 rtv;

    rtv.x = (int)std::floor(v2.x);
    rtv.y = (int)std::floor(v2.y);

    return rtv;
}

int_vector3 int_ops::convert_fv3_iv3(Vector3 v3){
    int_vector3 rtv;

    rtv.x = (int)std::floor(v3.x);
    rtv.y = (int)std::floor(v3.y);
    rtv.z = (int)std::floor(v3.z);

    return rtv;
}

Vector2 int_ops::convert_iv2_fv2(int_vector2 iv2){
    Vector2 rtv;

    rtv.x = (float)iv2.x;
    rtv.y = (float)iv2.y;

    return rtv;
}

Vector3 int_ops::convert_iv3_fv3(int_vector3 iv3){
    Vector3 rtv;

    rtv.x = (float)iv3.x;
    rtv.y = (float)iv3.y;
    rtv.z = (float)iv3.z;

    return rtv;

}


