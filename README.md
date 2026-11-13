# Safer Campus Environment Monitor
## 1. Project Overview

The Safer Campus Environment Monitor is an Arduino-based prototype designed to monitor environmental conditions using a gas/smoke sensor and a temperature sensor.

The system evaluates sensor readings and communicates environmental status through LEDs and an audible alarm.

## 2. Problem Statement

Environmental hazards such as smoke, gas leaks and excessive temperatures can pose risks in indoor environments.

This project explores an affordable electronic monitoring system that can provide an early warning when monitored conditions exceed predefined thresholds.

## 3. Project Objectives

- Monitor gas/smoke sensor readings.
- Measure surrounding temperature using an NTC thermistor.
- Classify environmental conditions into NORMAL, WARNING and CRITICAL states.
- Provide visual and audible alerts.

## 4. Hardware Components

- Arduino Uno
- MQ-2 gas/smoke sensor
- NTC thermistor
- 10 kΩ fixed resistor
- Green LED
- Yellow LED
- Red LED
- Buzzer
- Connecting wires and breadboard

## 5. System Operation

The Arduino reads the gas sensor and thermistor values.

It evaluates the readings against predefined thresholds and selects an environmental state.

| State | Indication 
| NORMAL | Green LED 
| WARNING | Yellow LED
| CRITICAL | Red LED and buzzer 

## 6. Software

The project is programmed using Arduino C/C++.

The software includes sensor-reading functions, temperature calculations, condition evaluation and output-control functions.

## 7. Current Development Status

The prototype control logic has been implemented and tested in simulation.

Physical testing and sensor calibration should be documented separately when completed.

## 8. Limitations

- MQ-2 readings are not calibrated gas concentrations in ppm.
- Temperature accuracy depends on the thermistor specifications and calibration.
- The project is an educational prototype, not a certified safety or fire detection system.

## 9. Future Improvements

- Sensor calibration.
- Improved temperature measurement accuracy.
- Data logging.
- Wireless monitoring.
- Enclosure design.

