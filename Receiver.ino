#include <SPI.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "driver/i2s.h"

#define WS  12          // Word Select (L/R) pin for MAX98357A
#define SCK 13          // Bit Clock pin for MAX98357A
#define DATA_OUT  15    // Data Out pin for MAX98357A

#define I2S_PORT I2S_NUM_0
#define UPDATE_INTERVAL   (500)

//LED pins
const int greenLED = 15;
const int redLED = 18;
const int yellowLED = 21;

const char* ssid = "{WIFI-SSID}";
const char* password = "{PASSWORD}";


using namespace websockets;
WebsocketsServer server;
WebsocketsClient client;

const i2s_config_t i2s_config_tx = {
  .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate = 16000,        //.sample_rate = 44100, higher sample rate required higher memory and processing speed, causes delay, sample rate of both devices shoud be same
  .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
  .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
  .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
  .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
  .dma_buf_count = 8,         // Reduced buffer count for smooth playback
  .dma_buf_len = 256          // Reduced buffer length for lower latency
};

const i2s_pin_config_t pin_config_tx = {
  .bck_io_num = SCK,
  .ws_io_num = WS,
  .data_out_num = DATA_OUT,
  .data_in_num = I2S_PIN_NO_CHANGE
};

unsigned long last_update_sent = 0;
bool isConnected; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  server.listen(8888);
  delay(1000);
  Serial.print("ESP32 server IP Address: ");
  Serial.println(WiFi.localIP());
  xTaskCreate(server_task, "server_task", 4096, NULL, 1, NULL);
}

static void server_task(void *arg) {
  while(1){
    if(server.poll()){
      client = server.accept();
      i2sInit();
      last_update_sent = millis();
      isConnected = true;
    }

    if(isConnected && millis() - last_update_sent > UPDATE_INTERVAL) {
      Serial.println("Client disconnected! Uninstalling I2S driver");
      isConnected = false;      
      i2s_driver_uninstall(I2S_PORT);
    }
    vTaskDelay(100);
  }
}

void loop() {
  i2s_write_from_client();
}

void i2s_write_from_client() {   
  if(client.available()){
    last_update_sent = millis();
    client.poll();
    WebsocketsMessage msg = client.readBlocking();
    char *buf_ptr = (char*)msg.c_str();
    size_t bytes_to_write = msg.length();  // Number of bytes to write
    size_t bytes_written;  // Variable to store the number of bytes actually written

    // Use i2s_write with the correct parameters
    i2s_write(I2S_PORT, buf_ptr, bytes_to_write, &bytes_written, portMAX_DELAY);
  }
}

void i2sInit() {
  i2s_driver_install(I2S_PORT, &i2s_config_tx, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config_tx);
}
