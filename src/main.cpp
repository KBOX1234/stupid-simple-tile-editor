#include <iostream>
#include "raylib.h"

#include "../include/texture.hpp"

bool raylib_started = false;

texture_manager texture_master;


int main(){

    InitWindow(1280, 720, "Tile Editor");

    std::cout << "Starting tile editor\n";

    bool running = true;

    while(running){
        if(WindowShouldClose() &&!IsKeyDown(KEY_ESCAPE)){
            running = false;
        }
        BeginDrawing();
        ClearBackground(WHITE);


        EndDrawing();
    }

    return 0;
}
