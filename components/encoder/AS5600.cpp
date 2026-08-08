#include "AS5600.h"
#include <cmath>

AS5600::AS5600(i2cBus& bus, const DeviceConfig& deviceConfig) : device_(bus, deviceConfig){}

void AS5600::init(){
    device_.init();
}

uint16_t AS5600::readRawAngle(){
    uint8_t reg = 0x0C;
    uint8_t data[2];

    esp_err_t err = device_.transmitRecive(
        &reg,
        1,
        data,
        2
    );
    if(err != ESP_OK){
        printf("I2C Error: %s (%d)\n", esp_err_to_name(err), err);
        return 1;
    };
    uint16_t angle = ((data[0] << 8) | data[1]) & 0x0FFF;
    return angle;
}

float AS5600::raw2rad(uint16_t rawAngle){

    return static_cast<float>(rawAngle) * 2 * M_PI / 4096.0f;

}

float AS5600::readRadAngle(){
    
    return raw2rad(readRawAngle());

}

float AS5600::getAngularVel(float prevRadAngle, float radAngle){
    
    float deltaAngle = radAngle - prevRadAngle;

    if(deltaAngle > M_PI){
        deltaAngle -= 2.0f * M_PI;
    }
    else if(deltaAngle < -M_PI){
        deltaAngle += 2.0f * M_PI;
    }
    float angularVel = deltaAngle / 0.01f;
    filtAngularVel = filtAngularVel + alpha_ * (angularVel - filtAngularVel);
    return filtAngularVel;
}