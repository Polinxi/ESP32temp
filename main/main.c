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
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "dht11.h" //library for DHT11

#include "wificonnect.h"
#include "http_post.h"
// function to read the DHT11 sensor and handle the errors
void DHT11_read(struct DHT11_t *in)
{
   int response = getData(in);
   if (response==DHT_OK){
     //Do something if the lecture is OK
   } else {
     //Handle the error
     DHT_errorHandle(response);
     in->temperature = -2;
     in->humidity = -2;
   }
}

/* FreeRTOS event group to signal when we are connected & ready to make a request */
// EventGroupHandle_t w ifi_event_group;

static const char *TAG = "ESP32_1";

void app_main(){
    ESP_LOGI(TAG, "Starting the project ESP tmemperature");

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

    ESP_ERROR_CHECK( nvs_flash_init() ); //Check if there are any error
    int* stauts = initialise_wifi(); //connect to the wifi

    /* Configuration */

    // DHT11 Configuration
    struct DHT11_t DTHsensor;
    DTHsensor.PIN = 4; //Set DHT11 data pin to pin 4

    while (1){ // Infinite loop
      /* Reading sensors */
      DHT11_read(&DTHsensor);

      /* Display the results to serial interface */
      ESP_LOGI(TAG, "Temperature=%dºC   Humidity=%d\n",
        DTHsensor.temperature, DTHsensor.humidity);

      http_post_send(TAG, "temperature",DTHsensor.temperature);//Send the information
      //vTaskDelay(300 / portTICK_RATE_MS);
      http_post_send(TAG, "humidity",DTHsensor.humidity);//Send the information

      vTaskDelay(3000 / portTICK_RATE_MS);
    }
}
