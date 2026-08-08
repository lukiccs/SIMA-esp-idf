#include <stdio.h>
#include "motor.h"
#include "i2cDriver.h"
#include "AS5600.h"
#include "speedController.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"



extern "C" void app_main(){

    MotorConfig leftConfig = {
        .pinForward = GPIO_NUM_0,
        .pinBackward = GPIO_NUM_1,
        .channelForward = LEDC_CHANNEL_0,
        .channelBackward = LEDC_CHANNEL_1
    };
    Motor leftMotor(leftConfig);

    MotorConfig rightConfig = {
        .pinForward = GPIO_NUM_2,
        .pinBackward = GPIO_NUM_3,
        .channelForward = LEDC_CHANNEL_2,
        .channelBackward = LEDC_CHANNEL_3
    };
    Motor rightMotor(rightConfig);

    BusConfig busConfig = {
        .port = I2C_NUM_0,
        .pinSDA = GPIO_NUM_8,
        .pinSCL = GPIO_NUM_9
    };
    i2cBus bus(busConfig);

    DeviceConfig enkoderConfig = {
        .deviceAddr = 0x36,
        .SCLfreq = 100000
    };
    AS5600 enkoder(bus, enkoderConfig);

    PIController leftPI(20.0f, 15.0f, 20.0f);

    bus.init();

    enkoder.init();
    
    float prevRadAngle = enkoder.readRadAngle();
    float Kv = 16.94;
    TickType_t lastWakeTime = xTaskGetTickCount();
    while(true){
        float desAngVel = 6.0f;
        float feedforward = Kv * desAngVel;
        float radAngle = enkoder.readRadAngle();
        float angularVel = enkoder.getAngularVel(prevRadAngle, radAngle);
        
        
        float update = leftPI.update(desAngVel, angularVel, 0.01f, feedforward);
        float controlInput = feedforward + update;
        leftMotor.setPWM(controlInput);
        prevRadAngle = radAngle;
        printf("Rad Angle: %.3f, angular vel: %.3f, CI: %.3f\n", radAngle, angularVel, controlInput);
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));

    }

}
