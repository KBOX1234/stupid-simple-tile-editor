#pragma once

#include "int_vectors.hpp"
#include <cstdint>
#include <raylib.h>
#include <vector>
#include <string>

#define MAX_LAYER_NAME_LENGTH 20

struct __attribute__((packed)) tile_index{
    uint8_t tile_type;
    uint8_t bank;

    uint8_t h_flip;
    uint8_t v_flip;
};

#include <stdint.h>

struct layer_header {
    char name[MAX_LAYER_NAME_LENGTH];

    uint8_t pos_scale_p_float[4];

    uint8_t pad[ (4 - ( (MAX_LAYER_NAME_LENGTH + 4) % 4 )) % 4 ];

    struct {
        int32_t x;
        int32_t y;
    } size;
};

struct tile_map_header{
    uint8_t layer_count;
};


struct layer{
    int_vector2 size = {0};
   
    tile_index* data = nullptr;

    float pos_scale = 1;

    std::string name = "";

    bool render = true;

    int_vector2 tile_size = {0};

    void resize(int_vector2 new_size);

    ~layer();
};

struct tile{
    int texture_id = -1;
    std::string file = "";
    std::string name = "";
};

struct tile_pallet{
    tile tiles[256][256] = {-1};
};

class tilemap{
    private:

        std::vector<layer> layers;

        tile_pallet tl;

        int find_layer_index(const std::string& name);

        void draw_layer(int layer, Vector2 offset);

    public:

        void load_tile_pallet_json(const std::string& fname);

        void new_layer(const std::string& name, int_vector2 size);

        void resize_layer(const std::string& name, int_vector2 new_size);

        void rename_layer(const std::string& old_name, const std::string& new_name);

        void draw_tilemap(Vector2 offset);

        void toggle_layer(const std::string& name);

        void export_tilemap(const std::string& fname);

        void load_tilemap(const std::string& fname);

};
