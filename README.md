## 🚀 Sensy-One E1 Pro Multi Sense

The all-in-one presence and environmental sensor for Homey Pro and Home Assistant.

![Sensy-One Banner](https://github.com/sensy-one/E1-Pro-Multi-Sense/blob/main/assets/images/S1_Pro_Multi_Sense.webp)

E1 Pro combines presence detection, air-quality monitoring and ambient light sensing in one compact device. It connects locally to Homey Pro or Home Assistant through ESPHome.

## ✨ Standout Specs

**Local smart home integration**

Connect E1 Pro to Homey Pro or Home Assistant over your local network using ESPHome. Follow [Getting Started](#-getting-started) to set up your connection and add the sensor.

**Powered by ESP32-C3**

At its core, the E1 Pro uses the ESP32-C3 module — offering reliable Wi-Fi, Bluetooth Low Energy, and Ethernet support, low power consumption, and compatibility with ESPHome, Homey Pro and Home Assistant.

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

In Homey, use the sensor's LED Flow cards to set power, colour and brightness. In Home Assistant, use its light entity.

**Built-in buzzer**

The integrated MLT-8530 buzzer delivers clear audio alerts at 80–90 dB and 2.7 kHz, perfect for notifications, warnings, or presence feedback. In Homey, use the buzzer Flow cards; in Home Assistant, use its switch.

**Comprehensive environmental monitoring**

The E1 Pro is equipped with the Bosch BME280 sensor, providing air pressure measurements for environmental monitoring and system integration.

> Note: Temperature and humidity readings from the BME280 are disabled due to self-heating effects inside the enclosure. Air pressure data is used to support the optional SCD40 add-on, which provides accurate CO₂, temperature, and humidity measurements without self-heating impact.

**High-precision CO₂ sensing (add-on)**

For highly accurate air quality measurements, the E1 Pro supports an optional Sensirion SCD40 add-on module. This add-on provides precise CO₂, temperature, and humidity readings and connects directly to the main PCB via a Molex mezzanine connector — no soldering required.

> Note: An optional Bosch BME688 air quality add-on for the E1 Pro is currently in development and will be released soon. This add-on will enable monitoring of eCO₂, VOCs, IAQ, and gas resistance, providing broader air quality insight similar to the S1 Pro.

**Ambient light and UV sensing**

Earlier E1 Pro units use the Lite-On LTR-390UV with illuminance (Lux) and UV index (UVI); newer units use the LTR-F216A with illuminance only. At startup, the firmware reads the sensor's full PART_ID at I²C address `0x53`, register `0x06`. UVI is exposed only for the documented LTR390 ID (`0xB2`); the LTR-F216A (`0xB1`), an unrecognized ID, or a failed read hides UVI and disables UV sampling. The existing lux calculation, calibration, entity names, and IDs are preserved. The UV-offset control is unchanged.

If Home Assistant already registered a UVI entity on a unit without UV hardware, that old entry may remain unavailable after updating. Disable that entry once in Home Assistant; newly discovered units without UV hardware will not offer a UVI entity.

## ⚡ Getting Started

### Connect to your network

Connect E1 Pro to your network with an Ethernet cable. Use PoE for power, or a 5 V USB-C supply alongside Ethernet.

If you use the [Wi-Fi firmware](#-flashing-wi-fi-firmware), connect to the **I am Sensy!** access point, open `http://192.168.4.1`, and save your 2.4 GHz Wi-Fi credentials.

### Add to Homey Pro

1. Install the [SENSY-ONE app](https://homey.app/en-nl/app/com.sensy-one/SENSY-ONE/test/).
2. Make sure E1 Pro and Homey Pro are on the same local network.
3. In Homey, select **Devices → + → SENSY-ONE → E1 Pro**, then choose your sensor.

Measurements are available in Flows and Insights. Home Assistant is not required. The app is under review and can already be installed through the test link above.

### Add to Home Assistant

Once connected to your network, E1 Pro appears under **Settings → Devices & services**. Select the discovered ESPHome device and complete the setup.

SCD40 and BME688 add-on entities are disabled by default, including their calibration and temperature-offset controls. If you use an add-on, open the E1 Pro device in Home Assistant, show its disabled entities, and enable the entities for the installed module. The BME688 IAQ classification remains `unknown` until a valid IAQ measurement is available.

This default applies when Home Assistant first adds the entities. Existing entities keep their enabled/disabled setting after a firmware update. Home Assistant can also restore that setting when a device is removed and added again, so removing the device or performing a factory reset does not reliably apply the new default. Disable unused add-on entities manually if needed.

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

In Homey, use the SCD40 calibration control in the sensor's advanced settings and follow its instructions.

**In Home Assistant:**
- Place the sensor in fresh outdoor air.
- In Home Assistant, click Forced Calibration on the E1 Pro.
- The sensor will set a new baseline of 426 ppm (current global outdoor CO₂ level).

**Temperature offset:**
The SCD40 temperature offset is factory-calibrated based on the enclosure design to compensate for internal heat. Adjust it in the sensor's advanced settings in Homey or through its offset entity in Home Assistant.

## 🎯 Get in the Zone

E1 Pro supports three detection zones and one exclusion zone, drawn as polygons with up to eight points.

### Homey Pro

Open **Settings → Apps → SENSY-ONE → App settings** in Homey. Select your sensor, draw the zones and save. Presence and target-count readings appear for each configured detection zone.

### Home Assistant

Use the [SENSY-ONE Zone Editor](https://github.com/sensy-one/home-assistant-addons), available as a Home Assistant add-on or Docker image.

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
- Open the sensor's local IP address in your browser. In Home Assistant, you can also use **Visit** on its ESPHome device page.
- Scroll down to OTA Update, choose the firmware file, and click Update.

> Tip: If the page times out during upload, simply refresh the page and try again.

## 🛠 Troubleshooting

**Not found in Homey?** Check that the sensor and Homey Pro are on the same local network and that mDNS discovery is allowed.

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
