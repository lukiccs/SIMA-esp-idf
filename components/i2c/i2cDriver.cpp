#include "i2cDriver.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"

i2cBus::i2cBus(const BusConfig& busConfig) : busConfig_(busConfig){}

i2cBus::~i2cBus(){
    if(busHandle_ != nullptr){
        ESP_ERROR_CHECK(i2c_del_master_bus(busHandle_));
    }
}

void i2cBus::init(){
    if(busHandle_ != nullptr){
        return;
    };
    initBus();
}

void i2cBus::initBus(){
    i2c_master_bus_config_t i2c_mst_config = {
        .i2c_port          = busConfig_.port,
        .sda_io_num        = busConfig_.pinSDA,
        .scl_io_num        = busConfig_.pinSCL,
        .clk_source        = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority     = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false
        }
    };
    // i2c_mst_config.flags.enable_internal_pullup = true;
    // i2c_mst_config.flags.allow_pd = false;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &busHandle_));
}

i2c_master_bus_handle_t i2cBus::getHandle() const{
    return busHandle_;
}


//DEVICE SETUP
i2cDevice::i2cDevice(i2cBus& bus, const DeviceConfig& deviceConfig) : bus_(bus), deviceConfig_(deviceConfig){};

i2cDevice::~i2cDevice(){
    if(deviceHandle_ != nullptr){
        ESP_ERROR_CHECK(i2c_master_bus_rm_device(deviceHandle_));
    };
}

void i2cDevice::init(){
    if(deviceHandle_ != nullptr){
        return;
    };
    initDevice();
}

void i2cDevice::initDevice() {
    i2c_device_config_t dev_cfg = {
        .dev_addr_length =      I2C_ADDR_BIT_LEN_7,
        .device_address =       deviceConfig_.deviceAddr,
        .scl_speed_hz =         deviceConfig_.SCLfreq,
        .scl_wait_us =          0,
        .flags = {
            .disable_ack_check = 0
        }
    };
    // dev_cfg.flags.disable_ack_check = 0;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_.getHandle(), &dev_cfg, &deviceHandle_));
    printf("Device handle = %p\n", deviceHandle_);
}

esp_err_t i2cDevice::transmitRecive(
    const uint8_t* txData,
    size_t txLenght,
    uint8_t* rxData,
    size_t rxLenght,
    int timeoutMS
){
    return i2c_master_transmit_receive(
        deviceHandle_,
        txData,
        txLenght,
        rxData,
        rxLenght,
        timeoutMS
    );
}

esp_err_t i2cDevice::transmit(
    const uint8_t* data,
    size_t length,
    int timeoutMs
)
{
    return i2c_master_transmit(
        deviceHandle_,
        data,
        length,
        timeoutMs
    );
}

esp_err_t i2cDevice::receive(
    uint8_t* data,
    size_t length,
    int timeoutMs
)
{
    return i2c_master_receive(
        deviceHandle_,
        data,
        length,
        timeoutMs
    );
}