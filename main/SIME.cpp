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
        .pinIN1 = GPIO_NUM_10,
        .pinIN2 = GPIO_NUM_9,
        .pinPWM = GPIO_NUM_8,
        .channelPWM = LEDC_CHANNEL_0
    };
    Motor leftMotor(leftConfig);

    MotorConfig rightConfig = {
        .pinIN1 = GPIO_NUM_11,
        .pinIN2 = GPIO_NUM_12,
        .pinPWM = GPIO_NUM_13,
        .channelPWM = LEDC_CHANNEL_1
    };
    Motor rightMotor(rightConfig);

    //Left encoder setup
    BusConfig busConfig1 = {
        .port = I2C_NUM_0,
        .pinSDA = GPIO_NUM_2,
        .pinSCL = GPIO_NUM_1
    };
    i2cBus bus1(busConfig1);
    DeviceConfig enkoderConfig1 = {
        .deviceAddr = 0x36,
        .SCLfreq = 100000
    };
    AS5600 enkoderLeft(bus1, enkoderConfig1);
    //Right encoder setup
    BusConfig busConfig2 = {
        .port = I2C_NUM_1,
        .pinSDA = GPIO_NUM_6,
        .pinSCL = GPIO_NUM_5
    };
    i2cBus bus2(busConfig2);
    DeviceConfig enkoderConfig2 = {
        .deviceAddr = 0x36,
        .SCLfreq = 100000
    };
    AS5600 enkoderRight(bus2, enkoderConfig2);

    PIController leftPI(20.0f, 15.0f, 20.0f);
    PIController rightPI(20.0f, 15.0f, 20.0f);

    bus1.init();
    bus2.init();

    enkoderLeft.init();
    enkoderRight.init();
    
    float prevRadAngleLeft = enkoderLeft.readRadAngle();
    float prevRadAngleRight = enkoderRight.readRadAngle();
    float Kv = 16.94;
    TickType_t lastWakeTime = xTaskGetTickCount();
    while(true){
        float desAngVel = 4.0f;
        float feedforward = Kv * desAngVel;
        float radAngleLeft = enkoderLeft.readRadAngle();
        float radAngleRight = enkoderRight.readRadAngle();
        float angularVelLeft = -enkoderLeft.getAngularVel(prevRadAngleLeft, radAngleLeft);
        float angularVelRight = enkoderRight.getAngularVel(prevRadAngleRight, radAngleRight);
        
        
        float updateLeft = leftPI.update(desAngVel, angularVelLeft, 0.01f, feedforward);
        float updateRight = rightPI.update(desAngVel, angularVelRight, 0.01f, feedforward);
        float controlInputLeft = feedforward + updateLeft;
        float controlInputRight = feedforward + updateRight;
        leftMotor.setPWM(controlInputLeft);
        rightMotor.setPWM(controlInputRight);
        prevRadAngleLeft = radAngleLeft;
        prevRadAngleRight = radAngleRight;
        printf(
            "L: angle=%.3f vel=%.3f CI=%.3f | "
            "R: angle=%.3f vel=%.3f CI=%.3f\n",

            radAngleLeft,
            angularVelLeft,
            controlInputLeft,

            radAngleRight,
            angularVelRight,
            controlInputRight);

        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));

    }
    // while (true){
    //     leftMotor.setPWM(100);
    //     rightMotor.setPWM(100);
    //     printf("100\n");
    //     printf("Levo: %.2f, Desno: %.2f\n", enkoderLeft.readRadAngle(), enkoderRight.readRadAngle());
    //     vTaskDelay(pdMS_TO_TICKS(10));
    // }
}
