#include "pong_model.hpp"
#include "raylib.h"
#include "raylib_extensions.hpp"
#include "raymath.h"

using namespace extensions;

void pong::Paddle::drawObject() {
    // int rectCornerX = (int) (xpos - rect.width/2.0);
    // int rectCornerY = (int) (ypos - rect.height/2.0);
    // DrawRectangle(rectCornerX, rectCornerY, width, height, fillColour);
    DrawRectangleRec(rect, fillColour);
    DrawRectangleLinesEx(rect, 1, lineColour);
}

void pong::Paddle::updatePaddle(float verticalDelta, float maxYPos, float minYPos) {
    float modifiedMinYPos = minYPos + rect.height/2.0;
    float modifiedMaxYPos = maxYPos - rect.height/2.0;
    
    //Move the paddle vertically
    xyPosition.y += verticalDelta;
    rect.y += verticalDelta;

    //Ensure paddle doesn't leave boundaries
    if (xyPosition.y < modifiedMinYPos)
        xyPosition.y = modifiedMinYPos;
    if (xyPosition.y > modifiedMaxYPos)
        xyPosition.y = modifiedMaxYPos;
}

void pong::ScoreBoard::drawObject() {
    Font font = GetFontDefault();
    DrawTextRec(font, TextFormat("%d", model_ptr->P1Score), P1ScoreDisplayZone, fontSize, 0, 0, BLACK);
    DrawTextRec(font, TextFormat("%d", model_ptr->P2Score), P2ScoreDisplayZone, fontSize, 0, 0, BLACK);
}

pong::PongModel::PongModel(concept::GameWorld* gw) {
    worldInfo = gw;
    canBallMove = false;
    int topBottomWallThickness = 10;
    MaxPaddleYPosition = 0 + topBottomWallThickness;
    MinPaddleYPosition = gw->height - topBottomWallThickness;
    P1Score = 0;
    P2Score = 0;
    
    paddleWidth = 20;
    paddleHeight = 60;
    paddleSpeed = 120;
    P1Paddle = Paddle(Vector2{0 + paddleWidth/2.0f, gw->height/2.0f}, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(Vector2{gw->width - paddleWidth/2.0f, gw->height/2.0f}, paddleWidth, paddleHeight, paddleSpeed);

    TopWall = Wall(Rectangle{0, 0, gw->width, (float)topBottomWallThickness});
    BottomWall = Wall(Rectangle{0, gw->height-topBottomWallThickness, gw->width, (float)topBottomWallThickness});

    PongBall = Ball(gw->width/2.0, gw->height/2.0, 10, 150, PI/4);

    float fontSize = 50;
    GameScore = ScoreBoard(this, RectangleCentreOnCoord(Vector2{worldInfo->width/4.0f, worldInfo->height/2.0f}, fontSize, fontSize),
        RectangleCentreOnCoord(Vector2{3.0f*worldInfo->width/4.0f, worldInfo->height/2.0f}, fontSize, fontSize), fontSize);

    P1ScoreZone = ScoreZone(Rectangle{0, 0, PongBall.radius, worldInfo->height});
    P2ScoreZone = ScoreZone(Rectangle{worldInfo->width - PongBall.radius, 0, PongBall.radius, worldInfo->height});
}

void pong::PongModel::drawObject() {
    GameScore.drawObject();
    P1Paddle.drawObject();
    P2Paddle.drawObject();
    TopWall.drawObject();
    BottomWall.drawObject();
    PongBall.drawObject();
}