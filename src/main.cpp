#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

const char* ssid = "";
const char* password = "";

HTTPClient client;

bool getState() {
    bool led = false;

    WiFiClient w;
    client.begin(w, "http://192.168.0.151:5000/api/state");

    int code = client.GET();
    if(code == 200) {
        String res = client.getString();

        if(res == "false") led = false;
        else if(res == "true") led = true;
        else Serial.printf("response from the server: %s\n", res.c_str());
    } else {
        Serial.printf("Result code: %i\n", code);
    }

    client.end();
    return led;
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    bool state = getState();
    if(state == true) digitalWrite(LED_BUILTIN, HIGH);
    else if(state == false) digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
