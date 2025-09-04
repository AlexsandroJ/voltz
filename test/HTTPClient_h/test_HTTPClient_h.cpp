// test_HTTPClient_client.cpp
#include "../mocks/HTTPClient_h.cpp"  // Caminho para o mock
#include <unity.h>

// Teste: Inicialização da requisição HTTP
void test_HTTPClient_begin() {
    HTTPClientMock::begin("http://example.com/api");
    TEST_ASSERT_TRUE(HTTPClientMock::isConnected);
    TEST_ASSERT_EQUAL_STRING("http://example.com/api", HTTPClientMock::requestUrl.c_str());
}

// Teste: Envio de requisição GET
void test_HTTPClient_get_request() {
    HTTPClientMock::begin("http://example.com/data");
    int code = HTTPClientMock::GET();
    
    TEST_ASSERT_EQUAL(200, code);
    TEST_ASSERT_EQUAL_STRING("GET", HTTPClientMock::requestMethod.c_str());
}

// Teste: Leitura do código de resposta e corpo
void test_HTTPClient_get_response() {
    HTTPClientMock::setResponse(200, "{'status':'ok'}");

    HTTPClientMock::begin("http://example.com/status");
    HTTPClientMock::GET();

    TEST_ASSERT_EQUAL(200, HTTPClientMock::getResponseCode());
    TEST_ASSERT_EQUAL_STRING("{'status':'ok'}", HTTPClientMock::getString().c_str());
}

// Teste: Requisição POST com payload
void test_HTTPClient_post_request() {
    HTTPClientMock::begin("http://example.com/submit");
    HTTPClientMock::addHeader("Content-Type", "application/json");

    int code = HTTPClientMock::POST(R"({"name":"John"})");

    TEST_ASSERT_EQUAL(200, code);
    TEST_ASSERT_EQUAL_STRING("POST", HTTPClientMock::requestMethod.c_str());
    TEST_ASSERT_EQUAL_STRING("application/json", HTTPClientMock::headerContentType.c_str());
    TEST_ASSERT_EQUAL_STRING("{\"name\":\"John\"}", HTTPClientMock::requestPayload.c_str());
}

// Teste: Tratamento de erro de conexão
void test_HTTPClient_connection_failure() {
    HTTPClientMock::failNextConnect(true);
    HTTPClientMock::begin("http://example.com/fail");

    int get_code = HTTPClientMock::GET();
    int post_code = HTTPClientMock::POST("data");

    TEST_ASSERT_EQUAL(-1, get_code);
    TEST_ASSERT_EQUAL(-1, post_code);
    TEST_ASSERT_FALSE(HTTPClientMock::isConnected);
}

// Teste: Uso de end() para encerrar conexão
void test_HTTPClient_end() {
    HTTPClientMock::begin("http://example.com");
    TEST_ASSERT_TRUE(HTTPClientMock::isConnected);

    HTTPClientMock::end();
    TEST_ASSERT_FALSE(HTTPClientMock::isConnected);
    TEST_ASSERT_TRUE(HTTPClientMock::requestUrl.empty());
}

// Teste: Respostas com códigos de erro
void test_HTTPClient_error_response() {
    HTTPClientMock::setResponse(404, "Not Found");

    HTTPClientMock::begin("http://example.com/missing");
    int code = HTTPClientMock::GET();

    TEST_ASSERT_EQUAL(404, code);
    TEST_ASSERT_EQUAL_STRING("Not Found", HTTPClientMock::getString().c_str());
}