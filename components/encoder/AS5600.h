#pragma once

#include "i2cDriver.h"

class AS5600{

    public:
        explicit AS5600(i2cBus& bus, const DeviceConfig& deviceConfig);

        void init();
        uint16_t readRawAngle();
        float readRadAngle();
        static float raw2rad(uint16_t rawAngle);
        float getAngularVel(float prevRadAngle, float radAngle);

        private:
            i2cDevice device_;
            float filtAngularVel = 0.0f;
            static constexpr float alpha_ = 0.3f;
};