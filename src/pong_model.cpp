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

Rectangle pong::Paddle::getCollisionBox() const {
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
    paddleSpeed = 120;
    P1Paddle = Paddle(0 + paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(gw->width - paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);

    TopWall = Wall(Rectangle{0, 0, gw->width, (float)topBottomWallThickness});
    BottomWall = Wall(Rectangle{0, gw->height-topBottomWallThickness, gw->width, (float)topBottomWallThickness});

    PongBall = Ball(gw->width/2.0, gw->height/2.0, 10, 150, PI/4);
}

void pong::PongModel::drawObject() {
    P1Paddle.drawObject();
    P2Paddle.drawObject();
    TopWall.drawObject();
    BottomWall.drawObject();
    PongBall.drawObject();
}