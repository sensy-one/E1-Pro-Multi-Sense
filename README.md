## 🚀 Sensy-One E1 Pro Multi Sense

The all-in-one open-source sensor designed for Home Assistant, refined through real-world user feedback.

![Sensy-One Banner](https://github.com/sensy-one/E1-Pro-Multi-Sense/blob/main/assets/images/E1_Pro_Multi_Sense.jpg)

The Sensy-One E1 Pro Multi Sense is an open-source presence and environmental sensor, built from the ground up with Home Assistant in mind. After extensive prototyping, firmware tuning, and valuable input from users and smart home enthusiasts, the E1 Pro brings together reliable presence detection, real-time air quality monitoring, and ambient light sensing — all in one compact, Home Assistant-ready device!

## ✨ Standout Specs

**Seamless Home Assistant integration**

The E1 Pro is automatically discovered by Home Assistant when running in PoE (Ethernet) mode.

If you choose the Wi-Fi firmware, the device will be automatically discovered via BLE Improv.  
If BLE discovery is not available or fails, the E1 Pro will start its own wireless access point to complete the setup and connect the sensor to Home Assistant — no additional tools required.

**Powered by ESP32-C3**

At its core, the E1 Pro uses the ESP32-C3 module — offering reliable Wi-Fi, Bluetooth Low Energy, and Ethernet support, low power consumption, and full compatibility with ESPHome and Home Assistant integrations.

**Modular mounting options**

The E1 Pro supports modular built-in mounting options for flexible installation, including flush in-wall and in-ceiling add-ons for a clean, integrated finish.

> Note: These built-in mounting options are currently in development and will be released soon, including STEP and STL files for DIY 3D printing, with the option to purchase the mounting add-ons if you don’t have access to a 3D printer.

**Precision-engineered enclosure**

The custom enclosure is optimized for reliable sensing and long-term operation, featuring minimal mmWave signal interference, optimized airflow across sensors, and a passive cooling design. The resin-printed enclosure ensures a clean, high-quality finish and measures 65 × 52 × 30 mm.

**Advanced mmWave presence sensing**

Built around the Hi-Link LD2460 mmWave presence radar module, the E1 Pro continuously tracks presence in real space, including position, distance, and movement. The system supports tracking of up to five targets simultaneously with fast, stable updates at approximately 30 ms.

Dedicated wall and ceiling detection modes ensure accurate sensing for different mounting positions. With support for three configurable detection zones and one exclusion zone, you can precisely control where presence should trigger automations and where it should be ignored.

The radar supports multiple operating modes:
- Side mode with a detection range of up to 6 m, a 120° horizontal field of view, and a 35° vertical pitch angle
- Top-down mode with full 360° coverage and up to an 8 m diameter

Adjustable sensitivity levels (High, Medium, Low) allow fine-tuning for different environments, delivering reliable and responsive presence detection.

**BLE presence & proximity**

The E1 Pro includes a built-in BLE Proxy for Bluetooth-based presence and proximity detection. The BLE Proxy can be enabled or disabled as needed, allowing seamless integration with Home Assistant and other BLE-based tracking solutions for accurate room-level detection of smartphones, wearables, and tags.

**Full-color status LEDs**

The E1 Pro features four front-facing full-color RGB LEDs, providing clear visual feedback for status indication, presence detection, alerts, and ambient lighting effects.

**Built-in buzzer**

The integrated MLT-8530 buzzer delivers clear audio alerts at 80–90 dB and 2.7 kHz, perfect for notifications, warnings, or presence feedback.

**Comprehensive environmental monitoring**

The E1 Pro is equipped with the Bosch BME280 sensor, providing air pressure measurements for environmental monitoring and system integration.

> Note: Temperature and humidity readings from the BME280 are disabled due to self-heating effects inside the enclosure. Air pressure data is used to support the optional SCD40 add-on, which provides accurate CO₂, temperature, and humidity measurements without self-heating impact.

**High-precision CO₂ sensing (add-on)**

For highly accurate air quality measurements, the E1 Pro supports an optional Sensirion SCD40 add-on module. This add-on provides precise CO₂, temperature, and humidity readings and connects directly to the main PCB via a Molex mezzanine connector — no soldering required.

**Ambient light and UV sensing**

The integrated Lite-On LTR-390UV sensor measures both illuminance (Lux) and UV index (UVI), enabling smart lighting control and sun exposure awareness based on real-time ambient conditions.