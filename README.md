# Project for DMP

## Core Concept
This project implements a Remote Weather Monitoring Station using two ESP32 microcontrollers communicating over a private, local Wi-Fi network. The system is designed to monitor environmental conditions: temperature, humidity, pressure, and light intensity in real-time.

## Materials
- 2 x ESP32 board
- 2 x USB cable
- wires
- 2 X breadboards
- 1 x DHT22 
- 1 x LDR
- 1 x 10 kΩ resistor
- 1 x BMP280/BME280 

## Connections
The ESP32 that manages the sensors:
  - 3V3 pin to the red rails of the breadboards
  - GND pin to the blue rails of the breadboards

The DHT22 sensor:
  - VCC connected to the red rail
  - GND connected to the blue rail
  - OUT connected to the D4 pin of the ESP32 board

The BME/BMP280 sensor:
  - VCC connected to the red rail
  - GND connected to the blue rail
  - SCL connected to pin D22
  - SDA connected to pin D21
  - CSB connected to the red rail (for I2C mode)
  - SDO connected to the blue rail (sets adress to 0x76)

The LDR sensor and resistor:
  - One leg of the LDR connected to the red rail
  - Other leg of the LDR connected to a row on the breadboard
  - One leg of the resistor connected to the blue rail
  - Other leg of the resistor connected to the same row as the LDR on the breadboard
  - A wire connects the row on the breadboard to pin D34

## Functionality
The project works based on a Client-Server model consisting of two units: 

The receiver (receiver.ino):    
 &ensp; This ESP32 acts as the central hub, creating a private Wi-Fi network named "DMP_Project". It listens for incoming messages on port 80 and displays received data on the serial monitor.  

The client (sensors.ino):  
&ensp;  The remote monitoring unit, collects the environmental data from the sensors (DHT22, BMP280, LDR), formats the readings into a data packet, and sends them to the receiver every 5 seconds.  
&ensp;  The DHT22 sensor measures the temperature and humidity, the BMP280 measures the athmospheric pressure and sends the value over the I2C bus, and the LDR measures the intensity of light.
