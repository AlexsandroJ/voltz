// mocks/CAN_config.h

#pragma once

// --- Mock dos tipos do FreeRTOS e ESP-IDF ---
// (Usamos void* ou int para simular handles)

#ifndef __cplusplus
typedef unsigned int uint32_t;
typedef int bool;
#define true 1
#define false 0
#else
#include <cstddef>
#include <cstdint>
#endif

// Mock de gpio_num_t (GPIOs do ESP32: 0 a 39)
typedef int gpio_num_t;
#define GPIO_NUM_0   0
#define GPIO_NUM_1   1
#define GPIO_NUM_2   2
// ... você pode definir mais se necessário
#define GPIO_NUM_4   4
#define GPIO_NUM_5   5
#define GPIO_NUM_32 32
#define GPIO_NUM_33 33

// Mock de FreeRTOS: filas e tarefas
typedef void* QueueHandle_t;
typedef void* TaskHandle_t;

// --- Fim dos mocks de tipos ---

/**
 * @brief CAN Node Bus speed
 */
typedef enum {
    CAN_SPEED_100KBPS = 100,    /**< 100 kBit/s */
    CAN_SPEED_125KBPS = 125,    /**< 125 kBit/s */
    CAN_SPEED_200KBPS = 200,    /**< 200 kBit/s */
    CAN_SPEED_250KBPS = 250,    /**< 250 kBit/s */
    CAN_SPEED_500KBPS = 500,    /**< 500 kBit/s */
    CAN_SPEED_800KBPS = 800,    /**< 800 kBit/s */
    CAN_SPEED_1000KBPS = 1000   /**< 1000 kBit/s */
} CAN_speed_t;

/**
 * @brief CAN configuration structure
 */
typedef struct {
    CAN_speed_t speed;          /**< CAN speed in kBit/s */
    gpio_num_t tx_pin_id;       /**< TX pin */
    gpio_num_t rx_pin_id;       /**< RX pin */
    QueueHandle_t rx_queue;     /**< FreeRTOS RX queue handle */
    QueueHandle_t tx_queue;     /**< FreeRTOS TX queue handle */
    TaskHandle_t tx_handle;     /**< TX task handle */
    TaskHandle_t rx_handle;     /**< RX task handle */
} CAN_device_t;

// Declaração da variável global CAN_cfg (definida no .cpp ou mock)
extern CAN_device_t CAN_cfg;

// Função auxiliar para inicializar CAN_cfg (para testes)
void initCANConfig();

// Função de validação
bool isValidCANConfig();