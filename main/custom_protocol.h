#ifndef CUSTOM_PROTOCOL_H
#define CUSTOM_PROTOCOL_H

#include <stdint.h>

#define MSG_LENGTH 100

typedef struct __attribute__((packed)) {
    uint8_t send_by_id;
    char msg[MSG_LENGTH];
} test_data_t;


#endif