#include "../include/tilemap.hpp"
#include "../include/texture.hpp"
#include "../include/f_utils.hpp"
#include "../include/json.hpp"
#include "../include/util.hpp"
#include <cstddef>
#include <cstring>
#include <raylib.h>

void layer::resize(int_vector2 new_size){
    tile_index* new_tiles = new tile_index[new_size.x * new_size.y];

    memset(new_tiles, -1, new_size.x * new_size.y);

    if(size.x > new_size.x) size.x = new_size.x;
    if(size.y > new_size.y) size.y = new_size.y;

    for(int x = 0; x < size.x; x++){
        for(int y = 0; y < size.y; y++){
            int index_new = (y * new_size.y) + x;
            int index_old = (y * size.y) + x;


            new_tiles[index_new] = data[index_old];
        }
    }

    delete [] data;

    data = new_tiles;

    size = new_size;
}

layer::~layer(){
    if(data){
        delete [] data;
    }
}

int tilemap::find_layer_index(const std::string& name){
    for(int i = 0; i < layers.size(); i++){
        if(layers[i].name == name) return i;
    }

    return -1;
}

void tilemap::draw_layer(int layer_i, Vector2 offset){
    if(layer_i >= layers.size()) return;


    layer* l = &layers[layer_i];

    for(int x = offset.x; x < l->size.x + offset.x; x++){
        for(int y = offset.y; y < l->size.y + offset.y; y++){
            tile_index ti = l->data[(y * l->size.x) + x];

            tile draw_tile = tl.tiles[ti.bank][ti.tile_type];

            if(draw_tile.texture_id == -1) continue;

            Texture2D tx = texture_master.yoink_texture(draw_tile.texture_id);

            DrawTexture(tx, (x * l->tile_size.x) + offset.x, (y * l->tile_size.y) + offset.y, WHITE);
        }
    }
}

void tilemap::load_tile_pallet_json(const std::string& fname){
    std::string json_str = easy_file_ops::load_text_file(fname);

    if(json_str == NOFILE__) return;

    nlohmann::json j_obj = nlohmann::json::parse(json_str);

    if(!j_obj.is_array()) return;

    for(size_t i = 0; i < j_obj.size(); i++){
        nlohmann::json bank = j_obj[i];

        for(size_t j = 0; j <  bank.size(); j++){
            nlohmann::json entry = bank[i];

            tile t;
            t.name = entry.value("name", "");
            t.file = entry.value("file", "");

            if(t.file == "") continue;

            t.texture_id = texture_master.add_texture(t.file);

            tl.tiles[i][j] = t;
        }
    }

}

void tilemap::new_layer(const std::string& name, int_vector2 size){
    layer l;

    l.resize(size);
    l.name = name;

    layers.push_back(l);
}

void tilemap::resize_layer(const std::string& name, int_vector2 new_size){
    int index = find_layer_index(name);

    if(index == -1) return;

    layers[index].resize(new_size);
}

void tilemap::rename_layer(const std::string& old_name, const std::string& new_name){
    int index = find_layer_index(old_name);

    if(index == -1) return;

    layers[index].name = new_name;
}

void tilemap::draw_tilemap(Vector2 offset){
    for(size_t i = 0; i < layers.size(); i++){
        if(!layers[i].render) continue;
        Vector2 offset_2 = {offset.x * layers[i].pos_scale, offset.y * layers[i].pos_scale};

        draw_layer(i, offset_2);
    }
}

void tilemap::toggle_layer(const std::string& name){
    int index = find_layer_index(name);
    if(index == -1) return;

    bool* render = &layers[index].render;

    if(*render == true) *render = false;
    else if(*render == false) *render = true;
}

void tilemap::export_tilemap(const std::string& fname){
    size_t total_size = 0;

    total_size = total_size + sizeof(tile_map_header);

    for(int i = 0; i < layers.size(); i++){
        size_t layer_size = 0;

        layer_size = layer_size + sizeof(layer_header);

        layer_size = layer_size + ((layers[i].size.x * layers[i].size.y) * sizeof(tile_index));
        
        total_size = total_size + layer_size;
    }

    char* buffer = new char[total_size];
    size_t pointer = 0;

    tile_map_header tm_header;

    tm_header.layer_count = layers.size();

    memcpy(buffer + pointer, &tm_header, sizeof(tile_map_header));
    pointer = pointer + sizeof(tile_map_header);

    for(int i = 0; i < layers.size(); i++){
        layer_header lh = {0};

        layer* l = &layers[i];

        lh.size.x = l->size.x;
        lh.size.y = l->size.y;
        util::float_to_bytes(l->pos_scale, lh.pos_scale_p_float);
        
        size_t name_size = l->name.size() + 1;

        if(name_size >= MAX_LAYER_NAME_LENGTH){
            name_size = MAX_LAYER_NAME_LENGTH - 1;
        }

        memcpy(lh.name, l->name.c_str(), name_size);
        lh.name[MAX_LAYER_NAME_LENGTH-1] = '\0';

        memcpy(buffer + pointer, &lh, sizeof(layer_header));
        
        pointer = pointer + sizeof(layer_header);

        size_t layer_data_size = (l->size.x * l->size.y) * sizeof(tile_index);

        memcpy(buffer + pointer, l->data, layer_data_size);

        pointer = pointer + layer_data_size;
    }
    std::string bin_str(reinterpret_cast<char*>(buffer), total_size);

    easy_file_ops::save_binary_file(bin_str, fname);
}
