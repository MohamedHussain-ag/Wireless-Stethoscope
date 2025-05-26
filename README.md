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
### Stethoscope (chest piece)
<br />
A Microphone placed in the chest piece of the stethoscope captures the
acoustic sound sent through amplifier and goes to esp32 Wi-Fi module. Esp32
module send received data to receiver.
<br />
### Receiver
<br />
The receiver, another esp32 Wi-Fi module receives transmitted data from
stethoscope and Amplifier module amplifies the data output to speaker and we can
hear the acoustic heard beat sound.
<br />
Serial monitor of Arduino IDE prints connectivity details of the both
devices.
<br />
Web server stores the captured audio data.
<br />
