#include <DHT11.h>

const uint8_t dht11_pin = 2;

DHT11 dht11(dht11_pin);

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (dht11.update()) {
        Serial.print("DHT11 Okay,humidity is ");
        Serial.print(dht11.humidity);
        Serial.print(", temperature is ");
        Serial.println(dht11.temperature);
    } else {
        Serial.println("DHT11 ERROR!");
    }
    delay(2000);
}