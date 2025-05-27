# Web Socket function
The `onEventsCallback` function in our code is a **WebSocket event handler** written for an ESP32 or similar microcontroller using the Arduino framework and a WebSocket client library.

### 🔍 Purpose:

This function is called automatically by the WebSocket client library whenever specific **WebSocket events** occur. It helps manage and respond to connection-related events between the client (ESP32) and a WebSocket server.

---

### 🧠 Breakdown of Each Part:

```cpp
void onEventsCallback(WebsocketsEvent event, String data)
```

* **Function signature**: This is a callback function that gets called by the library when a WebSocket event occurs.
* **`event`**: Enum value representing the type of WebSocket event.
* **`data`**: Any additional data passed with the event (not used here).

---

### ⚙️ Event Handling Logic:

```cpp
if (event == WebsocketsEvent::ConnectionOpened) {
  Serial.println("Connnection Opened");
  isWebSocketConnected = true;
}
```

* Prints a message when the WebSocket connection is successfully opened.
* Sets a flag `isWebSocketConnected = true` to indicate that communication is now active.

---

```cpp
else if (event == WebsocketsEvent::ConnectionClosed) {
  Serial.println("Connnection Closed");
  isWebSocketConnected = false;
}
```

* Prints a message when the WebSocket connection is closed.
* Sets the flag to `false` to indicate the connection is no longer active.

---

```cpp
else if (event == WebsocketsEvent::GotPing) {
  Serial.println("Got a Ping!");
}
```

* Logs when the server sends a WebSocket **ping** message, often used to check if the client is still responsive.

---

```cpp
else if (event == WebsocketsEvent::GotPong) {
  Serial.println("Got a Pong!");
}
```

* Logs when the server responds to a ping with a **pong**, confirming the connection is alive.

---

### ✅ Summary:

This function is essential for monitoring the state of the WebSocket connection and maintaining the correct connection status in your ESP32 project. It allows our code to react accordingly when the connection opens, closes, or is checked with ping/pong signals.
