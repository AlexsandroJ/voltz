// mocks/esp32can_mock.cpp
#include <vector>
#include <cstdint>

// Estrutura simulada da mensagem CAN (compatível com a original)
struct CAN_message_t {
    uint32_t id = 0;
    uint8_t ext = 0;
    uint8_t rtr = 0;
    uint8_t len = 0;
    uint8_t buf[8] = {0};
};

namespace ESP32CANMock {

    // Estado do barramento CAN
    bool isInitialized = false;
    uint32_t bitrate = 0;
    std::vector<CAN_message_t> rxBuffer; // Fila de mensagens recebidas

    // Simula CAN.begin() - retorna 1 se sucesso, 0 se falha
    int begin(uint32_t baudrate) {
        if (baudrate == 0) return 0; // falha se baudrate inválido
        bitrate = baudrate;
        isInitialized = true;
        rxBuffer.clear();
        return 1;
    }

    // Simula CAN.end()
    void end() {
        isInitialized = false;
        bitrate = 0;
        rxBuffer.clear();
    }

    // Simula CAN.write() - envia uma mensagem
    bool write(const CAN_message_t& message) {
        if (!isInitialized) return false;
        // Simula recebimento imediato (loopback interno para testes)
        CAN_message_t copy = message;
        rxBuffer.push_back(copy);
        return true;
    }

    // Simula CAN.read() - lê mensagem do buffer
    bool read(CAN_message_t& message) {
        if (rxBuffer.empty()) return false;
        message = rxBuffer.front();
        rxBuffer.erase(rxBuffer.begin());
        return true;
    }

    // Retorna o número de mensagens disponíveis para leitura
    int available() {
        return rxBuffer.size();
    }

    // Funções auxiliares para testes
    void injectMessage(const CAN_message_t& msg) {
        rxBuffer.push_back(msg);
    }

    void forceInitFailure(bool fail) {
        isInitialized = !fail;
    }

    void clearBuffer() {
        rxBuffer.clear();
    }

} // namespace ESP32CANMock