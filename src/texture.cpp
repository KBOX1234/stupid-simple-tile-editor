#include "../include/texture.hpp"
#include "../include/f_utils.hpp"
#include <cstdlib>
#include <ostream>
#include <raylib.h>

int texture_manager::does_texture_exist(const std::string& path){
    for (const auto& [id, texture_s] : textures) {
        if(texture_s->origin == path) return id;
    }
    
    return -1;
}

int texture_manager::default_texture(){
    return default_texture_id;
}

int texture_manager::add_texture(const std::string& path){


    if(!easy_file_ops::file_exists(path)){
        std::cout << "(TEXTURE_MASTER): Error, texture does not exist: " << path << std::endl;
        return -1;
    }

    int id = textures.size();

    texture_archive* txt = new texture_archive;

    txt->origin = path;

    if(raylib_started == false){
        txt->loaded = false;
    }

    else{
        txt->loaded = true;

        txt->texture = LoadTexture(path.c_str());
    }

    textures[id] = txt;

    return id;
}

Texture2D texture_manager::yoink_texture(int id){
    texture_archive* txt;

    if(textures.count(id)){
        txt = textures[id];
    } else return default_texture_T;

    if(txt->loaded == false){
        txt->texture = LoadTexture(txt->origin.c_str());
    }

    if(txt->texture.id == 0) {
        if(id == default_texture_id || default_texture_id == -1){

            std::cout << "(TEXTURE_MASTER): Returned error because while falling back to the default texture, it was found that the default texture was invalid.\n(TEXTURE_MASTER): Error Code: " << -1 << std::endl;
            
            exit(-1);
            
        }

        return default_texture_T;
    }

    return txt->texture;
} 

void texture_manager::set_default_texture(const std::string& path){
    default_texture_id = add_texture(path);

    default_texture_T = yoink_texture(default_texture_id);
    
    if(default_texture_T.id == 0){
        std::cout << "(TEXTURE_MASTER): Returned error because set_default_texture() failed to find texture\n(TEXTURE_MASTER): Error Code: " << -1 << std::endl;
    }
}

void texture_manager::clean_up(){
    for (const auto& [id, texture_s] : textures) {
        if(texture_s->loaded == true) UnloadTexture(texture_s->texture);
    }
}

void texture_manager::print_all_ids(){
    for (const auto& [id, texture_s] : textures) {
        std::cout << id << std::endl;    
    }

}

texture_manager::~texture_manager(){
    for (const auto& [id, texture_s] : textures) {
        delete texture_s;  
    }

}
