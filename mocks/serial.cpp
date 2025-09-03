#include <unity.h>
#include <string>
#include <vector>

// Mock para Serial
namespace SerialMock {
    bool isInitialized = false; // Estado da inicialização
    std::vector<uint8_t> buffer; // Buffer simulado para armazenar dados enviados

    // Função simulada para Serial.begin()
    void begin(unsigned long baudrate) {
        isInitialized = true; // Simula inicialização
    }

    // Função simulada para Serial.print()
    void print(const std::string& message) {
        if (!isInitialized) return; // Ignora se não inicializado
        for (char c : message) {
            buffer.push_back(c); // Adiciona cada caractere ao buffer
        }
    }

    // Função simulada para Serial.println()
    void println(const std::string& message) {
        print(message); // Chama Serial.print()
        buffer.push_back('\n'); // Adiciona nova linha ao buffer
    }

    // Função simulada para Serial.available()
    int available() {
        return buffer.size(); // Retorna o tamanho do buffer
    }

    // Função simulada para Serial.read()
    int read() {
        if (buffer.empty()) return -1; // Retorna -1 se o buffer estiver vazio
        int data = buffer.front(); // Lê o primeiro byte
        buffer.erase(buffer.begin()); // Remove o byte lido
        return data;
    }

    // Função simulada para Serial.readString()
    std::string readString() {
        std::string result;
        while (available()) {
            char c = static_cast<char>(read()); // Lê byte por byte
            result += c;
        }
        return result;
    }
}
