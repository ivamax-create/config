import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, uart
from esphome.const import CONF_ID, CONF_DEVICE_CLASS, CONF_NAME, CONF_UART_ID

DEPENDENCIES = ["uart"]
CODEOWNER = ["@ivamax-create"]

water_sensor_component_ns = cg.esphome_ns.namespace("water_sensor_component")
WaterSensorBinarySensor = water_sensor_component_ns.class_(
    "WaterSensorBinarySensor", binary_sensor.BinarySensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(
    WaterSensorBinarySensor,
    device_class=binary_sensor.DEVICE_CLASSES_AND_ICONS["moisture"],
).extend(
    {
        cv.GenerateID(): cv.declare_id(WaterSensorBinarySensor),
        cv.Required(uart.CONF_UART_ID): cv.use_id(uart.UART_COMPONENT),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await binary_sensor.register_binary_sensor(var, config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
