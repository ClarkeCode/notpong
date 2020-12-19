#include "pong_model.hpp"

pong::PongModel::PongModel(GameWorld& gw) {
    topBottomWallThickness = 10;
    MaxPaddleYPosition = 0 + topBottomWallThickness;
    MinPaddleYPosition = gw.height - topBottomWallThickness;
    
    paddleWidth = 20;
    paddleHeight = 60;
    paddleSpeed = 10;
    P1Paddle = Paddle(0 + paddleWidth/2.0, gw.height/2.0, paddleWidth, paddleHeight, paddleSpeed);
    P2Paddle = Paddle(gw.width - paddleWidth/2.0, gw.height/2.0, paddleWidth, paddleHeight, paddleSpeed);

    PongBall.xpos = gw.width/2.0;
    PongBall.ypos = gw.height/2.0;
    PongBall.speed = 20;
}