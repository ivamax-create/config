#include "binary_sensor.h"

namespace esphome {
namespace water_sensor_component {

void WaterSensorComponent::setup() {
  if (this->uart_parent_ == nullptr) {
    ESP_LOGE(TAG, "UART parent not set!");
    this->mark_failed();
    return;
  }
  ESP_LOGI(TAG, "Water Sensor Component initialized successfully");
}

void WaterSensorComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "UART Water Sensor:");
  ESP_LOGCONFIG(TAG, "  Device Class: moisture");
  ESP_LOGCONFIG(TAG, "  Expects: 'WATER_ON' or 'WATER_OFF' from UART");
}

void WaterSensorComponent::loop() {
  while (this->uart_parent_->available()) {
    uint8_t byte;
    this->uart_parent_->read_array(&byte, 1);
    char c = (char)byte;

    if (this->received_data_.size() >= MAX_BUFFER_SIZE) {
      ESP_LOGW(TAG, "Buffer overflow detected, clearing");
      this->received_data_.clear();
      continue;
    }

    if (c == '\n') {
      // Видаляємо \r якщо присутня
      if (!this->received_data_.empty() && this->received_data_.back() == '\r') {
        this->received_data_.pop_back();
      }

      // Парсинг команд
      if (this->received_data_ == "WATER_ON") {
        this->publish_state(true);
        ESP_LOGI(TAG, "Water detected: ON");
      } else if (this->received_data_ == "WATER_OFF") {
        this->publish_state(false);
        ESP_LOGI(TAG, "Water detected: OFF");
      } else if (!this->received_data_.empty()) {
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
