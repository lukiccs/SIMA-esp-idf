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
        .pinIN1 = GPIO_NUM_25,
        .pinIN2 = GPIO_NUM_26,
        .pinPWM = GPIO_NUM_27,
        .channelPWM = LEDC_CHANNEL_0
    };
    Motor leftMotor(leftConfig);

    MotorConfig rightConfig = {
        .pinIN1 = GPIO_NUM_32,
        .pinIN2 = GPIO_NUM_33,
        .pinPWM = GPIO_NUM_14,
        .channelPWM = LEDC_CHANNEL_1
    };
    Motor rightMotor(rightConfig);

    // BusConfig busConfig = {
    //     .port = I2C_NUM_0,
    //     .pinSDA = GPIO_NUM_21,
    //     .pinSCL = GPIO_NUM_22
    // };
    // i2cBus bus(busConfig);

    // DeviceConfig enkoderConfig = {
    //     .deviceAddr = 0x36,
    //     .SCLfreq = 100000
    // };
    // AS5600 enkoder(bus, enkoderConfig);

    // PIController leftPI(20.0f, 15.0f, 20.0f);

    // bus.init();

    // enkoder.init();
    
    // float prevRadAngle = enkoder.readRadAngle();
    // float Kv = 16.94;
    // TickType_t lastWakeTime = xTaskGetTickCount();
    // while(true){
    //     float desAngVel = 6.0f;
    //     float feedforward = Kv * desAngVel;
    //     float radAngle = enkoder.readRadAngle();
    //     float angularVel = enkoder.getAngularVel(prevRadAngle, radAngle);
        
        
    //     float update = leftPI.update(desAngVel, angularVel, 0.01f, feedforward);
    //     float controlInput = feedforward + update;
    //     leftMotor.setPWM(controlInput);
    //     prevRadAngle = radAngle;
    //     printf("Rad Angle: %.3f, angular vel: %.3f, CI: %.3f\n", radAngle, angularVel, controlInput);
    //     vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(10));

    // }
    // leftMotor.setPWM(100);
    while (true){
        leftMotor.setPWM(100);
        rightMotor.setPWM(100);
        printf("100\n");

        vTaskDelay(pdMS_TO_TICKS(3000));

        leftMotor.setPWM(150);
        rightMotor.setPWM(150);
        printf("150\n");

        vTaskDelay(pdMS_TO_TICKS(3000));

        leftMotor.setPWM(200);
        rightMotor.setPWM(200);
        printf("200\n");

        vTaskDelay(pdMS_TO_TICKS(3000));

        leftMotor.setPWM(0);
        rightMotor.setPWM(0);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}



// extern "C" void app_main()
// {
//     // LEVI MOTOR
//     gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT); // AIN1
//     gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT); // AIN2
//     gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT); // PWMA

//     // DESNI MOTOR
//     gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT); // BIN1
//     gpio_set_direction(GPIO_NUM_33, GPIO_MODE_OUTPUT); // BIN2
//     gpio_set_direction(GPIO_NUM_14, GPIO_MODE_OUTPUT); // PWMB

//     // Početno stanje
//     gpio_set_level(GPIO_NUM_25, 0);
//     gpio_set_level(GPIO_NUM_26, 0);
//     gpio_set_level(GPIO_NUM_27, 0);

//     gpio_set_level(GPIO_NUM_32, 0);
//     gpio_set_level(GPIO_NUM_33, 0);
//     gpio_set_level(GPIO_NUM_14, 0);

//     while (true)
//     {
//         printf("FORWARD\n");

//         // Levi
//         gpio_set_level(GPIO_NUM_25, 1); // AIN1
//         gpio_set_level(GPIO_NUM_26, 0); // AIN2
//         gpio_set_level(GPIO_NUM_27, 1); // PWMA

//         // Desni
//         gpio_set_level(GPIO_NUM_32, 1); // BIN1
//         gpio_set_level(GPIO_NUM_33, 0); // BIN2
//         gpio_set_level(GPIO_NUM_14, 1); // PWMB

//         vTaskDelay(pdMS_TO_TICKS(3000));

//         printf("STOP\n");

//         gpio_set_level(GPIO_NUM_25, 0);
//         gpio_set_level(GPIO_NUM_26, 0);
//         gpio_set_level(GPIO_NUM_27, 0);

//         gpio_set_level(GPIO_NUM_32, 0);
//         gpio_set_level(GPIO_NUM_33, 0);
//         gpio_set_level(GPIO_NUM_14, 0);

//         vTaskDelay(pdMS_TO_TICKS(3000));

//         printf("BACKWARD\n");

//         // Levi
//         gpio_set_level(GPIO_NUM_25, 0);
//         gpio_set_level(GPIO_NUM_26, 1);
//         gpio_set_level(GPIO_NUM_27, 1);

//         // Desni
//         gpio_set_level(GPIO_NUM_32, 0);
//         gpio_set_level(GPIO_NUM_33, 1);
//         gpio_set_level(GPIO_NUM_14, 1);

//         vTaskDelay(pdMS_TO_TICKS(3000));

//         printf("STOP\n");

//         gpio_set_level(GPIO_NUM_25, 0);
//         gpio_set_level(GPIO_NUM_26, 0);
//         gpio_set_level(GPIO_NUM_27, 0);

//         gpio_set_level(GPIO_NUM_32, 0);
//         gpio_set_level(GPIO_NUM_33, 0);
//         gpio_set_level(GPIO_NUM_14, 0);

//         vTaskDelay(pdMS_TO_TICKS(3000));
//     }
// }