idf_component_register(SRCS "i2cDriver.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES 
                        esp_driver_i2c
                        esp_driver_gpio)
