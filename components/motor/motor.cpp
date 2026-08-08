#include "motor.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include <algorithm>
#include <cmath>



Motor::Motor(const MotorConfig& config) : config_(config)
{    
    init();
}

Motor::~Motor(){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, config_.channelForward, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, config_.channelForward);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, config_.channelBackward, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, config_.channelBackward);
}

void Motor::init()
{
    gpio_reset_pin(config_.pinForward);
    gpio_reset_pin(config_.pinBackward);

    gpio_set_direction(config_.pinForward, GPIO_MODE_OUTPUT);
    gpio_set_direction(config_.pinBackward, GPIO_MODE_OUTPUT);

    gpio_set_level(config_.pinForward, 0);
    gpio_set_level(config_.pinBackward, 0);

    ledc_timer_config_t timer_config = {
        .speed_mode         = LEDC_LOW_SPEED_MODE,
        .duty_resolution    = LEDC_TIMER_8_BIT,
        .timer_num          = LEDC_TIMER_0,
        .freq_hz            = 1500,
        .clk_cfg            = LEDC_AUTO_CLK,
        .deconfigure        = false
    };
    ledc_timer_config(&timer_config);

    ledc_channel_config_t channel_config_forward = {
        .gpio_num       = config_.pinForward,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = config_.channelForward,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0,
        .sleep_mode     = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .flags = {
            .output_invert = 0
        },
        .deconfigure    = false
    };
    ledc_channel_config(&channel_config_forward);
    ledc_channel_config_t channel_config_backward = {
        .gpio_num       = config_.pinBackward,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = config_.channelBackward,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0,
        .sleep_mode     = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .flags = {
            .output_invert = 0
        },
        .deconfigure    = false
    };
    ledc_channel_config(&channel_config_backward);
}

void Motor::setPWM(float pwm)
{
    uint32_t duty = static_cast<uint32_t>(
        std::clamp(
            std::abs(pwm),
            0.0f,
            255.0f
        )
    );

    if(pwm > 0){
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward,
            0
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward
        );
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward,
            duty
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward
        );
    }
    else if(pwm < 0){
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward,
            0
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward
        );
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward,
            duty
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward
        );
    }
    else{
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward,
            0
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelForward
        );
        ledc_set_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward,
            0
        );
        ledc_update_duty(
            LEDC_LOW_SPEED_MODE,
            config_.channelBackward
        );
    }
}
