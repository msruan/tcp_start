
# Wireless communication applications for IoT

A simple web server to send data of BitDogLa by HTML⚒️.

EmbarchaTech work, task of Unit 2




## Features

- BitDogLab buttons and joystick read;
- External PIR sensor read;
- Directory ```/drivers``` to organize peripheral access code. 
## Screenshots

![App Screenshot](https://z06ourw62g.ufs.sh/f/ycLYT3qk3ITUVd9ncUPj1lYQMKsZvuByU583Pn27iRrOwdWb)


## Environment Variables

To run this project, you will need to setup the following "environment variables" to ```config.g``` file

`wifi_config`: Struct to set your WiFi network credentials that will be used to serve the app on.

`PIR_SENSOR_GPIO_PIN`: Macro to define the GPIO pin where you connected the PIR sensor, if you intend to test its read. By default, pin 8 is setted.


## Installation

To be able to start development, make sure that you have the following prerequisites installed:
- C/C++ build tools
- [Raspberry Pi Pico W extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico), or _pico-sdk_ equivalent config.

Connect your BitDogLab in your machine by USB on BOOTSEL mode to be able to write code. 
Click on _Run_ option on Raspberry extension to build and write code on BDL.

## Roadmap

- Use ```file(GLOB)``` to get ```/drivers``` source files.
- Improve page styling
- Optimize updating data refresh method

