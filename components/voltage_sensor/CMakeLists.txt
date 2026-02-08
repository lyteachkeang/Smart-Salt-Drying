idf_component_register(
    SRCS "voltage_sensor.c"
    INCLUDE_DIRS "."
    REQUIRES esp_adc
    PRIV_REQUIRES driver freertos
)
