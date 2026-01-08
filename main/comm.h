#ifndef COMM_H
#define COMM_H

/*Here we used preprocessor to add a initializer list.*/


#define SLAVE_MACS {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
#define PEER_LIST { \
    {SLAVE_MACS, 1} \
}

#define PEER_NUM 1

#define ESPNOW_WIFI_MODE    WIFI_MODE_STA
#define ESPNOW_WIFI_IF      ESP_IF_WIFI_STA


#include "esp_now.h"
#include <stdint.h>

typedef struct{
    uint8_t mac[6];
    int channel;
} peer_t;

void wifi_init(void);
void comm_init(void);
void send_task(void *pvParameter);
void comm_peer_setup(void);
void comm_deinit(peer_t *peers);
void on_data_sent(const esp_now_send_info_t *info, esp_now_send_status_t status);

#endif