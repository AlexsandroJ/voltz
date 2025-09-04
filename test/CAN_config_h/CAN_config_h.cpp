// tests/test_can_config.cpp
#include "../mocks/CAN_config_h.cpp"
#include <unity.h>

// Teste: Verifica se a configuração padrão é válida
void test_can_config_default_valid() {
    initCANConfig();
    TEST_ASSERT_TRUE(isValidCANConfig());
    TEST_ASSERT_EQUAL(CAN_SPEED_500KBPS, CAN_cfg.speed);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, CAN_cfg.tx_pin_id);
    TEST_ASSERT_EQUAL(GPIO_NUM_4, CAN_cfg.rx_pin_id);
}

// Teste: Velocidade válida
void test_can_config_valid_speed() {
    initCANConfig();
    CAN_cfg.speed = CAN_SPEED_125KBPS;
    TEST_ASSERT_TRUE(isValidCANConfig());

    CAN_cfg.speed = CAN_SPEED_1000KBPS;
    TEST_ASSERT_TRUE(isValidCANConfig());
}

// Teste: Velocidade inválida
void test_can_config_invalid_speed() {
    initCANConfig();
    CAN_cfg.speed = (CAN_speed_t)999; // Inválido
    TEST_ASSERT_FALSE(isValidCANConfig());
}

// Teste: Pino TX inválido
void test_can_config_invalid_tx_pin() {
    initCANConfig();
    CAN_cfg.tx_pin_id = -1;
    TEST_ASSERT_FALSE(isValidCANConfig());

    CAN_cfg.tx_pin_id = 100;
    TEST_ASSERT_FALSE(isValidCANConfig());
}

// Teste: Pino RX inválido
void test_can_config_invalid_rx_pin() {
    initCANConfig();
    CAN_cfg.rx_pin_id = 40;
    TEST_ASSERT_FALSE(isValidCANConfig());
}

// Teste: Configuração personalizada
void test_can_config_custom_setup() {
    initCANConfig();
    CAN_cfg.speed = CAN_SPEED_250KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_32;
    CAN_cfg.rx_pin_id = GPIO_NUM_33;

    TEST_ASSERT_TRUE(isValidCANConfig());
    TEST_ASSERT_EQUAL(CAN_SPEED_250KBPS, CAN_cfg.speed);
    TEST_ASSERT_EQUAL(GPIO_NUM_32, CAN_cfg.tx_pin_id);
    TEST_ASSERT_EQUAL(GPIO_NUM_33, CAN_cfg.rx_pin_id);
}

// Teste: Pode usar null para filas e tarefas (simulado)
void test_can_config_null_handles() {
    initCANConfig();
    CAN_cfg.rx_queue = nullptr;
    CAN_cfg.tx_queue = nullptr;
    CAN_cfg.rx_handle = nullptr;
    CAN_cfg.tx_handle = nullptr;

    TEST_ASSERT_TRUE(isValidCANConfig()); // OK em teste
}
