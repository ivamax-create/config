#include "binary_sensor.h"
#include "esphome/core/log.h"
#include <cstring>

namespace esphome {
namespace water_sensor_component {

static const char *TAG = "water_sensor_component";

void WaterSensorBinarySensor::setup() {
  if (this->uart_parent_ == nullptr) {
    ESP_LOGE(TAG, "UART parent not set!");
    this->mark_failed();
    return;
  }
  // Ініціалізуємо індекс буфера
  this->buffer_index = 0;
  memset(this->buffer, 0, MAX_BUFFER_SIZE);
  ESP_LOGI(TAG, "Water Sensor BinarySensor initialized successfully");
}

void WaterSensorBinarySensor::dump_config() {
  ESP_LOGCONFIG(TAG, "UART Water Sensor:");
  ESP_LOGCONFIG(TAG, "  Device Class: moisture");
  ESP_LOGCONFIG(TAG, "  Expects: 'WATER_ON' or 'WATER_OFF' from UART");
}

void WaterSensorBinarySensor::loop() {
  while (this->uart_parent_ != nullptr && this->uart_parent_->available()) {
    uint8_t byte;
    if (this->uart_parent_->read_array(&byte, 1) <= 0)
      break;
    char c = static_cast<char>(byte);

    // Якщо прийшов '\n' — обробляємо рядок
    if (c == '\n') {
      // Видаляємо '\r' якщо є
      if (this->buffer_index > 0 && this->buffer[this->buffer_index - 1] == '\r') {
        this->buffer[this->buffer_index - 1] = '\0';
      } else {
        // Нуль-термінуємо
        this->buffer[this->buffer_index] = '\0';
      }

      // Тепер порівнюємо отриманий рядок
      if (this->buffer_index > 0) {
        if (strcmp(this->buffer, "WATER_ON") == 0) {
          this->publish_state(true);
          ESP_LOGI(TAG, "Water detected: ON");
        } else if (strcmp(this->buffer, "WATER_OFF") == 0) {
          this->publish_state(false);
          ESP_LOGI(TAG, "Water detected: OFF");
        } else {
          ESP_LOGD(TAG, "Received unknown data: %s", this->buffer);
        }
      }

      // Очищаємо буфер
      this->buffer_index = 0;
      memset(this->buffer, 0, MAX_BUFFER_SIZE);
    } else if (c != '\r') {
      // Додаємо символ в буфер, якщо місце є
      if (this->buffer_index < (MAX_BUFFER_SIZE - 1)) {
        this->buffer[this->buffer_index++] = c;
      } else {
        ESP_LOGW(TAG, "Buffer overflow detected, clearing");
        this->buffer_index = 0;
        memset(this->buffer, 0, MAX_BUFFER_SIZE);
      }
    }
  }
}

}  // namespace water_sensor_component
}  // namespace esphome
