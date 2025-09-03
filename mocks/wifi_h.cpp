#include <unity.h>
#include <string>
#include <vector>
// Definindo nossas próprias constantes para simular os estados do WiFi
#define MOCK_WL_CONNECTED       3   // Simula estado conectado
#define MOCK_WL_DISCONNECTED    0   // Simula estado desconectado
#define MOCK_WL_CONNECT_FAILED  4   // Simula falha na conexão

// Mocks para WiFi.h
namespace WiFiMock {
    int mockWiFiStatus = MOCK_WL_DISCONNECTED; // Estado inicial: desconectado
    std::string mockSSID;
    std::string mockPassword;

    // Simulação de redes Wi-Fi disponíveis
    struct Network {
        std::string ssid;
        int rssi;
    };
    std::vector<Network> mockNetworks = {
        {"HomeWiFi", -50},  // Rede 1
        {"OfficeWiFi", -60}, // Rede 2
        {"PublicWiFi", -80}  // Rede 3
    };

    // Função simulada para WiFi.begin()
    void begin(const char* ssid, const char* password) {
        mockSSID = ssid;
        mockPassword = password;

        if (mockSSID == "ValidSSID" && mockPassword == "ValidPassword") {
            mockWiFiStatus = MOCK_WL_CONNECTED; // Simula conexão bem-sucedida
        } else {
            mockWiFiStatus = MOCK_WL_CONNECT_FAILED; // Simula falha na conexão
        }
    }

    // Função simulada para WiFi.status()
    int status() {
        return mockWiFiStatus;
    }

    // Função simulada para WiFi.disconnect()
    void disconnect() {
        mockWiFiStatus = MOCK_WL_DISCONNECTED;
    }

    // Função simulada para WiFi.scanNetworks()
    int scanNetworks() {
        return mockNetworks.size(); // Retorna o número de redes disponíveis
    }

    // Função simulada para WiFi.SSID(index)
    std::string SSID(int index) {
        if (index >= 0 && index < mockNetworks.size()) {
            return mockNetworks[index].ssid; // Retorna o SSID da rede no índice
        }
        return ""; // Retorna string vazia se o índice for inválido
    }

    // Função simulada para WiFi.RSSI(index)
    int RSSI(int index) {
        if (index >= 0 && index < mockNetworks.size()) {
            return mockNetworks[index].rssi; // Retorna o RSSI da rede no índice
        }
        return 0; // Retorna 0 se o índice for inválido
    }
}
