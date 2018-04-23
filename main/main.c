/* ESP32temp main

   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "dht11.h" //library for DHT11

void DHT_task(void *pvParameter)
{
   printf("Starting DHT measurement...");
   //Configuration the DHT sensor to pin 4
   struct DHT11_t temp;
   temp.PIN = 4;

   int response;
   printf("DONE\n");
   while(1)
   {
     if ((response = getData(&temp))==DHT_OK){
       printf("Temperature= %dºC   Humidity= %d\n", temp.temperature, temp.humidity);
     } else {
       DHT_errorHandle(response);
     }
    vTaskDelay(3000 / portTICK_RATE_MS);
   }
}

void app_main()
{
    printf("ESP32temp project\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    vTaskDelay(1000 / portTICK_RATE_MS);
    xTaskCreate(&DHT_task, "DHT_task", 2048, NULL, 5, NULL);

}
