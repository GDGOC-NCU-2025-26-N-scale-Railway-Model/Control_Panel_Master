#include "comm.h"
#include "custom_protocol.h"
#include "esp_err.h"
#include "esp_now.h"
#include <string.h>

void comm_init(void){
    esp_err_t status = esp_now_init();
    if (status != ESP_OK){
        char* err = malloc(sizeof(esp_err_to_name(status)));
        strcpy_s(
            err, 
            sizeof(esp_err_to_name(status)), 
            esp_err_to_name(status));
        printf("The ESP-NOW is not initialized succefully. Error: %s", err);
        return;
    }
    printf("The ESP-NOW has been initialized successfully.");
    return;
}

/*TODO: Finish the test sending and de-initialization*/

esp_err_t send_test(const uint8_t *peer_mac, test_data_t *data){
    esp_err_t hold = 0x000;
    return hold;
}