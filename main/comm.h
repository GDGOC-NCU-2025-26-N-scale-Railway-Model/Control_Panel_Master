#ifndef COMM_H
#define COMM_H

#include "esp_err.h"
#include "custom_protocol.h"
#include <stdint.h>

void comm_init(void);
esp_err_t send_test(const uint8_t *peer_mac, test_data_t *data);
void comm_deinit(void);

#endif