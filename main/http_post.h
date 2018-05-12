/* Library to send via POST the values to influx */
#ifndef HTTP_POST_H_
#define HTTP_POST_H_

#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "192.168.22.30"
#define WEB_PORT "8086"
#define WEB_URL "http://192.168.22.30:8086/write?db=casa"

//static char *MESSAGE = "temperature,machine=test value=31";
//function to send the post message
void http_post_send(char *name, char *type, double value);

#endif
