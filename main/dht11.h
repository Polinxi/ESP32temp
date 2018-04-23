/* DHT11 temperature sensor library
   Usage:
   		Set DHT PIN using  setDHTPin(pin) command
   		getFtemp(); this returns temperature in F
   Sam Johnston
   October 2016
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#ifndef DHT11_H_
#define DHT11_H_

/* Nedded libraaries for DHT11 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Status codes for DHT11 comunications
#define DHT_TIMEOUT_ERROR -2
#define DHT_CHECKSUM_ERROR -1
#define DHT_OK  0

//Data information for DHT11 sensor
struct DHT11_t {
  int temperature;
  int humidity;
  int PIN;
};

//Functions

// Internal function to start the comunications with DHT11
void sendStart(int PIN);

// fFunction to read the response of getData
void DHT_errorHandle(int response);

// To get the measurements
// the response is DHT_OK or
// in case of error DHT_TIMEOUT_ERROR or DHT_CHECKSUM_ERROR
// the values are in the input value
int getData(struct DHT11_t *type);

#endif
