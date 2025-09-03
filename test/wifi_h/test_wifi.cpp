#include "../mocks/wifi_h.cpp"
#include <unity.h>

// Função de teste: Escanear redes Wi-Fi
void test_wifi_scan_networks() {
    int numNetworks = WiFiMock::scanNetworks();
    TEST_ASSERT_EQUAL(3, numNetworks); // Verifica se há 3 redes disponíveis
}

// Função de teste: Obter SSID de uma rede específica
void test_wifi_get_ssid() {
    TEST_ASSERT_EQUAL_STRING("HomeWiFi", WiFiMock::SSID(0).c_str()); // Verifica SSID da primeira rede
    TEST_ASSERT_EQUAL_STRING("OfficeWiFi", WiFiMock::SSID(1).c_str()); // Verifica SSID da segunda rede
    TEST_ASSERT_EQUAL_STRING("PublicWiFi", WiFiMock::SSID(2).c_str()); // Verifica SSID da terceira rede
}

// Função de teste: Obter RSSI de uma rede específica
void test_wifi_get_rssi() {
    TEST_ASSERT_EQUAL(-50, WiFiMock::RSSI(0)); // Verifica RSSI da primeira rede
    TEST_ASSERT_EQUAL(-60, WiFiMock::RSSI(1)); // Verifica RSSI da segunda rede
    TEST_ASSERT_EQUAL(-80, WiFiMock::RSSI(2)); // Verifica RSSI da terceira rede
}
