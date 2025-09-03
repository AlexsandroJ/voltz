
#include "../mocks/serial.cpp"
#include <unity.h>

// Função de teste: Inicialização da comunicação serial
void test_serial_begin() {
    SerialMock::begin(9600);
    TEST_ASSERT_TRUE(SerialMock::isInitialized); // Verifica se a inicialização foi bem-sucedida
}

// Função de teste: Envio de dados com Serial.print()
void test_serial_print() {
    SerialMock::begin(9600);
    SerialMock::print("Hello");
    std::string expected = "Hello";
    TEST_ASSERT_EQUAL_STRING(expected.c_str(), std::string(SerialMock::buffer.begin(), SerialMock::buffer.end()).c_str());
}

// Função de teste: Envio de dados com Serial.println()
void test_serial_println() {
    SerialMock::begin(9600);
    SerialMock::println("World");
    std::string expected = "World\n";
    TEST_ASSERT_EQUAL_STRING(expected.c_str(), std::string(SerialMock::buffer.begin(), SerialMock::buffer.end()).c_str());
}

// Função de teste: Leitura de dados com Serial.available() e Serial.read()
void test_serial_read() {
    SerialMock::begin(9600);
    SerialMock::println("Test");
    TEST_ASSERT_EQUAL(5, SerialMock::available()); // Verifica se há 5 bytes disponíveis ('T', 'e', 's', 't', '\n')

    std::string result;
    while (SerialMock::available()) {
        result += static_cast<char>(SerialMock::read());
    }
    TEST_ASSERT_EQUAL_STRING("Test\n", result.c_str()); // Verifica se os dados lidos são corretos
}

// Função de teste: Leitura de strings com Serial.readString()
void test_serial_read_string() {
    SerialMock::begin(9600);
    SerialMock::println("Arduino");
    std::string result = SerialMock::readString();
    TEST_ASSERT_EQUAL_STRING("Arduino\n", result.c_str()); // Verifica se a string lida é correta
}
