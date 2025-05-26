 # Wireless Stethoscope
 Designed and developed a wireless stethoscopesystem using ESP32 and ESP8266 microcontrollers for real-time lung and heart sound monitoring over a local area network (LAN). Integrated the INMP441 digital microphone for capturing high-fidelity audio and the MAX98357A DAC amplifier for playback. Programmed the microcontrollers in C++, and built a Python-based remote server to store and manage lung sound recordings for further analysis and retrieval. The system facilitates remote auscultation and supports future enhancements like telemedicine integration.
<br />
In Addition to that I have implemented LED Indicators to show the connectivity statues of the device to the Wi-Fi, Client and Server.


## Block Diagram and Explanation
![block diagram](https://github.com/user-attachments/assets/1d2581a2-ac65-4c81-ab9b-3a471f7f4a41)

<br />

Above block diagram shows what are the modules intergraded to develop this wireless stethoscope. There are two major parts those are Stethoscope (chest
piece) and Receiver.
<br />

## Stethoscope (chest piece)
A Microphone placed in the chest piece of the stethoscope captures the acoustic sound sent through amplifier and goes to esp32 Wi-Fi module. Esp32 module send received data to receiver.
<br />

## Receiver
The receiver, another esp8266 Wi-Fi module receives transmitted data from stethoscope and Amplifier module amplifies the data output to speaker and we can hear the acoustic heard beat sound.
<br />
## Indicaters
Serial monitor of Arduino IDE prints connectivity details of the both devices and LED indicaters to show connectivity states
<br />
Web server stores the captured audio data. for this pupose i developed a simple python server on linux.
<br />

## Basic design of the Stethoscope
To develop the stethoscope, I have got a normal stethoscope and cut it from the middle part of its rubber tube. fix the microphone in the rubber tube, to fix melt the rubber tube to make its hole larger according to the size of microphone and fix it properly using hot glue without any air leak between the rubber tube and microphone.

Arrangement of electronic modules

![transmitter final](https://github.com/user-attachments/assets/6534263b-fc47-4f8a-8de5-13e19ff79396)

Pin Mapping INMP441 to ESP32

**INMP441 microphone pins**|**ESP32 pins**
-|-
VDD|3.3V
GND|GND
SD|GPIO32/D32
SCK|GPIO12/D12
WS|GPIO13/D13
L/R|GND
Green LED|GPIO15/D15
Red LED|GPIO17/D17
Yellow LED|GPIO21/D21

prototype of my Stethoscope

![WhatsApp Image 2024-11-11 at 5 11 28 PM11](https://github.com/user-attachments/assets/42ed4580-dfb6-41af-85aa-2b6737c44d20)

## Hardware modules to develop the Stethoscope

#### ESP32 Wi-Fi module

![esp32](https://github.com/user-attachments/assets/f38995f8-6919-4af4-8daa-6a134a5c18ea)

Esp32 is containing a low cost, low power consumption and high-performance Microcontroller that built by Espressif Systems. It has a Tensilica Xtensa LX6 32-bit with 160- 240 MHz dual core microprocessor. Its processing power help to success my project with one core is in reading mode while other core is in writing mode. includes built-in wireless antenna switches, RF balun, power amplifier, low-noise receive amplifier, filters, and power-management modules.

- Memory: -520 KiB SRAM
- Wireless connectivity: - Wi-Fi: 802.11 b/g/n, Bluetooth:-v4.2 BR/EDR and BLE
- Peripheral interfaces: - 12-bit SAR ADC up to 18 channels, 2 × 8-bit DACs, 10 × touch sensors (capacitive sensing GPIOs), 4 × SPI, 2 × I²S interfaces, 2 × I²C interfaces, 3 × UART
- SD/SDIO host controller, SDIO/SPI slave controller
- Ethernet MAC interface and CAN bus 2.0
- Infrared remote controller (TX/RX), Motor PWM, LED PWM
- Ultra-low power analog pre-amplifier
- Security: IEEE 802.11 standard security features WFA, WPA/WPA2 and WAPI
- Flash encryption

#### Microphone - INMP441

![download](https://github.com/user-attachments/assets/7ddf41d8-f4cf-48aa-974c-c3877bb49910)

The INMP441 is a popular MEMS (Micro-Electro-Mechanical System) omni-directional microphone it comes up with some special features that need for the development of the wireless stethoscope. It has major inbuilt capabilities rather than the regular microphones. Its shape and size are very suitable for my project and it make easy attach to the chest piece. Let’s look its built-in function of INMP441.
- Digital Output (I2S Interface).
It has inbuilt I2S converter. when its captures a date it outputs the data using I2s protocol is make easier to handle data with integrated circuits and microcontrollers.
And it has inbuilt analog to digitals converter as we receive the data from microphone as digital data rather than analog. And it makes easier to handle and process data to transmit or the wireless network.
- Low Power Consumption.
- Integrated Amplifier - it reduces the work load of converting analog to digital.
- Cost effective.
Compare to regular microphones and amplifiers it is very cost-effective buying a single device to buying two devices.
Because of its inbuilt functions it makes easier to implement the project. its working frequency (typically 60 Hz to 15 kHz) captured data less prone to noise and MEMS technology made it small and light weight.

#### Connection Status of the Stethoscope

![indications](https://github.com/user-attachments/assets/95bd6922-b8ec-4e3a-9eb4-06838a3afbe4)

#### Indications

- RED LED - Not Connected to WIFI.
- GREEN LED - Connected to WIFI.
- ORANGE LED - Connected to Server.

#### Serial Moniter printing connection Status

![trnsmiter ip sts](https://github.com/user-attachments/assets/6665f71a-51da-4722-9753-44d1cc35e8c8)

Printing the IP Address of the Stethoscope that verifies the connectivity and communication enabled.

## Web Server

I have implemented a simple python Web server to receive data using my Linux machine. And the transmitted data received by the webserver and stored in steth_beat.wav format.

![webserver](https://github.com/user-attachments/assets/2344dd3f-a0ee-47f3-9fbf-67d5b70c9835)

## Basic design of the Receiver
In the development phase of the receiver, I have used another esp32 Wi-Fi access module as main processing unit. Other components like speaker, MAX9735A amplifier module and other electrical components like jumpers, connectors all are connected using solderless bread board to work as a receiver.

Arrangement of electronic modules

![recvr_final](https://github.com/user-attachments/assets/c5a06f88-0522-4513-8116-a3e0d3afa8b7)

Pin Mapping MAX9735A to ESP32

**MAX98357A**|**ESP32**
-|-
Vin|3.3V
GND|GND
DIN|GPIO14/D14
BCLK|GPIO13/D13
LRC|GPIO12/D12
GAIN|GND/Vin (optional)
Green LED|GPIO15/D15
Red LED|GPIO18/D18
Yellow LED|GPIO21/D21

prototype of my Recevier

![recvr](https://github.com/user-attachments/assets/a1096a4b-5a70-4a9b-b289-a2186c268f35)

## Hardware modules to develop the Recevier

#### ESP32 Wi-Fi module

![esp32](https://github.com/user-attachments/assets/f38995f8-6919-4af4-8daa-6a134a5c18ea)

Esp32 is containing a low cost, low power consumption and high-performance Microcontroller that built by Espressif Systems. It has a Tensilica Xtensa LX6 32-bit with 160- 240 MHz dual core microprocessor. Its processing power help to success my project with one core is in reading mode while other core is in writing mode. includes built-in wireless antenna switches, RF balun, power amplifier, low-noise receive amplifier, filters, and power-management modules.

- Memory: -520 KiB SRAM
- Wireless connectivity: - Wi-Fi: 802.11 b/g/n, Bluetooth:-v4.2 BR/EDR and BLE
- Peripheral interfaces: - 12-bit SAR ADC up to 18 channels, 2 × 8-bit DACs, 10 × touch sensors (capacitive sensing GPIOs), 4 × SPI, 2 × I²S interfaces, 2 × I²C interfaces, 3 × UART
- SD/SDIO host controller, SDIO/SPI slave controller
- Ethernet MAC interface and CAN bus 2.0
- Infrared remote controller (TX/RX), Motor PWM, LED PWM
- Ultra-low power analog pre-amplifier
- Security: IEEE 802.11 standard security features WFA, WPA/WPA2 and WAPI
- Flash encryption

#### Amplifier - MAX98357A

![amp](https://github.com/user-attachments/assets/b5fae8f7-7c49-4fb9-931c-13508eecc0ed)

Like above mentioned INMP441 microphone this amplifier Digital to analog converter also have some unique features other than the normal amplifiers. Its getting a digital signal and directly convert to analog signal. Specially it has audio output pins and directly connectable to speakers. We will look how it differs from normal digital to analog converters.
- Integrated Class D Amplifier
It has in-built class D amplifier and it able run 3.3V, 8ohm speaker without and power modules. So, this is reduced my work load and it’s a suitable module for power efficient systems like wireless devices.
- Digital Audio interfaces
It uses I2S (Inter-IC Sound) protocol to communicate so it is suitable for microcontroller-based applications and it make easy to implement because no need of special converters.
- It comes with in-built nose reduction systems so its suitable for audio related implementations
- Cost effective.
And there are more specifications.
