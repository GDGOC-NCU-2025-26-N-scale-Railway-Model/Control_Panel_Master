#ifndef CUSTOM_PROTOCOL_H
#define CUSTOM_PROTOCOL_H

#include <stdint.h>

/**
 * @brief Maximum length of the message payload.
 */
#define MSG_LENGTH 100

/**
 * @brief Structure representing the custom data protocol.
 * 
 * This structure is packed to ensure consistent byte alignment across different platforms.
 */
typedef struct __attribute__((packed)) {
    uint8_t send_by_id;       /**< Identifier of the sender */
    char msg[MSG_LENGTH];     /**< Message payload */
} test_data_t;


#endif // CUSTOM_PROTOCOL_H
