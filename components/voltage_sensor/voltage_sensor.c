//testing one SSR and read ADC
// #include <stdio.h>
// #include "esp_adc/adc_oneshot.h"
// #include "esp_adc/adc_cali.h"
// #include "esp_adc/adc_cali_scheme.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// static adc_oneshot_unit_handle_t adc1_handle;
// static adc_cali_handle_t cali_handle;
// static bool cali_enabled = false;

// void voltage_sensor_init(void)
// {
//     // --- ADC setup ---
//     adc_oneshot_unit_init_cfg_t init_config = {
//         .unit_id = ADC_UNIT_1,
//     };
//     ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc1_handle));

//     adc_oneshot_chan_cfg_t chan_config = {
//         .bitwidth = ADC_BITWIDTH_DEFAULT,
//         .atten = ADC_ATTEN_DB_12,   // DB_11 is deprecated
//     };
//     ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &chan_config));

//     // --- Calibration setup ---
//     adc_cali_line_fitting_config_t cali_config = {
//         .unit_id = ADC_UNIT_1,
//         .atten = ADC_ATTEN_DB_12,
//         .bitwidth = ADC_BITWIDTH_DEFAULT,
//     };

//     if (adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle) == ESP_OK) {
//         cali_enabled = true;
//         printf("ADC calibration enabled.\n");
//     } else {
//         printf("ADC calibration not available, raw values only.\n");
//     }
// }

// void voltage_task(void *pvParameters)
// {
//     while (1) {
//         int raw = 0;
//         ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &raw));

//         if (cali_enabled) {
//             int voltage = 0;
//             ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cali_handle, raw, &voltage));
//             printf("Raw: %d, Voltage: %d mV\n", raw, voltage);
//         } else {
//             printf("Raw: %d\n", raw);
//         }

//         vTaskDelay(pdMS_TO_TICKS(1000)); // delay 1s
//     }
// }


//testing three Solid State relays and read output voltage

#include <stdio.h>
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static adc_oneshot_unit_handle_t adc1_handle;
static adc_cali_handle_t cali_handle;
static bool cali_enabled = false;

// Assign ADC channels for each SSR output sensor
#define SSR1_CH ADC_CHANNEL_6   // GPIO34
#define SSR2_CH ADC_CHANNEL_7   // GPIO35
#define SSR3_CH ADC_CHANNEL_4   // GPIO32

void voltage_sensor_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc1_handle));

    adc_oneshot_chan_cfg_t chan_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, SSR1_CH, &chan_config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, SSR2_CH, &chan_config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, SSR3_CH, &chan_config));

    adc_cali_line_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    if (adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle) == ESP_OK) {
        cali_enabled = true;
        printf("ADC calibration enabled.\n");
    } else {
        printf("ADC calibration not available, raw values only.\n");
    }
}

void voltage_task(void *pvParameters)
{
    while (1) {
        int raw1 = 0, raw2 = 0, raw3 = 0;

        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, SSR1_CH, &raw1));
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, SSR2_CH, &raw2));
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, SSR3_CH, &raw3));

        if (cali_enabled) {
            int v1 = 0, v2 = 0, v3 = 0;
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cali_handle, raw1, &v1));
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cali_handle, raw2, &v2));
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cali_handle, raw3, &v3));

            printf("SSR1: %d mV | SSR2: %d mV | SSR3: %d mV\n", v1, v2, v3);
        } else {
            printf("SSR1 raw: %d | SSR2 raw: %d | SSR3 raw: %d\n", raw1, raw2, raw3);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
