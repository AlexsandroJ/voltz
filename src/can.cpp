#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

// Configuração do CAN
CAN_device_t CAN_cfg;
const int rx_queue_size = 10;       // Tamanho da fila de recepção

void setup() {
  // Inicializa a serial
  Serial.begin(115200);
  while (!Serial); // Espera o Serial Monitor (opcional)

  Serial.println("ESP32 CAN - Modo Escuta (Recepção Apenas)");

  // Configuração do barramento CAN
  CAN_cfg.speed = CAN_SPEED_125KBPS;     // Ajuste conforme sua rede (125K, 250K, 500K, etc)
  CAN_cfg.tx_pin_id = GPIO_NUM_5;        // Obrigatório mesmo sem transmissão (biblioteca exige)
  CAN_cfg.rx_pin_id = GPIO_NUM_4;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));

  // Inicializa o módulo CAN
  if (ESP32Can.CANInit()) {
    Serial.println("Inicialização CAN: SUCESSO");
  } else {
    Serial.println("Erro ao inicializar CAN!");
  }
}

void loop() {
  CAN_frame_t rx_frame;

  // Tenta ler uma mensagem da fila (timeout de 100ms)
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 100 / portTICK_PERIOD_MS) == pdTRUE) {
    // Imprime o início da mensagem
    Serial.print("ID: 0x");
    Serial.print(rx_frame.MsgID, HEX);

    // Tipo de frame
    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      Serial.print(" (STD)");
    } else {
      Serial.print(" (EXT)");
    }

    // Verifica se é RTR (Remote Transmission Request)
    if (rx_frame.FIR.B.RTR == CAN_RTR) {
      Serial.print(" - RTR, DLC: ");
      Serial.println(rx_frame.FIR.B.DLC);
    } else {
      Serial.print(" - Data [");
      Serial.print(rx_frame.FIR.B.DLC);
      Serial.print("]: ");

      // Imprime os bytes de dados
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        if (rx_frame.data.u8[i] < 0x10) {
          Serial.print("0"); // Formatação: 0x0F em vez de 0xF
        }
        Serial.print(rx_frame.data.u8[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }

  // Nenhum envio será feito
}