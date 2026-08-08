#pragma once
#include "driver/i2c_master.h"
#include "driver/gpio.h"

struct BusConfig{
    i2c_port_num_t port;
    gpio_num_t pinSDA;
    gpio_num_t pinSCL;
    
};

struct DeviceConfig{
    uint16_t deviceAddr;
    uint32_t SCLfreq;
};

class i2cBus{

    public:
        explicit i2cBus(const BusConfig& busConfig);

        ~i2cBus();

        void init();

        i2c_master_bus_handle_t getHandle() const;
    private:
        void initBus();
        i2c_master_bus_handle_t busHandle_ = nullptr;
        BusConfig busConfig_;

};

class i2cDevice{

    public:
        explicit i2cDevice(i2cBus& bus, const DeviceConfig& deviceConfig);// dodati da je potreban bus handle za konstrukciju
        
        ~i2cDevice();

        void init();

        esp_err_t transmitRecive(
            const uint8_t* txData,
            size_t txLenght,
            uint8_t* rxData,
            size_t rxLenght,
            int timeoutMS = 10
        );
        esp_err_t transmit(
            const uint8_t* data,
            size_t length,
            int timeoutMs = 10
        );
        esp_err_t receive(
            uint8_t* data,
            size_t length,
            int timeoutMs = 10
        );
    private:
        i2cBus& bus_;
        void initDevice();
        i2c_master_dev_handle_t deviceHandle_ = nullptr;
        DeviceConfig deviceConfig_;
};
