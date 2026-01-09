#ifndef COMM_H
#define COMM_H

#include <stdint.h>
#include "esp_now.h"

/* -------------------------------------------------------------------------- */
/*                                   Macros                                   */
/* -------------------------------------------------------------------------- */

/**
 * @brief MAC address of the slave device.
 */
#define SLAVE_MACS {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

/**
 * @brief Initialization list for peers.
 * Format: {MAC_ADDRESS, CHANNEL}
 */
#define PEER_LIST { \
    {SLAVE_MACS, 1} \
}

/**
 * @brief Number of peers defined in PEER_LIST.
 */
#define PEER_NUM 1

/**
 * @brief WiFi mode and interface configuration for ESP-NOW.
 */
#define ESPNOW_WIFI_MODE    WIFI_MODE_STA
#define ESPNOW_WIFI_IF      ESP_IF_WIFI_STA

/* -------------------------------------------------------------------------- */
/*                                 Data Types                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Structure to hold peer information.
 */
typedef struct {
    uint8_t mac[6]; /**< Peer MAC address */
    int channel;    /**< WiFi channel for the peer */
} peer_t;

/* -------------------------------------------------------------------------- */
/*                            Function Prototypes                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize the WiFi stack in Station mode.
 */
void wifi_init(void);

/**
 * @brief Initialize the ESP-NOW communication protocol.
 * 
 * This function initializes WiFi, ESP-NOW, and registers the send callback.
 */
void comm_init(void);

/**
 * @brief Register peers for ESP-NOW communication.
 * 
 * Iterates through the predefined PEER_LIST and adds them to the ESP-NOW peer list.
 */
void comm_peer_setup(void);

/**
 * @brief FreeRTOS task to send test data via ESP-NOW.
 * 
 * @param pvParameter Task parameter (unused).
 */
void send_task(void *pvParameter);

/**
 * @brief Deinitialize ESP-NOW and remove all peers.
 * 
 * @param peers Array of peer_t structures to remove.
 */
void comm_deinit(peer_t *peers);

/**
 * @brief Callback function triggered after an ESP-NOW packet is sent.
 * 
 * @param info Information about the sent packet.
 * @param status Status of the transmission (Success/Fail).
 */
void on_data_sent(const esp_now_send_info_t *info, esp_now_send_status_t status);

#endif // COMM_H
