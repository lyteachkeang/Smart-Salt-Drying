// testing one ssr and read ADC
// #include "driver/gpio.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #define SSR_GPIO 18

// void ssr_init(void) {
//     gpio_config_t io_conf = {
//         .pin_bit_mask = (1ULL << SSR_GPIO),
//         .mode = GPIO_MODE_OUTPUT,
//         .pull_up_en = GPIO_PULLUP_DISABLE,
//         .pull_down_en = GPIO_PULLDOWN_DISABLE,
//         .intr_type = GPIO_INTR_DISABLE
//     };
//     gpio_config(&io_conf);
// }

// void ssr_task(void *pvParameter) {
//     while (1) {
//         gpio_set_level(SSR_GPIO, 1); // SSR ON
//         vTaskDelay(pdMS_TO_TICKS(2000));
//         gpio_set_level(SSR_GPIO, 0); // SSR OFF
//         vTaskDelay(pdMS_TO_TICKS(2000));
//     }
// }


//testing three Solid state relays and read output voltage


#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SSR1_GPIO 18
#define SSR2_GPIO 19
#define SSR3_GPIO 21

void ssr_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SSR1_GPIO) | (1ULL << SSR2_GPIO) | (1ULL << SSR3_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void ssr_task(void *pvParameter) {
    while (1) {
        gpio_set_level(SSR1_GPIO, 1);
        gpio_set_level(SSR2_GPIO, 0);
        gpio_set_level(SSR3_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        gpio_set_level(SSR1_GPIO, 0);
        gpio_set_level(SSR2_GPIO, 1);
        gpio_set_level(SSR3_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        gpio_set_level(SSR1_GPIO, 0);
        gpio_set_level(SSR2_GPIO, 0);
        gpio_set_level(SSR3_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
