#pragma once
#include "esphome/core/component.h"

namespace esphome {
namespace water_sensor_component {

class WaterSensorComponent : public Component {
 public:
  void setup() override {
    ESP_LOGI("water_sensor_component", "Water Sensor Component setup complete");
  }

  void loop() override {
    // Тут можна читати UART або GPIO
  }
};

}  // namespace water_sensor_component
}  // namespace esphome
