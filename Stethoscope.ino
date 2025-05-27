#include <driver/i2s.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#define SD 32
#define WS 15
#define SCK 12
#define PORT I2S_NUM_0

#define bufferCnt 8
#define bufferLen 256
#define LED_PIN 2  // Choose GPIO pin 2, or any other available pin

//LED pins
const int greenLED = 21;
const int redLED = 17;
const int yellowLED = 15;

// passing buffer lenth
int16_t sBuffer[bufferLen];

// setting wifi credentials
const char* ssid = "{WIFI-SSID}";
const char* password = "{PASSWORD}";

// passing wifi credentials to stethoscope
const char* server_IP = "{IP ADDRESS}"; // server ip address
const uint16_t server_port = 8888;  // WEBSOCKET_SERVER_PORT can be any

using namespace websockets;
WebsocketsClient client;
bool isWebSocketConnected;

//called automatically by the WebSocket client library whenever specific WebSocket events occur. It helps manage and respond to connection-related events
// detailed description is ther in the web-socket-description.md file 
void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    Serial.println("Connnection Opened");
    isWebSocketConnected = true;
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    Serial.println("Connnection Closed");
    isWebSocketConnected = false;
  } else if (event == WebsocketsEvent::GotPing) {
    Serial.println("Got a Ping!");
  } else if (event == WebsocketsEvent::GotPong) {
    Serial.println("Got a Pong!");
  }
}

void i2s_install() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    //.sample_rate = 44100, higher sample rate required higher memory and processing speed, causes delay
    .sample_rate = 16000, // sample rate of both devices shoud be same
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = bufferCnt,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  // Set I2S pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num = SCK,
    .ws_io_num = WS,
    .data_out_num = -1,
    .data_in_num = SD
  };

  i2s_set_pin(PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);

  connectWiFi();
  connectWSServer();
  xTaskCreatePinnedToCore(micTask, "micTask", 10000, NULL, 1, NULL, 1);

  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output
}

void loop() {
}

void connectWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(1000);
    Serial.print(".");

    // redLED = on greenLED = off
    digitalwrite (greenLED, LOW);
    digitalwrite (redLED, HIGH);
  }

  // redLED = on greenLED = off
  digitalwrite (greenLED, HIGH);
  digitalwrite (redLED, LOW);

  // serial printing connection status
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Chest Piece IP Address: ");
  Serial.println(WiFi.localIP()); // printing IPs
}

void connectWSServer() {
  client.onEvent(onEventsCallback);
  while (!client.connect(server_IP, server_port, "/")) {
    delay(500);
    Serial.print(".");
  }
  digitalwrite (yellowLED, HIGH);
  Serial.println("Server Connected!");
}


void micTask(void* parameter) {

  i2s_install();
  i2s_setpin();
  i2s_start(PORT);

  size_t bytesIn = 0;
  while (1) {
    esp_err_t result = i2s_read(PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
    if (result == ESP_OK && isWebSocketConnected) {
      client.sendBinary((const char*)sBuffer, bytesIn);
    }
  }
}
