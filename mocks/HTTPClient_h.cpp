// http_client_mock.cpp
#include <string>
#include <vector>

namespace HTTPClientMock {

    // Estado do cliente
    bool isConnected = false;
    std::string requestUrl;
    std::string requestMethod;
    std::string requestPayload;
    std::string headerContentType;

    // Resposta simulada
    int responseStatusCode = 200;
    std::string responseBody = "OK";
    bool shouldFailConnect = false;

    // Simula begin (inicialização da requisição)
    void begin(const char* url) {
        requestUrl = std::string(url);
        isConnected = !shouldFailConnect;
    }

    // Simula addHeader
    void addHeader(const char* name, const char* value) {
        if (std::string(name) == "Content-Type") {
            headerContentType = std::string(value);
        }
    }

    // Simula GET
    int GET() {
        if (!isConnected) return -1;
        requestMethod = "GET";
        return responseStatusCode;
    }

    // Simula POST
    int POST(const char* payload) {
        if (!isConnected) return -1;
        requestMethod = "POST";
        requestPayload = std::string(payload);
        return responseStatusCode;
    }

    // Simula POST sem payload (para testar overload)
    int POST() {
        return POST("");
    }

    // Simula getString() - retorna o corpo da resposta
    std::string getString() {
        return responseBody;
    }

    // Simula getResponseCode()
    int getResponseCode() {
        return responseStatusCode;
    }

    // Libera recursos (simulado)
    void end() {
        isConnected = false;
        requestUrl.clear();
        requestMethod.clear();
        requestPayload.clear();
    }

    // Funções de controle para testes
    void setResponse(int code, const std::string& body) {
        responseStatusCode = code;
        responseBody = body;
    }

    void failNextConnect(bool fail) {
        shouldFailConnect = fail;
    }

} // namespace HTTPClientMock