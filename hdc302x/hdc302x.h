#pragma once
#include "esphome.h"
#include <Adafruit_HDC302X.h>

class HDC302XSensor : public PollingComponent {
 public:
  Sensor *temperature_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();

  HDC302XSensor(uint32_t update_interval) : PollingComponent(update_interval) {}

  void setup() override {
    Wire.begin();
    if (!hdc.begin()) {
      ESP_LOGE("HDC302X", "Failed to initialize HDC302X sensor!");
      mark_failed();
    }
    hdc.setDRDYpin(0xFF); // Disable DRDY pin if not used
  }

  void update() override {
    float temp = hdc.readTemperature();
    float hum = hdc.readHumidity();

    if (!isnan(temp)) {
      temperature_sensor->publish_state(temp);
    }
    if (!isnan(hum)) {
      humidity_sensor->publish_state(hum);
    }
  }

 private:
  Adafruit_HDC302X hdc;
};
