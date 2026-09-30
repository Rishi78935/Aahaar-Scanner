# Aahaar Scanner

Portable spectral sensing prototype for fruit quality and ripeness analysis using an ESP32-S3 and AS7341 spectral sensor.

## Project status

**Working prototype / active development**

## What it does

Aahaar Scanner collects multi-channel spectral measurements from fruit samples and records them with fruit and ripeness labels for later analysis and machine-learning experiments.

### Current hardware

- ESP32-S3
- AS7341 11-channel spectral sensor
- OLED / TFT display integration
- Controlled illumination and optical enclosure
- Li-ion battery system

### Sensor interface

| Signal | ESP32-S3 |
|---|---:|
| SDA | GPIO 4 |
| SCL | GPIO 5 |
| Serial | 115200 baud |

## Data pipeline

```text
Fruit sample
    ↓
Controlled illumination
    ↓
AS7341 spectral measurement
    ↓
ESP32-S3
    ↓
Serial data stream
    ↓
Python data logger
    ↓
Labeled dataset
    ↓
Analysis / ML
```

## Repository structure

```text
.
├── firmware/
│   └── data_collector.ino
├── tools/
│   └── datacollector.py
├── dataset/
│   └── aahaar_dataset.txt
├── calibration/
│   ├── white_reference.txt
│   └── calibration_notes.txt
├── mechanical/
│   ├── cap.gcode.3mf
│   ├── main-body.gcode.3mf
│   └── support.gcode.3mf
└── README.md
```

## Firmware

The ESP32-S3 initializes the AS7341 over I2C, configures integration time and gain, accepts fruit/ripeness labels over serial, and streams sensor readings while capture is active.

The current firmware uses:

- ATIME: 100
- ASTEP: 999
- Gain: 128×
- Serial baud rate: 115200
- Capture interval: approximately 100 ms

## Python data collector

`tools/datacollector.py` communicates with the ESP32-S3 over a serial port. It sends labels, starts/stops capture, timestamps incoming measurements, and stores the collected data.

Before running it, install the serial dependency:

```bash
pip install pyserial
```

Update `PORT` in the script to match the connected ESP32-S3.

## Calibration

The repository includes the recorded calibration data and a white-reference measurement used during the prototype's sensor setup.

## Dataset

The included dataset contains raw spectral measurements with labels. The data is experimental and should not be interpreted as a scientifically validated classifier or as proof of organic certification.

## Engineering notes

The project is being developed as an optics-first sensing system. Repeatable illumination, fixed sensor-to-sample geometry, calibration, data quality, and validation are treated as prerequisites for reliable machine-learning results.

## Next development steps

- Improve repeatability of the optical enclosure
- Expand labeled samples across fruit types and ripeness stages
- Validate calibration across sessions
- Compare classical ML models using held-out samples
- Integrate the final display and battery system
- Report measured classification performance

## License

Project code and data are provided for educational and experimental use.
