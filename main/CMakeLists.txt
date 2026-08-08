idf_component_register(SRCS "SIME.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES 
                        motor
                        i2c
                        encoder
                        speedControler)
