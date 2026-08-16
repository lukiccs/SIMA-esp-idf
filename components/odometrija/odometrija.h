#pragma once

#include <cmath>

struct odometryCoor{
    float x;
    float y;
    float theta;
};

class Odometry{

    public:
        Odometry(float wheelRadius, float wheelBase);

        void update(float deltaAngleLeft, float deltaAngleRight);

        odometryCoor getCoor() const;

        float getX() const;
        float getY() const;
        float getTheta() const;

        void setPose(float x, float y, float theta);

    private:
            float wheelRadius_;
            float wheelBase_;

            float x_;
            float y_;
            float theta_;
};