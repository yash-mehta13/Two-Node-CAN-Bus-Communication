#include <Arduino.h>
#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define CAN_TX_GPIO GPIO_NUM_5
#define CAN_RX_GPIO GPIO_NUM_4

volatile uint32_t total_received = 0;
volatile uint32_t id_0x100_received = 0;

// Receive task: blocks until a CAN frame arrives, then processes it
void can_rx_task(void *arg) {
    twai_message_t rx_msg;
    while (1) {
        // Wait indefinitely for a message
        if (twai_receive(&rx_msg, portMAX_DELAY) == ESP_OK) {
            total_received++;
            if (rx_msg.extd && rx_msg.identifier == 0x100) {
                id_0x100_received++;
                // Process payload here (e.g., read sensor data)
            }
        }
    }
}

void setup() {
    Serial.begin(115200);

    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(
        CAN_TX_GPIO,
        CAN_RX_GPIO,
        TWAI_MODE_NO_ACK          // no external transceiver, loopback only
    );

    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
        Serial.println("TWAI driver install failed");
        return;
    }

    if (twai_start() != ESP_OK) {
        Serial.println("TWAI start failed");
        return;
    }

    // Create the receive task
    xTaskCreate(can_rx_task, "can_rx_task", 4096, NULL, 10, NULL);

    Serial.println("TWAI loopback test running");
}

void loop() {
    twai_message_t tx_msg;
    tx_msg.extd = 1;                    // extended 29-bit identifier
    tx_msg.identifier = 0x200;
    tx_msg.data_length_code = 8;
    for (int i = 0; i < 8; i++) {
        tx_msg.data[i] = i;
    }

    esp_err_t res = twai_transmit(&tx_msg, 0);  // non-blocking
    if (res == ESP_OK) {
        Serial.println("Sent frame with ID 0x200");
    } else {
        Serial.printf("TX failed: %s\n", esp_err_to_name(res));
    }

    Serial.printf("Total received: %u | ID 0x100 received: %u\n",
                  total_received, id_0x100_received);

    delay(2000);
}