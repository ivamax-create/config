#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace water_sensor_component {

class WaterSensorBinarySensor : public binary_sensor::BinarySensor,
                                public Component,
                                public uart::UARTDevice {
public:
  void setup() override;
  void loop() override;
  void dump_config() override;

 protected:
  static const int MAX_BUFFER_SIZE = 64;
  char buffer[MAX_BUFFER_SIZE];
  int buffer_index = 0;
};

}  // namespace water_sensor_component
}  // namespace esphome
