#include <iostream>
#include "raylib.h"

#include "../include/texture.hpp"
#include "../include/tilemap.hpp"

bool raylib_started = false;

texture_manager texture_master;


int main(){

    InitWindow(1280, 720, "Tile Editor");

    std::cout << "Starting tile editor\n";

    bool running = true;

    tilemap tm;

    tm.new_layer("test", {32, 32});

    tm.export_tilemap("test.tlm");

    while(running){
        if(WindowShouldClose() &&!IsKeyDown(KEY_ESCAPE)){
            running = false;
        }
        BeginDrawing();
        ClearBackground(WHITE);

        tm.draw_tilemap({0, 0});

        EndDrawing();
    }

    return 0;
}
