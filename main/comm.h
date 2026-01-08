#ifndef COMM_H
#define COMM_H

/*Here we used preprocessor to add a initializer list.*/

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

#define SLAVE_MACS {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define PEER_LIST { \
    {SLAVE_MACS, 1} \
=======
#define PEER_LIST { \
    {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1} \
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======
#define PEER_LIST { \
    {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 1} \
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======

#define SLAVE_MACS {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define PEER_LIST { \
    {SLAVE_MACS, 1} \
>>>>>>> 31ff734 (feat: Finish send testing code)
}

#define PEER_NUM 1

#define ESPNOW_WIFI_MODE    WIFI_MODE_STA
#define ESPNOW_WIFI_IF      ESP_IF_WIFI_STA


<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "esp_err.h"
#include "custom_protocol.h"
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======
#include "esp_err.h"
#include "custom_protocol.h"
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======
>>>>>>> 31ff734 (feat: Finish send testing code)
#include "esp_now.h"
#include <stdint.h>

typedef struct{
    uint8_t mac[6];
    int channel;
} peer_t;

typedef struct {

} on_data_sent_cb;

void wifi_init(void);
void comm_init(void);
void send_task(void *pvParameter);
void comm_peer_setup(void);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
esp_err_t send_test(const uint8_t *peer_addr, test_data_t *data);
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======
esp_err_t send_test(const uint8_t *peer_addr, test_data_t *data);
>>>>>>> 0877032 (feat: Finish the initialization functions partially)
=======
>>>>>>> 31ff734 (feat: Finish send testing code)
void comm_deinit(peer_t *peers);
void on_data_sent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif