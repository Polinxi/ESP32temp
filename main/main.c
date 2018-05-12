/* ESP32temp main

   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

const char *TAG = "ESP32_1"; //Ientifier

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "wificonnect.h"

/* The HTTP/2 server to connect to */
#define HTTP2_SERVER_URI  "http://192.168.22.30:8086"

void app_main()
{

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    ESP_LOGI(TAG, "silicon revision %d, ", chip_info.revision);

    ESP_LOGI(TAG, "%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    //Starting connection to wifi
    ESP_ERROR_CHECK( nvs_flash_init() ); //Check if there are any error

    initialise_wifi(); //connect to the wifi

    /* Waiting for connection */
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,false, true, portMAX_DELAY);

    /* HTTP2: one connection multiple requests. Do the TLS/TCP connection first */
    printf("Connecting to server\n");
    struct sh2lib_handle hd;
    if (sh2lib_connect(&hd, HTTP2_SERVER_URI) != 0) {
        printf("Failed to connect\n");
        return;
    }
    printf("Connection done\n");

}
