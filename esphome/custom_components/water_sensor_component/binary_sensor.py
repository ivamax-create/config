import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, uart
from esphome.const import CONF_ID

# Визначення простору імен C++
water_sensor_uart_ns = cg.esphome_ns.namespace('water_sensor_component') 
WaterSensorComponent = water_sensor_uart_ns.class_('WaterSensorComponent', binary_sensor.BinarySensor, cg.Component)

# Визначення схеми конфігурації
CONFIG_SCHEMA = binary_sensor.BINARY_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(WaterSensorComponent),
    # Вимагаємо, щоб користувач надав ID для UART
    cv.Required('uart_id'): cv.use_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA)

# Функція для генерації коду
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await binary_sensor.register_binary_sensor(var, config)

    # Отримуємо об'єкт UART-компонента
    parent = await cg.get_variable(config['uart_id'])

    # Викликаємо метод set_uart_parent у вашому C++ класі
    cg.add(var.set_uart_parent(parent))