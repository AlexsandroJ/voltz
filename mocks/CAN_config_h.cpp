// mocks/CAN_config.cpp

#include "../lib/CAN_config.h"
#include <cstring>

// Definição da variável global CAN_cfg
CAN_device_t CAN_cfg;

// Inicializa a configuração com valores padrão
void initCANConfig() {
    CAN_cfg.speed = CAN_SPEED_500KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_5;
    CAN_cfg.rx_pin_id = GPIO_NUM_4;
    CAN_cfg.rx_queue = nullptr;
    CAN_cfg.tx_queue = nullptr;
    CAN_cfg.tx_handle = nullptr;
    CAN_cfg.rx_handle = nullptr;
}

// Valida a configuração
bool isValidCANConfig() {
    // Valida pinos (0 a 39)
    if (CAN_cfg.tx_pin_id < 0 || CAN_cfg.tx_pin_id > 39) return false;
    if (CAN_cfg.rx_pin_id < 0 || CAN_cfg.rx_pin_id > 39) return false;

    // Valida velocidade
    switch (CAN_cfg.speed) {
        case CAN_SPEED_100KBPS:
        case CAN_SPEED_125KBPS:
        case CAN_SPEED_200KBPS:
        case CAN_SPEED_250KBPS:
        case CAN_SPEED_500KBPS:
        case CAN_SPEED_800KBPS:
        case CAN_SPEED_1000KBPS:
            break;
        default:
            return false;
    }

    // As filas e tarefas podem ser nulas em teste
    return true;
}