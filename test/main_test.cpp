
#include "../test/serial/test_serial.cpp"
#include "../test/wifi_h/test_wifi.cpp"

#include <unity.h>

// Configurações antes de cada teste
void setUp() {
    // Reinicializa o estado do mock antes de cada teste
    WiFiMock::mockWiFiStatus = MOCK_WL_DISCONNECTED;
    WiFiMock::mockSSID.clear();
    WiFiMock::mockPassword.clear();

    SerialMock::isInitialized = false;
    SerialMock::buffer.clear();
}
// Limpeza após cada teste
void tearDown() {
    // Limpa recursos, se necessário (opcional neste caso)
}
// Função main para executar os testes
int main(int argc, char **argv) {
    UNITY_BEGIN(); // Inicializa o Unity

    RUN_TEST(test_wifi_scan_networks);
    RUN_TEST(test_wifi_get_ssid);
    RUN_TEST(test_wifi_get_rssi);


    RUN_TEST(test_serial_begin);
    RUN_TEST(test_serial_print);
    RUN_TEST(test_serial_println);
    RUN_TEST(test_serial_read);
    RUN_TEST(test_serial_read_string);

    UNITY_END(); // Finaliza o Unity

    return 0; // Retorna 0 para indicar sucesso
}