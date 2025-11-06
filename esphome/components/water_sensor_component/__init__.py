import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

water_sensor_ns = cg.esphome_ns.namespace("water_sensor_component")
WaterSensorComponent = water_sensor_ns.class_("WaterSensorComponent", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(WaterSensorComponent),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
