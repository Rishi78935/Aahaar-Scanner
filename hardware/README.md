# Hardware

## Current prototype

| Component | Role |
|---|---|
| ESP32-S3 | Embedded controller and data acquisition |
| AS7341 | Multi-channel spectral sensor |
| OLED / 2.8-inch TFT | User interface |
| Controlled illumination | Repeatable optical measurement |
| Li-ion battery | Portable power |

## AS7341 connection

| AS7341 | ESP32-S3 |
|---|---:|
| SDA | GPIO 4 |
| SCL | GPIO 5 |
| GND | GND |
| VIN | Appropriate sensor supply |

The exact optical geometry and illumination setup should remain fixed during a dataset collection session. Changes in distance, ambient light, or illumination can change the measured spectrum.
