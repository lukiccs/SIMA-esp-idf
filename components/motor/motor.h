#pragma once
#include "driver/ledc.h"
#include "driver/gpio.h"

struct MotorConfig{
    gpio_num_t pinIN1;
    gpio_num_t pinIN2;
    gpio_num_t pinPWM;
    ledc_channel_t channelPWM;
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