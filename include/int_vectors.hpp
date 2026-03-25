#pragma once

#include <raylib.h>
typedef struct{
    int x;
    int y;
} int_vector2;

typedef struct{
    int x;
    int y;
    int z;
} int_vector3;

class int_ops{
    public:

        static int_vector2 convert_fv2_iv2(Vector2 v2);

        static int_vector3 convert_fv3_iv3(Vector3 v3);

        static Vector2 convert_iv2_fv2(int_vector2 iv2);

        static Vector3 convert_iv3_fv3(int_vector3 iv3);
};
