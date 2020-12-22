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

Camera2D setupCamera(concept::GameWorld& gw) {
    Camera2D camera {0};
    camera.target = Vector2{ (float)gw.width/2, (float)gw.height/2 };
    camera.offset = Vector2{ (float)gw.width/2, (float)gw.height/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

void updateGameState(pong::PongModel& model) {
    float frameTime = GetFrameTime();
    
    //P1 controls
    if (IsKeyDown(KEY_W))
        model.P1Paddle.updatePaddle(frameTime * model.P1Paddle.speed * -1, model.BottomWall.getCollisionBox().y, model.TopWall.getCollisionBox().height);
    if (IsKeyDown(KEY_S))
        model.P1Paddle.updatePaddle(frameTime * model.P1Paddle.speed, model.BottomWall.getCollisionBox().y, model.TopWall.getCollisionBox().height);

    //P2 controls
    if (IsKeyDown(KEY_UP))
        model.P2Paddle.updatePaddle(frameTime * model.P2Paddle.speed * -1, model.BottomWall.getCollisionBox().y, model.TopWall.getCollisionBox().height);
    if (IsKeyDown(KEY_DOWN))
        model.P2Paddle.updatePaddle(frameTime * model.P2Paddle.speed, model.BottomWall.getCollisionBox().y, model.TopWall.getCollisionBox().height);
    
    //Start ball movement
    if (IsKeyPressed(KEY_R)) {
        if (model.canBallMove) {
            model.PongBall.xyPosition = Vector2{model.worldInfo->width/2.0f, model.worldInfo->height/2.0f};
            model.PongBall.setDirection(DEG2RAD * GetRandomValue(0, 360));
        }
        model.canBallMove = true;
    }

    model.PongBall.updateBall(frameTime, model);
}

void drawGameState(Camera2D& camera, pong::PongModel& model) {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                model.drawObject();
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
    concept::GameWorld gameWorld(800, 450);

    InitWindow(gameWorld.width, gameWorld.height, "NotPong");
    std::cout << "Screen " << GetMonitorWidth(0) << ", " << GetMonitorHeight(0) << "\n";

    Camera2D camera = setupCamera(gameWorld);
    pong::PongModel gameModel(&gameWorld);
    
    SetTargetFPS(60); // Set game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    while (!IsWindowReady()) {
        continue;
    }
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