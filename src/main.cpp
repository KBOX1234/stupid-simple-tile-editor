#include <iostream>
#include "raylib.h"


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
