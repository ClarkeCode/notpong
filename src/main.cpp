/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "pong_model.hpp"
#include <iostream>

Camera2D setupCamera(pong::GameWorld& gw) {
    Camera2D camera {0};
    camera.target = Vector2{ (float)gw.width/2, (float)gw.height/2 };
    camera.offset = Vector2{ (float)gw.width/2, (float)gw.height/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

void updateGameState(pong::PongModel& model) {
    //float frameTime = GetFrameTime();
    // Update
    //----------------------------------------------------------------------------------
    //if (IsKeyDown(KEY_RIGHT)) camera.fovy += frameTime * fovChangePerSecond;
    //if (IsKeyDown(KEY_LEFT)) camera.fovy -= frameTime * fovChangePerSecond;
    //pressedKey = GetKeyPressed();
    //if (pressedKey != oldKey && pressedKey != 0) oldKey = pressedKey;
    //if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
    //if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
    //-----------------------------------------------
}

void drawGameState(Camera2D& camera, pong::PongModel& model) {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                DrawGrid(10, 1.0f);

            EndMode2D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            //DrawText(TextFormat("FOV: %f", camera.fovy), 10, 60, 20, DARKGRAY);
            //DrawText(TextFormat("Last key: %d", oldKey), 10, 80, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
}

int main(int argc, char* argv[]) {
    // Initialization
    //--------------------------------------------------------------------------------------
    pong::GameWorld gameWorld(800, 450);

    InitWindow(gameWorld.width, gameWorld.height, "NotPong");
    std::cout << "Screen " << GetMonitorWidth(0) << ", " << GetMonitorHeight(0) << "\n";

    Camera2D camera = setupCamera(gameWorld);
    pong::PongModel gameModel(gameWorld);
    
    SetTargetFPS(60); // Set game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        updateGameState(gameModel);

        drawGameState(camera, gameModel);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}