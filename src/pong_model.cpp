#include "pong_model.hpp"
#include "raylib.h"

void pong::Paddle::drawObject() {
    int rectCornerX = (int) (xpos - width/2.0);
    int rectCornerY = (int) (ypos - height/2.0);
    DrawRectangle(rectCornerX, rectCornerY, width, height, fillColour);
    DrawRectangleLinesEx(Rectangle{(float)rectCornerX, (float)rectCornerY, (float)width, (float)height}, 1, lineColour);
}

void pong::Ball::drawObject() {
    DrawCircle(xpos, ypos, radius, fillColour);
    DrawCircleLines(xpos, ypos, radius, lineColour);
}

pong::PongModel::PongModel(GameWorld* gw) {
    worldInfo = gw;
    topBottomWallThickness = 10;
    MaxPaddleYPosition = 0 + topBottomWallThickness;
    MinPaddleYPosition = gw->height - topBottomWallThickness;
    
    paddleWidth = 20;
    paddleHeight = 60;
    paddleSpeed = 10;
    P1Paddle = Paddle(0 + paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(gw->width - paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);

    PongBall.xpos = gw->width/2.0;
    PongBall.ypos = gw->height/2.0;
    PongBall.radius = 10;
    PongBall.speed = 20;
}

void pong::PongModel::drawObject() {
    //Top Wall
    DrawRectangleRec(Rectangle{0, 0, (float)worldInfo->width, (float)topBottomWallThickness}, GRAY);
    DrawRectangleLinesEx(Rectangle{0, 0, (float)worldInfo->width, (float)topBottomWallThickness}, 1, DARKGRAY);

    //Bottom Wall
    DrawRectangleRec(Rectangle{0, (float)(worldInfo->height - topBottomWallThickness), (float)worldInfo->width, (float)topBottomWallThickness}, GRAY);
    DrawRectangleLinesEx(Rectangle{0, (float)(worldInfo->height - topBottomWallThickness), (float)worldInfo->width, (float)topBottomWallThickness}, 1, DARKGRAY);

    P1Paddle.drawObject();
    P2Paddle.drawObject();
    PongBall.drawObject();
}