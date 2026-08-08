#pragma once
#include "driver/ledc.h"
#include "driver/gpio.h"

struct MotorConfig{
    gpio_num_t pinForward;
    gpio_num_t pinBackward;
    ledc_channel_t channelForward;
    ledc_channel_t channelBackward;
};


class Motor{

    public:
        explicit Motor(const MotorConfig& config);
        
        ~Motor();

        void setPWM(float pwm);

    private:
        void init();
        MotorConfig config_;
};