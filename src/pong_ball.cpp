#include "pong_model.hpp"
#include "raylib.h"
#include "raymath.h"

//UTIL
//========
// Normalize input value within input range
RMDEF float Normalize(float value, float start, float end) {
    return (value - start) / (end - start);
}

// Remap input value within input range to output range
RMDEF float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd) {
    return (value - inputStart) / (inputEnd - inputStart) * (outputEnd - outputStart) + outputStart;
}
//========


pong::Ball::Ball(float x, float y, float r, float s, float d)  : GeometryColours(Color{0,0,230,255}, Color{60,60,60,255}), xyPosition(Vector2{x,y}), radius(r), speed(s) {
    setDirection(d);
}

void pong::Ball::drawObject() {
    DrawCircle(xyPosition.x, xyPosition.y, radius, fillColour);
    DrawCircleLines(xyPosition.x, xyPosition.y, radius, lineColour);
}

enum RectangleCorner { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
Rectangle expandRectangleByAmount(Rectangle const& rect, float amount) {
    return Rectangle{rect.x-amount, rect.y-amount, rect.width+2*amount, rect.height+2*amount};
}
Vector2 getRectangleCoord(Rectangle const& rect, RectangleCorner desiredCorner) {
    if (desiredCorner == TOPLEFT)
        return Vector2{rect.x, rect.y};
    else if (desiredCorner == TOPRIGHT)
        return Vector2{rect.x+rect.width, rect.y};
    else if (desiredCorner == BOTTOMLEFT)
        return Vector2{rect.x, rect.y+rect.height};
    else
        return Vector2{rect.x+rect.width, rect.y+rect.height};
}

bool isValueWithinRange(float value, float min, float max) { return value >= min && value <= max; }

Vector2 haltTravelAtXBarrier(Vector2& coord, Vector2& target, float barrier) {
    return Vector2 {barrier, Remap(target.y, coord.y, target.y, coord.x, barrier)};
}
Vector2 haltTravelAtYBarrier(Vector2& coord, Vector2& target, float barrier) {
    return Vector2 {Remap(target.x, coord.x, target.x, 5,7), barrier};
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

    Vector2 scaledMovementVect = Vector2Scale(directionVect, frameTime*speed);

    Rectangle P1PaddleCollisionZone = expandRectangleByAmount(gameModel.P1Paddle.getCollisionBox(), radius);
    Rectangle P2PaddleCollisionZone = expandRectangleByAmount(gameModel.P2Paddle.getCollisionBox(), radius);
    Rectangle TopWallCollisionZone = expandRectangleByAmount(gameModel.TopWall.getCollisionBox(), radius);
    Rectangle BottomWallCollisionZone = expandRectangleByAmount(gameModel.BottomWall.getCollisionBox(), radius);

    Vector2 targetCoord = Vector2Add(xyPosition, scaledMovementVect);
    float unusedFrametimeRatio = 0;
    if (isValueWithinRange(BottomWallCollisionZone.y, xyPosition.y, targetCoord.y)) { //Will bounce
        unusedFrametimeRatio = (BottomWallCollisionZone.y-xyPosition.y)/(targetCoord.y-xyPosition.y);
        xyPosition = Vector2Add(xyPosition, Vector2Scale(scaledMovementVect, unusedFrametimeRatio));
        directionVect.y *= -1; //Invert y movement
        updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
    }

    else {
        xyPosition = Vector2Add(xyPosition, scaledMovementVect);
    }
}

void pong::Ball::setDirection(Vector2& directionVector) { directionVect = directionVector; }
void pong::Ball::setDirection(float radianAngle) {
    directionVect.x = sinf(radianAngle);
    directionVect.y = cosf(radianAngle);
}