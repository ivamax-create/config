#include "binary_sensor.h"

namespace esphome {
namespace water_sensor_component {

void WaterSensorComponent::setup() {
  if (this->uart_parent_ == nullptr) {
    ESP_LOGE(TAG, "UART parent not set!");
    this->mark_failed();
  }
}

void WaterSensorComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "UART Water Sensor:");
  ESP_LOGCONFIG(TAG, "  Device Class: moisture");
}

void WaterSensorComponent::loop() {
  while (this->uart_parent_->available()) {
    uint8_t byte;
    this->uart_parent_->read_array(&byte, 1);
    char c = (char) byte;

    if (c == '\n') {
      if (!this->received_data_.empty() && this->received_data_.back() == '\r') {
        this->received_data_.pop_back();
      }

      // Парсинг вхідного рядка
      if (this->received_data_ == "WATER_ON") {
        this->publish_state(true);
        ESP_LOGI(TAG, "Water detected: ON");
      } else if (this->received_data_ == "WATER_OFF") {
        this->publish_state(false);
        ESP_LOGI(TAG, "Water detected: OFF");
      } else {
        ESP_LOGD(TAG, "Received unknown data: %s", this->received_data_.c_str());
      }

      this->received_data_.clear();
      
    } else if (c != '\r') {
      this->received_data_.push_back(c);
    }
  }
}

} // namespace water_sensor_component
} // namespace esphome