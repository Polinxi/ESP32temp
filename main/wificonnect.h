/* Wifi connect
   TODO Usage:
       1. Declare the structure DHT11_t and set the Data PIN of DHT11
      2. Use getData() with the declated structure to get the values
      3. Check the returnad value if is ecual to DHT_OK you can get the
      values (temperature and humidity) from the structure.
      E. In case of error you can chech the error with DHT_errorHandle()
   Pol Paradell
   April 2018
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#ifndef WIFIC_H_
#define WIFIC_H_

#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "apps/sntp/sntp.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

//#include "sh2lib.h"

/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_WIFI_SSID CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS CONFIG_WIFI_PASSWORD

/* FreeRTOS event group to signal when we are connected & ready to make a request */
EventGroupHandle_t wifi_event_group;

esp_err_t event_handler(void *ctx, system_event_t *event);

int* initialise_wifi(void);

#endif
