#include "pong_model.hpp"
#include "raylib.h"
#include "raylib_extensions.hpp"
#include "raymath.h"

using namespace extensions;

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

void pong::ScoreBoard::drawObject() {
    Font font = GetFontDefault();
    DrawTextRec(font, TextFormat("%d", model_ptr->P1Score), P1ScoreDisplayZone, fontSize, 0, 0, BLACK);
    DrawTextRec(font, TextFormat("%d", model_ptr->P2Score), P2ScoreDisplayZone, fontSize, 0, 0, BLACK);
}

pong::PongModel::PongModel(concept::GameWorld* gw) {
    worldInfo = gw;
    canBallMove = false;
    topBottomWallThickness = 10;
    MaxPaddleYPosition = 0 + topBottomWallThickness;
    MinPaddleYPosition = gw->height - topBottomWallThickness;
    P1Score = 0;
    P2Score = 0;
    
    paddleWidth = 20;
    paddleHeight = 60;
    paddleSpeed = 120;
    P1Paddle = Paddle(0 + paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(gw->width - paddleWidth/2.0, gw->height/2.0, paddleWidth, paddleHeight, paddleSpeed);

    TopWall = Wall(Rectangle{0, 0, gw->width, (float)topBottomWallThickness});
    BottomWall = Wall(Rectangle{0, gw->height-topBottomWallThickness, gw->width, (float)topBottomWallThickness});

    PongBall = Ball(gw->width/2.0, gw->height/2.0, 10, 150, PI/4);

    float fontSize = 50;
    GameScore = ScoreBoard(this, RectangleCentreOnCoord(Vector2{worldInfo->width/4.0f, worldInfo->height/2.0f}, fontSize, fontSize),
        RectangleCentreOnCoord(Vector2{3.0f*worldInfo->width/4.0f, worldInfo->height/2.0f}, fontSize, fontSize), fontSize);
}

void pong::PongModel::drawObject() {
    GameScore.drawObject();
    P1Paddle.drawObject();
    P2Paddle.drawObject();
    TopWall.drawObject();
    BottomWall.drawObject();
    PongBall.drawObject();
}