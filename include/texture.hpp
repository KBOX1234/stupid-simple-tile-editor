
#ifndef TEXTURE_HPP

#define TEXTURE_HPP

#include <iostream>
#include <unordered_map>
#include "raylib.h"

struct texture_archive{
    Texture2D texture;
    std::string origin;

    bool loaded;
};

class texture_manager{
    private:
        
        std::unordered_map<int, texture_archive*> textures;

        int default_texture_id = -1;

        Texture2D default_texture_T;

    public:

        ~texture_manager();

        //if texture does not exist then return -1 otherwise it returns the texture id
        int does_texture_exist(const std::string& path);

        int default_texture();

        //returns id
        int add_texture(const std::string& path);

        Texture2D yoink_texture(int id);

        void set_default_texture(const std::string& path);

        void clean_up();

        void print_all_ids();


};

extern texture_manager texture_master;

extern bool raylib_started;

#endif
