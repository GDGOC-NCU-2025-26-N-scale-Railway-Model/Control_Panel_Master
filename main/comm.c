#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h" /* Required for FreeRTOS headers */
#include "freertos/semphr.h"
#include "freertos/timers.h"

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_err.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi_types_generic.h"

#include "comm.h"

#define MAC_LEN 6

static const char *TAG = "comm";

/* -------------------------------------------------------------------------- */
/*                              Helper Functions                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize the WiFi driver in Station mode.
 */
void wifi_init(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(ESPNOW_WIFI_MODE));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(0x0, WIFI_SECOND_CHAN_NONE));
}

/* -------------------------------------------------------------------------- */
/*                              Callbacks                                     */
/* -------------------------------------------------------------------------- */

/**
 * @brief Callback function for ESP-NOW sending status.
 */
void on_data_sent(const esp_now_send_info_t *info, esp_now_send_status_t status) {
    ESP_LOGI(TAG, "Last packet send status: %s", status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

/* -------------------------------------------------------------------------- */
/*                           Initialization Functions                         */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize the Communication Module (WiFi + ESP-NOW).
 */
void comm_init(void) {
    /* 1. Initialize WiFi first */
    wifi_init();

    /* 2. Initialize ESP-NOW */
    ESP_ERROR_CHECK(esp_now_init());

    /* 3. Register Send Callback */
    ESP_ERROR_CHECK(esp_now_register_send_cb(on_data_sent));
    
    printf("The ESP-NOW has been initialized successfully.\n");
}

/**
 * @brief Configure and add peers to the ESP-NOW peer list.
 */
void comm_peer_setup(void) {
    peer_t peers[] = PEER_LIST;
    
    for (int i = 0; i < PEER_NUM; i++) {
        esp_now_peer_info_t peer_handler;
        memset(&peer_handler, 0, sizeof(esp_now_peer_info_t));
        
        /* Note: Arrays cannot be directly assigned, memcpy is required */
        memcpy(peer_handler.peer_addr, peers[i].mac, MAC_LEN);
        
        peer_handler.channel = peers[i].channel;
        peer_handler.ifidx = WIFI_IF_STA; /* ESP-NOW usually works on STA interface */
        peer_handler.encrypt = false;
        
        ESP_ERROR_CHECK(esp_now_add_peer(&peer_handler));
    }
}

/* -------------------------------------------------------------------------- */
/*                                Tasks                                       */
/* -------------------------------------------------------------------------- */

/**
 * @brief Task to broadcast a test message periodically.
 * TODO: Verify test logic and timing.
 */
void send_task(void *pvParameter) {
    const char *msg = "ESP-NOW string testing.";
    uint8_t broadcast_mac[6] = SLAVE_MACS;
    
    while (1) {
        esp_err_t res = esp_now_send(broadcast_mac, (uint8_t *)msg, strlen(msg));
        
        if (res != ESP_OK) {
            ESP_LOGE(TAG, "Send error: 0x%x", res);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* -------------------------------------------------------------------------- */
/*                             De-initialization                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Clean up peers and deinitialize ESP-NOW.
 */
void comm_deinit(peer_t *peers) {
    for (uint8_t i = 0; i < PEER_NUM; i++) {
        ESP_ERROR_CHECK(esp_now_del_peer(peers[i].mac));
    }

    ESP_ERROR_CHECK(esp_now_deinit());
}
