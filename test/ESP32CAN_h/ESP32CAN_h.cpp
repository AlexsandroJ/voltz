// tests/test_esp32can.cpp
#include "../mocks/ESP32CAN_h.cpp"
#include <unity.h>

// Função auxiliar para comparar duas mensagens CAN
void assertCANMessagesEqual(const CAN_message_t& expected, const CAN_message_t& actual) {
    TEST_ASSERT_EQUAL(expected.id, actual.id);
    TEST_ASSERT_EQUAL(expected.ext, actual.ext);
    TEST_ASSERT_EQUAL(expected.rtr, actual.rtr);
    TEST_ASSERT_EQUAL(expected.len, actual.len);
    for (int i = 0; i < expected.len; i++) {
        TEST_ASSERT_EQUAL(expected.buf[i], actual.buf[i]);
    }
}

// Teste: Inicialização com bit rate válido
void test_ESP32CAN_begin() {
    int result = ESP32CANMock::begin(500000);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_TRUE(ESP32CANMock::isInitialized);
    TEST_ASSERT_EQUAL(500000, ESP32CANMock::bitrate);
}

// Teste: Inicialização com bit rate inválido
void test_ESP32CAN_begin_invalid_baudrate() {
    int result = ESP32CANMock::begin(0);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_FALSE(ESP32CANMock::isInitialized);
}

// Teste: Envio e recebimento de mensagem (loopback simulado)
void test_ESP32CAN_send_receive() {
    ESP32CANMock::begin(250000);

    CAN_message_t sentMsg;
    sentMsg.id = 0x123;
    sentMsg.ext = 1;  // ID estendido
    sentMsg.rtr = 0;
    sentMsg.len = 4;
    sentMsg.buf[0] = 0xDE;
    sentMsg.buf[1] = 0xAD;
    sentMsg.buf[2] = 0xBE;
    sentMsg.buf[3] = 0xEF;

    bool sent = ESP32CANMock::write(sentMsg);
    TEST_ASSERT_TRUE(sent);

    TEST_ASSERT_EQUAL(1, ESP32CANMock::available());

    CAN_message_t receivedMsg;
    bool received = ESP32CANMock::read(receivedMsg);
    TEST_ASSERT_TRUE(received);

    assertCANMessagesEqual(sentMsg, receivedMsg);
}

// Teste: Buffer com múltiplas mensagens
void test_ESP32CAN_receive_multiple_messages() {
    ESP32CANMock::begin(500000);

    CAN_message_t msg1, msg2;
    msg1.id = 0x100; msg1.len = 2; msg1.buf[0] = 1; msg1.buf[1] = 2;
    msg2.id = 0x200; msg2.len = 3; msg2.buf[0] = 10; msg2.buf[1] = 20; msg2.buf[2] = 30;

    ESP32CANMock::write(msg1);
    ESP32CANMock::write(msg2);

    TEST_ASSERT_EQUAL(2, ESP32CANMock::available());

    CAN_message_t received;
    TEST_ASSERT_TRUE(ESP32CANMock::read(received));
    assertCANMessagesEqual(msg1, received);

    TEST_ASSERT_TRUE(ESP32CANMock::read(received));
    assertCANMessagesEqual(msg2, received);

    TEST_ASSERT_EQUAL(0, ESP32CANMock::available());
}

// Teste: Leitura com buffer vazio
void test_ESP32CAN_read_empty() {
    ESP32CANMock::end(); // Garante que está desligado
    ESP32CANMock::begin(500000);

    CAN_message_t msg;
    bool result = ESP32CANMock::read(msg);
    TEST_ASSERT_FALSE(result); // Não deve ler nada
}

// Teste: Injeção de mensagem (simulando recebimento externo)
void test_ESP32CAN_inject_message() {
    ESP32CANMock::begin(500000);

    CAN_message_t injected;
    injected.id = 0xABC;
    injected.ext = 1;
    injected.len = 1;
    injected.buf[0] = 0xFF;

    ESP32CANMock::injectMessage(injected);

    TEST_ASSERT_EQUAL(1, ESP32CANMock::available());

    CAN_message_t received;
    TEST_ASSERT_TRUE(ESP32CANMock::read(received));
    assertCANMessagesEqual(injected, received);
}

// Teste: Falha na inicialização afeta envio
void test_ESP32CAN_write_uninitialized() {
    ESP32CANMock::end();
    ESP32CANMock::forceInitFailure(true); // força falha

    CAN_message_t msg;
    msg.id = 0x100;
    msg.len = 1;
    msg.buf[0] = 42;

    bool result = ESP32CANMock::write(msg);
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(0, ESP32CANMock::available());
}

// Teste: Limpeza com end()
void test_ESP32CAN_end() {
    ESP32CANMock::begin(500000);
    TEST_ASSERT_TRUE(ESP32CANMock::isInitialized);

    ESP32CANMock::end();
    TEST_ASSERT_FALSE(ESP32CANMock::isInitialized);
    TEST_ASSERT_EQUAL(0, ESP32CANMock::bitrate);
    TEST_ASSERT_EQUAL(0, ESP32CANMock::available());
}
