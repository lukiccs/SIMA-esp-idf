#pragma once

class PIController{

    public:
        PIController(float Kp, float Ki, float Kaw);

        float update(float ref, float meas, float dt, float feedforward);

        void reset();

    private:
        float Kp_;
        float Ki_;
        float Kaw_;

        float integral_ = 0.0f;
};