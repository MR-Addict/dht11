#ifndef _DHT11_H_
#define _DHT11_H_

#define TIMEOUT 1e5

class DHT11 {
   private:
    uint8_t dht11_pin;
    uint32_t getLowTime();
    uint32_t getHighTime();

   public:
    DHT11(uint8_t);
    uint8_t humidity;
    uint8_t temperature;
    bool update();
};

#endif