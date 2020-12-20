#include "pong_model.hpp"
#include "raylib.h"
#include "raymath.h"

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

bool isPointWithinYValues(Vector2& xyCoord, Rectangle& rect) {
    return xyCoord.y >= rect.y && xyCoord.y <= rect.y + rect.height;
}
bool isPointWithinXValues(Vector2& xyCoord, Rectangle& rect) {
    return xyCoord.x >= rect.x && xyCoord.x <= rect.x + rect.width;
}
bool isPointBelowYValue(Vector2& xyCoord, float yValue) {
    return xyCoord.y > yValue; //Larger Y-values are lower in screen-space
}
bool isPointLeftOfXValue(Vector2& xyCoord, float xValue) {
    return xyCoord.x < xValue;
}
void pong::Ball::updateBall(float frameTime, PongModel& gameModel) {
    //If the game has not started, do not move
    if (!gameModel.canBallMove) {
        return;
    }

    Rectangle P2PaddleCollision = gameModel.P2Paddle.getCollisionBox();

    float remainingMovement = frameTime * speed;
    float xDelta, yDelta;

    xDelta = remainingMovement * sinf(direction);
    yDelta = remainingMovement * cosf(direction);

    Vector2 targetEndLocation {xyPosition.x + xDelta, xyPosition.y + yDelta};
    Vector2 checkPoint {0};

    if (xDelta > 0 && targetEndLocation.x > P2PaddleCollision.x - radius) { //Moving horizontally right past the P2 paddle, check collision with P2 paddle
        checkPoint.x = P2PaddleCollision.x - radius;
        float yxRatio = abs(yDelta / xDelta);
        checkPoint.y = xyPosition.y + (checkPoint.x - xyPosition.x) * (yxRatio * yDelta);

        if (isPointWithinYValues(checkPoint, P2PaddleCollision)) {
            float usedMovement = Vector2Distance(xyPosition, checkPoint);
            remainingMovement -= usedMovement;

        }
        
    }



    xyPosition.x += xDelta;
    xyPosition.y += yDelta;
}