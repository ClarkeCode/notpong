#include "pong_model.hpp"
#include "raylib.h"
#include "raymath.h"

pong::Ball::Ball(float x, float y, float r, float s, float d)  : GeometryColours(Color{0,0,230,255}, Color{60,60,60,255}), xyPosition(Vector2{x,y}), radius(r), speed(s) {
    setDirection(d);
}

void pong::Ball::drawObject() {
    DrawCircle(xyPosition.x, xyPosition.y, radius, fillColour);
    DrawCircleLines(xyPosition.x, xyPosition.y, radius, lineColour);
}

enum RectangleSide { TOP, BOTTOM, LEFT, RIGHT };
enum RectangleVertex { TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };
Rectangle RectangleExpandByAmount(Rectangle const& rect, float amount) {
    return Rectangle{rect.x-amount, rect.y-amount, rect.width+2*amount, rect.height+2*amount};
}
Vector2 RectangleGetVertexCoord(Rectangle const& rect, RectangleVertex desiredVertex) {
    if (desiredVertex == TOPLEFT)
        return Vector2{rect.x, rect.y};
    else if (desiredVertex == TOPRIGHT)
        return Vector2{rect.x+rect.width, rect.y};
    else if (desiredVertex == BOTTOMLEFT)
        return Vector2{rect.x, rect.y+rect.height};
    else
        return Vector2{rect.x+rect.width, rect.y+rect.height};
}

bool isValueWithinRange(float value, float min, float max) { return value >= min && value <= max; }
bool isPointWithinYValues(Vector2 const& xyCoord, Rectangle const& rect) {
    return xyCoord.y >= rect.y && xyCoord.y <= rect.y + rect.height;
}
bool isPointWithinXValues(Vector2 const& xyCoord, Rectangle const& rect) {
    return xyCoord.x >= rect.x && xyCoord.x <= rect.x + rect.width;
}

void pong::Ball::updateBall(float frameTime, PongModel& gameModel) {
    //If the game has not started, do not move
    if (!gameModel.canBallMove) {
        return;
    }

    Vector2 scaledMovementVect = Vector2Scale(directionVect, frameTime*speed);

    Rectangle P1PaddleCollisionZone = RectangleExpandByAmount(gameModel.P1Paddle.getCollisionBox(), radius);
    Rectangle P2PaddleCollisionZone = RectangleExpandByAmount(gameModel.P2Paddle.getCollisionBox(), radius);
    Rectangle TopWallCollisionZone = RectangleExpandByAmount(gameModel.TopWall.getCollisionBox(), radius);
    Rectangle BottomWallCollisionZone = RectangleExpandByAmount(gameModel.BottomWall.getCollisionBox(), radius);

    Vector2 targetCoord = Vector2Add(xyPosition, scaledMovementVect);
    float unusedFrametimeRatio = 0;

    //Bouncing off paddles
    if (isValueWithinRange(P1PaddleCollisionZone.x+P1PaddleCollisionZone.width, targetCoord.x, xyPosition.x)) { //Ball will pass by the right side of the paddle
        unusedFrametimeRatio = (xyPosition.x-(P1PaddleCollisionZone.x+P1PaddleCollisionZone.width))/(xyPosition.x-targetCoord.x);
        Vector2 candidatePosition = Vector2Add(xyPosition, Vector2Scale(scaledMovementVect, unusedFrametimeRatio));
        if (isPointWithinYValues(candidatePosition, P1PaddleCollisionZone)) { //Ball will be in contact as it goes to the right side of the paddle
            xyPosition = candidatePosition;
            directionVect.x *= -1; //Invert x movement
            updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
        }
    }
    else if (isValueWithinRange(P2PaddleCollisionZone.x, xyPosition.x, targetCoord.x)) { //Ball will pass by the left side of the paddle
        unusedFrametimeRatio = (P2PaddleCollisionZone.x-xyPosition.x)/(targetCoord.x-xyPosition.x);
        Vector2 candidatePosition = Vector2Add(xyPosition, Vector2Scale(scaledMovementVect, unusedFrametimeRatio));
        if (isPointWithinYValues(candidatePosition, P2PaddleCollisionZone)) { //Ball will be in contact as it goes to the left side of the paddle
            xyPosition = candidatePosition;
            directionVect.x *= -1; //Invert x movement
            updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
        }
    }

    //Bouncing off walls
    if (isValueWithinRange(TopWallCollisionZone.y+TopWallCollisionZone.height, targetCoord.y, xyPosition.y)) {
        unusedFrametimeRatio = (xyPosition.y-(TopWallCollisionZone.y+TopWallCollisionZone.height))/(xyPosition.y-targetCoord.y);
        xyPosition = Vector2Add(xyPosition, Vector2Scale(scaledMovementVect, unusedFrametimeRatio));
        directionVect.y *= -1; //Invert y movement
        updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
    }
    else if (isValueWithinRange(BottomWallCollisionZone.y, xyPosition.y, targetCoord.y)) { //Will bounce
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