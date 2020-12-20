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

void pong::Ball::drawObject() {
    DrawCircle(xyPosition.x, xyPosition.y, radius, fillColour);
    DrawCircleLines(xyPosition.x, xyPosition.y, radius, lineColour);
}

float flipAngleVerticalCollision(float angle) {
    if (angle < PI/2.0) //Q1 -> Q2
        return PI - angle;
    else if (angle < PI) //Q2 -> Q1
        return PI - angle;
    else if (angle < 3*PI/2.0) //Q3 -> Q4  3PI-angle
        return 2*PI - (angle - PI);
    else //Q4 -> Q3
        return PI + (2*PI - angle);
}

float flipAngleHorizontalCollision(float angle) {
    if (angle < PI/2.0) //Q1 -> Q4
        return 2*PI - angle;
    else if (angle < PI) //Q2 -> Q3
        return PI + (PI - angle);
    else if (angle < 3*PI/2.0) //Q3 -> Q2
        return PI - (angle-PI);
    else //Q4 -> Q1
        return 2*PI - angle;
}

bool isPointWithinYValues(Vector2& xyCoord, Vector2& yMinMaxValues) {
    return xyCoord.y >= yMinMaxValues.x && xyCoord.y <= yMinMaxValues.y;
}
bool isPointWithinXValues(Vector2& xyCoord, Vector2& xMinMaxValues) {
    return xyCoord.x >= xMinMaxValues.x && xyCoord.x <= xMinMaxValues.y;
}
bool isPointBelowYValue(Vector2& xyCoord, float yValue) {
    return xyCoord.y > yValue; //Larger Y-values are lower in screen-space
}
bool isPointLeftOfXValue(Vector2& xyCoord, float xValue) {
    return xyCoord.x < xValue;
}
void pong::Ball::updateBall(float frameTime, PongModel& gameModel) {
    float remainingMovement = frameTime * speed;
    float xDelta, yDelta;

    xDelta = frameTime * speed * sinf(direction);
    yDelta = frameTime * speed * cosf(direction);
}

pong::PongModel::PongModel(GameWorld* gw) {
    worldInfo = gw;
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
    PongBall.direction = PI/2.5;
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