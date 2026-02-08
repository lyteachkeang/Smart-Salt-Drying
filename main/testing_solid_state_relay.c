//tessting one ssr and read ADC
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "ssr_control.h"
// #include "voltage_sensor.h"

// void app_main(void) {
//     ssr_init();
//     voltage_sensor_init();

//     xTaskCreate(ssr_task, "ssr_task", 2048, NULL, 5, NULL);
//     xTaskCreate(voltage_task, "voltage_task", 4096, NULL, 5, NULL);
// }

//testing three ssr and read ADC
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssr_control.h"
#include "voltage_sensor.h"

void app_main(void) {
    ssr_init();
    voltage_sensor_init();

    xTaskCreate(ssr_task, "ssr_task", 2048, NULL, 5, NULL);
    xTaskCreate(voltage_task, "voltage_task", 4096, NULL, 5, NULL);
}
