#include <Arduino.h>

#include "DHT11.h"

DHT11::DHT11(uint8_t pin) {
    dht11_pin = pin;
}

uint32_t DHT11::getLowTime() {
    uint32_t lastTime = micros();
    while (!digitalRead(dht11_pin)) {
        if (micros() - lastTime > TIMEOUT) {
            break;
        }
    }
    return (micros() - lastTime);
}

uint32_t DHT11::getHighTime() {
    uint32_t lastTime = micros();
    while (digitalRead(dht11_pin)) {
        if (micros() - lastTime > TIMEOUT) {
            break;
        }
    }
    return (micros() - lastTime);
}

bool DHT11::update() {
    /*MCU发送开始信号, 并等待应答*/
    pinMode(dht11_pin, OUTPUT);
    // 拉低18ms
    digitalWrite(dht11_pin, LOW);
    delay(18);
    // 拉高40us
    digitalWrite(dht11_pin, HIGH);
    delayMicroseconds(40);
    /*接受DHT11做出的应答*/
    pinMode(dht11_pin, INPUT_PULLUP);
    getLowTime();
    getHighTime();
    /*开始接受40bit数据*/
    uint8_t buffer[5] = {0};
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            getLowTime();
            if (getHighTime() > 50)
                buffer[i] |= (0x80 >> j);
        }
    }
    /*结束通信*/
    getLowTime();
    /*检查校验和*/
    if (buffer[0] + buffer[1] + buffer[2] + buffer[3] != buffer[4])
        return false;
    /*更新数据*/
    humidity = buffer[0];
    temperature = buffer[2];
    return true;
}
