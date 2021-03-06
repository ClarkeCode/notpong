#include "pong_model.hpp"
#include "raylib.h"
#include "raylib_extensions.hpp"
#include "raymath.h"

using namespace extensions;

pong::Ball::Ball(float x, float y, float r, float s, float d)  : GeometryColours(Color{0,0,230,255}, Color{60,60,60,255}), xyPosition(Vector2{x,y}), radius(r), speed(s) {
    setDirection(d);
}

void pong::Ball::drawObject() {
    DrawCircle(xyPosition.x, xyPosition.y, radius, fillColour);
    DrawCircleLines(xyPosition.x, xyPosition.y, radius, lineColour);
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

    //Scoring
    if (CheckCollisionCircleRec(xyPosition, radius, gameModel.P1ScoreZone.getCollisionBox())) {
        gameModel.P2Score++;
        gameModel.canBallMove = false;
        xyPosition = RectangleGetCentre(Rectangle{0,0,gameModel.worldInfo->width, gameModel.worldInfo->height});
        setDirection();
    }
    else if (CheckCollisionCircleRec(xyPosition, radius, gameModel.P2ScoreZone.getCollisionBox())) {
        gameModel.P1Score++;
        gameModel.canBallMove = false;
        xyPosition = RectangleGetCentre(Rectangle{0,0,gameModel.worldInfo->width, gameModel.worldInfo->height});
        setDirection();
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
void pong::Ball::setDirection() { setDirection(DEG2RAD * GetRandomValue(0, 360)); }