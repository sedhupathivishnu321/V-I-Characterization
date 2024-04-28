# V-I-Characterization
A microvolt V-I characterization instrument with Instrumentational Amplifiers and matlab UI
# Arduino Data Plotter App

The Arduino Data Plotter app is a MATLAB application designed to plot real-time data received from an Arduino over a serial connection. It allows you to visualize voltage and current data from sensors or other sources connected to the Arduino.

## Features

- Select a serial port and baud rate for communication with the Arduino.
- Start and stop plotting data in real-time.
- Plot voltage vs. current on a dynamic graph.
- Save the plot as an image (PNG or JPEG) or as a CSV file.
- Easily customize the baud rate and data parsing for your specific Arduino setup.

## Requirements

- MATLAB R2019b or later
- Arduino board connected to your computer via USB
- Data being sent from the Arduino in the format "Voltage: x.xx V, Current: x.xx A"

## Usage

1. Connect your Arduino to your computer via USB.
2. Run the MATLAB script `ArduinoDataPlotter.m`.
3. Select the appropriate serial port and baud rate from the dropdown menus.
4. Click the "Start" button to begin plotting data.
5. Click the "Stop" button to stop plotting data.
6. Use the "Save Image" button to save the plot as an image file.
7. Use the "Save CSV" button to save the data as a CSV file.

## Troubleshooting

- If no serial ports are available, ensure that your Arduino is connected properly and recognized by your computer.
- Check the format of the data being sent from the Arduino to match the expected format in the MATLAB script.

