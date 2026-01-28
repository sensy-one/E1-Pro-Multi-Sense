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

> Note: An optional Bosch BME688 air quality add-on for the E1 Pro is currently in development and will be released soon. This add-on will enable monitoring of eCO₂, VOCs, IAQ, and gas resistance, providing broader air quality insight similar to the S1 Pro.

**Ambient light and UV sensing**

The integrated Lite-On LTR-390UV sensor measures both illuminance (Lux) and UV index (UVI), enabling smart lighting control and sun exposure awareness based on real-time ambient conditions.

## ⚡ From Power On to Home Assistant

The E1 Pro supports Power over Ethernet (PoE) and is automatically discovered by Home Assistant when connected via Ethernet.

If PoE is not available, the device can be powered using 5V USB-C in combination with an RJ45 Ethernet connection.

When using Wi-Fi mode, the E1 Pro can be powered via USB-C or PoE.  
Wi-Fi setup is handled using Bluetooth (Improv) or the built-in access point.

If your Home Assistant setup supports Bluetooth (Improv):
- The E1 Pro will be automatically discovered under Devices & Services.
- Click Add, enter your Wi-Fi credentials, and you're done.

If Bluetooth is not available:
- The E1 Pro will start a Wi-Fi access point named I am Sensy!.
- Connect to it and open http://192.168.4.1 in your browser.
- Enter your Wi-Fi details, click Save, and it will connect to your network.
- The device will then appear in Home Assistant as a discovered device.

## 📍 Best Placement Practices

**Recommended mounting height**

Wall mounting mode:
- 1.6 to 2.6 meters from the floor

Top-down (ceiling) mounting mode:
- 2.0 to 3.0 meters from the floor

**Placement tips:**
- Ensure a clear line of sight to the monitored area — walls, plants, or furniture can reduce detection accuracy.
- Avoid placing near large metal objects (such as fridges, pipes, or servers), as they can reflect mmWave signals.
- Avoid direct airflow from HVAC vents or fans to maintain stable environmental readings.
- Mount away from heat sources to prevent temperature distortion.

## 🧪 CO₂ Calibration (SCD40 add-on)

For faster or more precise calibration, you can use the Forced Calibration button in Home Assistant.

**To calibrate CO₂ manually:**
- Place the sensor in fresh outdoor air.
- In Home Assistant, click Forced Calibration on the E1 Pro.
- The sensor will set a new baseline of 426 ppm (current global outdoor CO₂ level).

**Temperature offset:**
The SCD40 temperature offset is factory-calibrated based on the enclosure design to compensate for internal heat. This offset can also be manually adjusted in Home Assistant if needed to fine-tune temperature accuracy for your environment.

## 🎯 Get in the Zone

The E1 Pro supports up to 3 detection zones and 1 exclusion zone — all configurable as custom polygons with up to 8 points each.  
Instead of adjusting multiple number entities, zones can be configured visually using the Zone Editor tool.

The Zone Editor is available as an official Home Assistant add-on or Docker image and can be found [here](https://github.com/sensy-one/home-assistant-addons).

## 📶 Flashing Wi-Fi Firmware

To switch the E1 to Wi-Fi mode, you need to flash the Wi-Fi factory firmware manually.

**Flash Wi-Fi factory firmware**
- Download the latest Wi-Fi factory firmware from the [releases page](https://github.com/sensy-one/E1-Pro-Multi-Sense/releases).
- Connect the E1 to your computer using a USB-C cable.
- Open the ESPHome web flasher: https://web.esphome.io/
- Click Connect and select the correct COM port.
- Choose Install and select the Wi-Fi factory firmware file you downloaded.
- Once flashing is complete, disconnect and power the E1 using USB-C or PoE.
- The E1 will start Wi-Fi provisioning using Bluetooth (Improv) or its built-in access point.

## 🔄 Firmware on the Fly

Keep your E1 up to date with regular OTA updates.  
We continuously improve performance and add new features to keep your device reliable and future-ready.

**Install OTA Updates**
- Download the latest OTA firmware from the [releases page](https://github.com/sensy-one/E1-Pro-Multi-Sense/releases).
- In Home Assistant, go to Devices & Services, ESPHome.
- Select your E1 and click Visit under Device Info to open the web interface.
- Scroll down to OTA Update, choose the firmware file, and click Update.

> Tip: If the page times out during upload, simply refresh the page and try again.

## 🛠 Troubleshooting

If your sensor isn’t behaving as expected, reinstalling the factory firmware can help you start fresh.

**Install Factory Firmware**
- Download the latest factory firmware from the [releases page](https://github.com/sensy-one/E1-Pro-Multi-Sense/releases).
- Connect the E1 to your computer using a USB-C cable.
- Open the ESPHome web wizard: https://web.esphome.io/?dashboard_wizard
- Click Connect and select the correct COM port.
- Choose Install, select the firmware file you downloaded, and click Install again.

## 💬 Let’s Connect

Your feedback helps us improve. Whether you’ve found a bug, need help, or want to suggest a feature — we’re listening.

**Discord**
- Join the community and get support on our [Discord server](https://discord.gg/TB78Wprn66).

**GitHub Issues**
- Found a bug or have a suggestion? Report it on our [GitHub issues page](https://github.com/sensy-one/E1-Pro-Multi-Sense/issues).
