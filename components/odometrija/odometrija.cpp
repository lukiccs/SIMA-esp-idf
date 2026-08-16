#include "odometrija.h"

Odometry::Odometry(float wheelRadius, float wheelBase) : wheelRadius_(wheelRadius), wheelBase_(wheelBase), x_(0.0f), y_(0.0f), theta_(0.0f){}

void Odometry::update(float deltaAngleLeft, float deltaAngleRight){

    if (deltaAngleLeft > M_PI) {
        deltaAngleLeft -= 2.0f * M_PI;
    }
    else if (deltaAngleLeft < M_PI){
        deltaAngleLeft += 2.0f * M_PI;
    }

    if (deltaAngleRight > M_PI) {
        deltaAngleRight -= 2.0f * M_PI;
    }
    else if (deltaAngleRight < M_PI){
        deltaAngleRight += 2.0f * M_PI;
    }

    float deltaSLeft = wheelRadius_ * deltaAngleLeft;
    float deltaSRight = wheelRadius_ * deltaAngleRight;

    float deltaS = (deltaSLeft + deltaSRight) / 2.0f;

    float deltaTheta = (deltaSRight - deltaSLeft) / wheelBase_;

    float thetaMid = theta_ + deltaTheta / 2.0f;

    x_ += deltaS * std::cos(thetaMid);
    y_ += deltaS * std::sin(thetaMid);
    theta_ += deltaTheta;

}

odometryCoor Odometry::getCoor() const{
    return {x_, y_, theta_};
}


float Odometry::getX() const{
    return x_;
}
float Odometry::getY() const{
    return y_;
}
float Odometry::getTheta() const{
    return theta_;
}

void Odometry::setPose(float x, float y, float theta){
    x_ = x;
    y_ = y;
    theta_ = theta;
}