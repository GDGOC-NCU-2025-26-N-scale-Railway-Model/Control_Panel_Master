#include "comm.h"
#include "esp_err.h"
#include "esp_now.h"
#include "esp_wifi_types_generic.h"
#include "esp_netif.h" /*Possible missing included heading is reported inside this, but building is still working.*/
#include "esp_event.h"
#include "esp_wifi.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_log.h"

#define MAC_LEN 6

const char *TAG = "comm:";

void wifi_init(void){
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(ESPNOW_WIFI_MODE));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(0x0, WIFI_SECOND_CHAN_NONE));
}

void comm_init(void){

    wifi_init();

    ESP_ERROR_CHECK(esp_now_init());

    ESP_ERROR_CHECK(esp_now_register_send_cb(on_data_sent));
    printf("The ESP-NOW has been initialized successfully.");    
    return;
}

void on_data_sent(const esp_now_send_info_t *info, esp_now_send_status_t status){
        ESP_LOGI(TAG, "Last packet send status: %s", status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

}


void comm_peer_setup(void){
    peer_t peers[] = PEER_LIST;
    for(int i = 0; i < PEER_NUM; i++){
        esp_now_peer_info_t peer_handler;
        memset(&peer_handler, 0, sizeof(esp_now_peer_info_t));
        memcpy(peer_handler.peer_addr, peers[i].mac, MAC_LEN); 
        /*Note: List can not be directly assigned, memcpy is required*/
        peer_handler.channel = peers[i].channel;
        peer_handler.ifidx = WIFI_IF_STA;
        peer_handler.encrypt = false;
        
        ESP_ERROR_CHECK(esp_now_add_peer(&peer_handler));
    }
}

/*TODO: Finish the test*/

void send_task(void *pvParameter){
    const char *msg = "ESP-NOW string testing.";
    uint8_t broadcast_mac[6] = SLAVE_MACS;
    
    while(1) {
        esp_err_t res = esp_now_send(broadcast_mac, (uint8_t *)msg, strlen(msg));
        if (res != ESP_OK) {
            ESP_LOGE(TAG, "Send error: 0x%x", res);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void comm_deinit(peer_t *peers){
    for(uint8_t i = 0; i < PEER_NUM; i++){
        ESP_ERROR_CHECK(esp_now_del_peer(peers[i].mac));
    }

    ESP_ERROR_CHECK(esp_now_deinit());
}