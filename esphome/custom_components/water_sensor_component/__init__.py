import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNER = ["@ivamax-create"]
DEPENDENCIES = ["uart"]

water_sensor_component_ns = cg.esphome_ns.namespace("water_sensor_component")
WaterSensorComponent = water_sensor_component_ns.class_(
    "WaterSensorComponent", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(WaterSensorComponent),
        cv.Required(uart.CONF_UART_ID): cv.use_id(uart.UART_COMPONENT),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
