#include "speedController.h"
#include <algorithm>

PIController::PIController(float Kp, float Ki, float Kaw) : Kp_(Kp), Ki_(Ki), Kaw_(Kaw){}


float PIController::update(float ref, float meas, float dt, float feedforward)
{

    float err = ref - meas;
    // integral_ += err * dt;
    
    float unsatCI = feedforward + Kp_ * err + Ki_* integral_;
    float satCI = std::clamp(unsatCI, -255.0f, 255.0f);

    integral_ += (err + Kaw_ * (satCI - unsatCI)) * dt;
    return satCI;
}

void PIController::reset(){
    integral_ = 0.0f;
}