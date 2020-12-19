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

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    
    SetCameraMode(camera, CAMERA_ORBITAL);

    Vector3 cubePosition = { 0.0f };
    int oldKey = 0;
    int pressedKey = 0;
    float fovChangePerSecond = 5;
    float frameTime = 0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
        
            // Update
            //----------------------------------------------------------------------------------
            frameTime = GetFrameTime();
            if (IsKeyDown(KEY_RIGHT)) camera.fovy += frameTime * fovChangePerSecond;
            if (IsKeyDown(KEY_LEFT)) camera.fovy -= frameTime * fovChangePerSecond;
            pressedKey = GetKeyPressed();
            if (pressedKey != oldKey && pressedKey != 0) oldKey = pressedKey;
            //if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
            //if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
            //-----------------------------------------------

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("FOV: %f", camera.fovy), 10, 60, 20, DARKGRAY);
            DrawText(TextFormat("Last key: %d", oldKey), 10, 80, 20, DARKGRAY);


            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}