
#include "../test/serial/test_serial.cpp"
#include "../test/wifi_h/test_wifi.cpp"
#include "../test/HTTPClient_h/test_HTTPClient_h.cpp"
#include "../test/ESP32CAN_h/ESP32CAN_h.cpp"
#include "../test/CAN_config_h/CAN_config_h.cpp"
#include <unity.h>

// Configurações antes de cada teste
void setUp()
{
    // Reinicializa o estado do mock antes de cada teste
    WiFiMock::mockWiFiStatus = MOCK_WL_DISCONNECTED;
    WiFiMock::mockSSID.clear();
    WiFiMock::mockPassword.clear();

    SerialMock::isInitialized = false;
    SerialMock::buffer.clear();

    HTTPClientMock::isConnected = false;
    HTTPClientMock::requestUrl.clear();
    HTTPClientMock::requestMethod.clear();
    HTTPClientMock::requestPayload.clear();
    HTTPClientMock::headerContentType.clear();
    HTTPClientMock::setResponse(200, "OK");
    HTTPClientMock::failNextConnect(false);

    ESP32CANMock::end(); // Garante estado limpo
    ESP32CANMock::clearBuffer();

    initCANConfig();
}
// Limpeza após cada teste
void tearDown()
{
    // Limpa recursos, se necessário (opcional neste caso)
    HTTPClientMock::end();

    ESP32CANMock::end();
    ESP32CANMock::clearBuffer();
}
// Função main para executar os testes
int main(int argc, char **argv)
{
    UNITY_BEGIN(); // Inicializa o Unity
    // Casos de teste WIFI.h
    RUN_TEST(test_wifi_scan_networks);
    RUN_TEST(test_wifi_get_ssid);
    RUN_TEST(test_wifi_get_rssi);
    // Casos de teste SERIAL.h
    RUN_TEST(test_serial_begin);
    RUN_TEST(test_serial_print);
    RUN_TEST(test_serial_println);
    RUN_TEST(test_serial_read);
    RUN_TEST(test_serial_read_string);
    // Casos de teste HTTPClient.h
    RUN_TEST(test_HTTPClient_begin);
    RUN_TEST(test_HTTPClient_get_request);
    RUN_TEST(test_HTTPClient_get_response);
    RUN_TEST(test_HTTPClient_post_request);
    RUN_TEST(test_HTTPClient_connection_failure);
    RUN_TEST(test_HTTPClient_end);
    RUN_TEST(test_HTTPClient_error_response);
    // Casos de teste ESP32CAN.h
    RUN_TEST(test_ESP32CAN_begin);
    RUN_TEST(test_ESP32CAN_begin_invalid_baudrate);
    RUN_TEST(test_ESP32CAN_send_receive);
    RUN_TEST(test_ESP32CAN_receive_multiple_messages);
    RUN_TEST(test_ESP32CAN_read_empty);
    RUN_TEST(test_ESP32CAN_inject_message);
    RUN_TEST(test_ESP32CAN_write_uninitialized);
    RUN_TEST(test_ESP32CAN_end);
    // Casos de teste CAN_config.h
    RUN_TEST(test_can_config_default_valid);
    RUN_TEST(test_can_config_valid_speed);
    RUN_TEST(test_can_config_invalid_speed);
    RUN_TEST(test_can_config_invalid_tx_pin);
    RUN_TEST(test_can_config_invalid_rx_pin);
    RUN_TEST(test_can_config_custom_setup);
    RUN_TEST(test_can_config_null_handles);

    UNITY_END(); // Finaliza o Unity

    return 0; // Retorna 0 para indicar sucesso
}