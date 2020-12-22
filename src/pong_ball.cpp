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
Vector2 RectangleGetVertexCoord(Rectangle const& rect, RectangleVertex const& desiredVertex) {
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

bool willPathCrossRectangleSide(Vector2 const& origin, Vector2 const& target, Rectangle const& rect, RectangleSide const& sideToCheck) {
    if (sideToCheck == TOP)
        return isValueWithinRange(rect.y, origin.y, target.y);
    else if (sideToCheck == BOTTOM)
        return isValueWithinRange(rect.y + rect.height, target.y, origin.y);
    else if (sideToCheck == LEFT)
        return isValueWithinRange(rect.x, origin.x, target.x);
    else //  sideToCheck == RIGHT
        return isValueWithinRange(rect.x + rect.width, target.x, origin.x);
}
Vector2 locationCrossingRectangleSide(Vector2 const& origin, Vector2 const& target, Rectangle const& rect, RectangleSide const& sideToCheck) {
    float pathTravelledRatio = 0;

    //Determine the ratio of the path that has been traversed when crossing the specified side
    {
        if (sideToCheck == TOP)
            pathTravelledRatio = (rect.y - origin.y)/(target.y - origin.y);
        else if (sideToCheck == BOTTOM)
            pathTravelledRatio = (origin.y - (rect.y + rect.height))/(origin.y - target.y);
        else if (sideToCheck == LEFT)
            pathTravelledRatio = (rect.x - origin.x)/(target.x - origin.x);
        else //  sideToCheck == RIGHT
            pathTravelledRatio = (origin.x - (rect.x + rect.width))/(origin.x - target.x);
    }

    Vector2 directionVector = Vector2Subtract(target, origin);
    return Vector2Add(origin, Vector2Scale(directionVector, pathTravelledRatio));
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
    if (willPathCrossRectangleSide(xyPosition, targetCoord, P1PaddleCollisionZone, RIGHT)) { //Ball will pass by the right side of the paddle
        Vector2 candidatePosition = locationCrossingRectangleSide(xyPosition, targetCoord, P1PaddleCollisionZone, RIGHT);
        if (isPointWithinYValues(candidatePosition, P1PaddleCollisionZone)) { //Ball will be in contact as it goes to the right side of the paddle
            xyPosition = candidatePosition;
            directionVect.x *= -1; //Invert x movement
            updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
        }
    }
    else if (willPathCrossRectangleSide(xyPosition, targetCoord, P2PaddleCollisionZone, LEFT)) { //Ball will pass by the left side of the paddle
        Vector2 candidatePosition = locationCrossingRectangleSide(xyPosition, targetCoord, P2PaddleCollisionZone, LEFT);
        if (isPointWithinYValues(candidatePosition, P2PaddleCollisionZone)) { //Ball will be in contact as it goes to the left side of the paddle
            xyPosition = candidatePosition;
            directionVect.x *= -1; //Invert x movement
            updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
        }
    }

    //Bouncing off walls
    if (willPathCrossRectangleSide(xyPosition, targetCoord, TopWallCollisionZone, BOTTOM)) {
        xyPosition = locationCrossingRectangleSide(xyPosition, targetCoord, TopWallCollisionZone, BOTTOM);
        directionVect.y *= -1; //Invert y movement
        updateBall((1-unusedFrametimeRatio)*frameTime, gameModel);
    }
    else if (willPathCrossRectangleSide(xyPosition, targetCoord, BottomWallCollisionZone, TOP)) { //Will bounce
        xyPosition = locationCrossingRectangleSide(xyPosition, targetCoord, BottomWallCollisionZone, TOP);
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