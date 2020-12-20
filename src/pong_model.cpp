#include "pong_model.hpp"
#include "raylib.h"
#include "raymath.h"

void pong::Paddle::drawObject() {
    int rectCornerX = (int) (xpos - width/2.0);
    int rectCornerY = (int) (ypos - height/2.0);
    DrawRectangle(rectCornerX, rectCornerY, width, height, fillColour);
    DrawRectangleLinesEx(Rectangle{(float)rectCornerX, (float)rectCornerY, width, height}, 1, lineColour);
}

void pong::Paddle::updatePaddle(float verticalDelta, float maxYPos, float minYPos) {
    float modifiedMinYPos = minYPos + height/2.0;
    float modifiedMaxYPos = maxYPos - height/2.0;
    
    //Move the paddle vertically
    ypos += verticalDelta;

    //Ensure paddle doesn't leave boundaries
    if (ypos < modifiedMinYPos)
        ypos = modifiedMinYPos;
    if (ypos > modifiedMaxYPos)
        ypos = modifiedMaxYPos;
}

Rectangle pong::Paddle::getCollisionBox() {
    return Rectangle{xpos-width/2.0f, ypos-height/2.0f, width, height};
}

pong::PongModel::PongModel(concept::GameWorld* gw) {
    worldInfo = gw;
    canBallMove = false;
    topBottomWallThickness = 10;
    MaxPaddleYPosition = 0 + topBottomWallThickness;
    MinPaddleYPosition = gw->height - topBottomWallThickness;
    
    paddleWidth = 20;
    paddleHeight = 60;
    paddleSpeed = 70;
    P1Paddle = Paddle(0 + paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(gw->width - paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);

    PongBall.xyPosition.x = gw->width/2.0;
    PongBall.xyPosition.y = gw->height/2.0;
    PongBall.radius = 10;
    PongBall.speed = 50;
    PongBall.direction = PI/4;
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