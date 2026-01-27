import esphome.codegen as cg  
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_UART_ID,
)
from esphome.components import sensor, uart, number, select
 
DEPENDENCIES = ["uart"]
AUTO_LOAD = ["sensor", "number", "select"]

ns = cg.esphome_ns.namespace("e1_pro")
LD2460 = ns.class_("LD2460", cg.Component, uart.UARTDevice)

CONF_EXCLUSION_ZONE_POINTS_COUNT = "exclusion_zone_points_count"
EXCLUSION_ZONE_KEYS = [f"exclusion_zone_p{i}_{axis}" for i in range(1, 9) for axis in "xy"]
CONF_INSTALLATION_METHOD = "installation_method"
CONF_INSTALLATION_ANGLE = "installation_angle"
CONF_INSTALLATION_HEIGHT = "installation_height"
CONF_DETECTION_SENSITIVITY = "detection_sensitivity"
CONF_SIDE_RANGE = "side_range"
CONF_TOP_RANGE = "top_range"
SENSOR_KEYS = [
    "target1_x", "target1_y", "target1_angle", "target1_distance",
    "target2_x", "target2_y", "target2_angle", "target2_distance",
    "target3_x", "target3_y", "target3_angle", "target3_distance",
    "target4_x", "target4_y", "target4_angle", "target4_distance",
    "target5_x", "target5_y", "target5_angle", "target5_distance",
]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(LD2460),
        cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),

        **{cv.Required(key): sensor.sensor_schema() for key in SENSOR_KEYS},

        cv.Optional(CONF_EXCLUSION_ZONE_POINTS_COUNT): cv.use_id(number.Number),
        **{cv.Optional(key): cv.use_id(number.Number) for key in EXCLUSION_ZONE_KEYS},
        cv.Optional(CONF_INSTALLATION_METHOD): cv.use_id(select.Select),
        cv.Optional(CONF_INSTALLATION_ANGLE): cv.use_id(select.Select),
        cv.Optional(CONF_INSTALLATION_HEIGHT): cv.use_id(select.Select),
        cv.Optional(CONF_DETECTION_SENSITIVITY): cv.use_id(select.Select),
        cv.Optional(CONF_SIDE_RANGE): cv.use_id(number.Number),
        cv.Optional(CONF_TOP_RANGE): cv.use_id(number.Number),
    }
).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for key in SENSOR_KEYS:
        await sensor.register_sensor(getattr(var, key), config[key])

    if CONF_EXCLUSION_ZONE_POINTS_COUNT in config:
        count_var = await cg.get_variable(config[CONF_EXCLUSION_ZONE_POINTS_COUNT])
        cg.add(var.set_exclusion_zone_points_count(count_var))

    for key in EXCLUSION_ZONE_KEYS:
        if key in config:
            point_var = await cg.get_variable(config[key])
            setter_name = "set_" + key
            cg.add(getattr(var, setter_name)(point_var))

    if CONF_INSTALLATION_METHOD in config:
        sel = await cg.get_variable(config[CONF_INSTALLATION_METHOD])
        cg.add(var.set_installation_method_select(sel))
    if CONF_INSTALLATION_ANGLE in config:
        sel = await cg.get_variable(config[CONF_INSTALLATION_ANGLE])
        cg.add(var.set_installation_angle_select(sel))
    if CONF_INSTALLATION_HEIGHT in config:
        sel = await cg.get_variable(config[CONF_INSTALLATION_HEIGHT])
        cg.add(var.set_installation_height_select(sel))
    if CONF_DETECTION_SENSITIVITY in config:
        sel = await cg.get_variable(config[CONF_DETECTION_SENSITIVITY])
        cg.add(var.set_sensitivity_select(sel))
    if CONF_SIDE_RANGE in config:
        num = await cg.get_variable(config[CONF_SIDE_RANGE])
        cg.add(var.set_side_range_select(num))
    if CONF_TOP_RANGE in config:
        num = await cg.get_variable(config[CONF_TOP_RANGE])
        cg.add(var.set_top_range_select(num))