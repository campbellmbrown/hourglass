# Hourglass

## Setup

Install packages:

```bash
arduino-cli core update-index --config-file arduino-cli.yaml
arduino-cli core install Seeeduino:nrf52 --config-file arduino-cli.yaml
arduino-cli lib install U8g2
pip install adafruit-nrfutil
```

Build:

```bash
cmake -S . -B build
cmake --build build
```
