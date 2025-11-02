#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"
#include <string>

namespace esphome {
namespace water_sensor_component {

static const char *const TAG = "water_sensor_uart"; // Тег для логів ESPHome

class WaterSensorComponent : public binary_sensor::BinarySensor, public Component {
public:
  // Метод для встановлення батьківського UART компонента
  void set_uart_parent(uart::UARTComponent *parent) { this->uart_parent_ = parent; }

  // Метод для налаштування (запускається один раз)
  void setup() override;

  // Метод для відображення конфігурації в логах
  void dump_config() override;

  // Метод для читання даних з UART в циклі (це замінює класичний loop)
  void loop() override;

protected:
  uart::UARTComponent *uart_parent_{nullptr};
  std::string received_data_; // Буфер для збору вхідних даних
};

} // namespace water_sensor_component
} // namespace esphome