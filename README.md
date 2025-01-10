# PlantieGuard

---

**PlantieGuard** is a tool that allows you to better take care of your plants at home, simply by using your smartphone.

### How does it do this?

The device, placed in the soil of your plant's pot, will measure atmospherical data from the ambient and the soil, and will transmit this data directly to your smartphone.
Then, the mobile device can let you know when the plant needs to be watered, so you never forget to do it yourself.

A detailed history of the plant's progress is kept in the memory of the application, so that from your phone you can see the intervals at which the plant has been watered, and the progress of the ambiental parameters.

Especially if your plant is water-dependant, you happen to often forget, or you tend to overwater your plants, **PlantieGuard** can save you a lot of troubles!

### What did the idea start from?

I have many plants in my home, but I also happen to leave for longer periods of time rather often. Therefore, I always need someone to come in and water my plants once in a while, and it's not pleasant to always have to ask people to do this. This is what made me think of a device that could solve this problem, allowing me to take care of my plants from far away, or allowing it to take care of my plants by itself.

Sadly, I've found that I was not able to setup hardware that would allow watering the plants automatically, so I've stuck to a design that will announce you whenever the plant needs water.

### Why do I think it's useful?

I think many people are in the situation that they simply forget to water their plants, because life is full and stressful and when something doesn't come up to your face to tell you what it needs, it's easy to forget. As we're connected more and more to our mobile devices, having push notifications to tell us that our plants are in trouble is something that for sure helps as a reminder.

# General Description

The microcontroller boots up, connects to a specified WiFi network and begins sending data collected from its sensors to a remote server.

This server allows its users to see when their plants need to be watered, when was the last time they were watered, and many other statistical information to help ease their plant-taking process.

# Hardware Design

The hardware of the project consists of two device categories, one for the functionality and measurement, namely the sensors used, and one for the interactivity - an LCD to present the user with information about the device's status, or instructions to connect to its local access point.

## Hardware: Functionality and Measurement

Two sensors are used for data collection: the [SEN0193 Soil Moisture Sensor](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193) and the [HTU21D Temperature and Relative Humidity sensor](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf). These sensors allow periodic collection of air humidity, air temperature and soil humidity, information which is sent through the microcontroller's WiFi module to a remote server for storage and display through HTTP requests.

### SEN0193 Moisture Sensor

This sensor functions as a variable resistor, and therefore its information can be read constantly through the Analog data pin. Based on the documentation, analog output values are as following:

- Dry: 520 - 430
- Wet: 430 - 350
- Water: 350 - 260

These values have an inverse proportionality with the actual humidity of the soil, therefore a lower value represent more humid soil. In the process of setting up the device, its values were measured both in dry air (~480) and in water (~280).

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/moisture-sensor.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/moisture-sensor.png" width = "300"></a>

### HTU21D Temperature and Relative Humidity sensor

This sensor communicates with the microcontroller through the I2C protocol. The sensor requires a specific hardware setup to ensure proper communication with the microcontroller. Following the sensor's datasheet guidelines, the + and - pins are connected together with a 104 capacitor, as close as possible to the pins. The DA and CL pins must both be pulled-up with an appropriate pull-up resistor - the ones used in this setup are 5.1kOhm resistors.

The DA and CL pins are connected to the microcontroller's I2C SDA and SCL pins, respectively.

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/temp-sensor.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/temp-sensor.png" width = "300"></a>

### 9V Battery

The device is powered by a 9V battery, connected to to the Microcontroller's Vin and GND pins to provide constant power to the system and its peripherals.

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/battery.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/battery.png" width = "300"></a>

## Hardware: Interactivity

An [Arduino LCD](https://wiki-content.arduino.cc/documents/datasheets/LCDscreen.PDF) is used to display information to the user. Based on the [Arduino LCD guide](https://docs.arduino.cc/learn/electronics/lcd-displays/), the LCD screen request an additional 220 Ohm resistor for the LED+ pin and a 10k potentiometer connected to the V0 pin to ensure good LCD contrast for visibility.

The other pins are connected as follows:

- VSS, R/W and LED- to GND
- VDD to 5V
- LED+ to 5V with a 220 Ohm resistor
- RS to digital pin 12
- E to digital pin 11
- DB4 to digital pin 5
- DB5 to digital pin 4
- DB6 to digital pin 3
- DB7 to digital pin 2

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/lcd.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/lcd.png" width = "300"></a>

## Hardware: Block Diagram

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/block-diagram.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/block-diagram.png" width = "300"></a>

## Hardware: Circuit Diagram

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/electrical-diagram.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/electrical-diagram.png" width = "300"></a>

### Circuit Diagram Notes

## Hardware: Bill of Materials

| Component                                       | Description                                                        | Links                                                                                                                                                                                                                  |
| ----------------------------------------------- | ------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Arduino Uno R4 Wifi                             | Arduino Board with WiFi capabilities                               | [Datasheet](https://docs.arduino.cc/resources/datasheets/ABX00087-datasheet.pdf)<br>[Arduino.cc](https://store.arduino.cc/en-ro/products/uno-r4-wifi?srsltid=AfmBOoqDBcUMsSjlqWBa6vhja294psPYgXWZh30cK8ZwA0iyJFgAmb-0) |
| SEN0193 Soil Moisture Sensor                    | Analog soil moisture sensor                                        | [Datasheet](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193)                                                                                                                                      |
| HTU21D Temperature and Relative Humidity sensor | Multimodal sensor, I2C connection                                  | [Datasheet](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf)<br>[Cleste.ro](https://cleste.ro/senzor-temperatura-i-umiditate-htu21d.html)                                                                     |
| Arduino LCD                                     |                                                                    | [Datasheet](https://wiki-content.arduino.cc/documents/datasheets/LCDscreen.PDF)                                                                                                                                        |
| 9V Battery                                      | Kodak 9V Battery                                                   |                                                                                                                                                                                                                        |
| WL 10K potentiometer                            | Potentiometer used for LCD contrast                                | [Datasheet](https://components101.com/resistors/potentiometer)                                                                                                                                                         |
| 104 Capacitor                                   | Capacitor used for HTU21D                                          |                                                                                                                                                                                                                        |
| Resistors                                       | 5.1KOhm and 220Ohm resistors used for HTU21D and LCD, respectively |                                                                                                                                                                                                                        |

# Software Design

The software built to power the application consists of three separate services collaborating:

- The software on the Arduino Microcontroller to connect to a WiFi network and send data to the remote server;
- The endpoints where the remote server acknowledges a new device and accepts incoming data
- The web application where the end-user can visualize their plants' data.

## Arduino Software

In this repository, in the [PlantieGuard](PlantieGuard/) folder resides the Platformio project used to compile the source code for the controller. There, the [src](PlantieGuard/src/) folder contains the main functions of the program (setup and loop), while the [lib](PlantieGuard/lib/) folder contains all the written libraries to power the application.

Additionally, the [ArduinoJson](https://docs.arduino.cc/libraries/arduinojson/), the [LiquidCrystal](https://github.com/fmalpartida/New-LiquidCrystal) and the [HTU2xD_SHT2x_Si70xx](https://github.com/enjoyneering/HTU2xD_SHT2x_Si70xx) libraries are installed for functionality.

### Setup and Main Loop

On first initialisation, the Arduino board initialises the libraries written to handle the EEPROM, the Sensors, and the LCD, and creates or retrieves the device's UUID from the flash memory and retrieves the saved WiFi network, if it exists.

If the WiFi network does not exist, the device creates an access point using the PGAccessPoint class and instructs the user to connect to the network. Once connected, the user is instructed to access an url that will open up a setup page on their browser, allowing the user to offer WiFi connection credentials to the PlantieGuard board and then register their account to see PlantieGuard data.

The board attempts to connect to the network with the received WiFi credentials (or the ones stored in the EEPROM), and saves them to the memory if successful. It sends an acknowledge request to the API server and waits for a response to verify that everything is in order. If so, the device begins sending its sensor data to the API server every 10 seconds.

### Deep dive into the Access Point class

The [PGAccessPoint](PlantieGuard/lib/AccessPoint/) is one of the more complex classes written for the PlantieGuard software. Whenever a client accesses its local IP, it sends an HTML 1.1 document, consisting of a styled page with a form to request connection credentials.

If the client sends a request to the /setup endpoint, it checks the HTTP request and parses for the sent ssid and password. If this data is received correctly, it sends an HTML 1.1 document containing a button to the mobile application where the user, based on the device's UUID, may register an account or connect to their existing account.

### Deep dive into the PG_EEPROM class

The [PG_EEPROM](PlantieGuard/lib/PG_EEPROM/) class allows the saving and retrieving of the UUID and WiFi credentials on the device's flash memory. It uses a custom format to check for data validity, saving the UUID at the first byte of memory, with a header of an 'u0' and two zeroes after, and directly after saves the credentials, like this:

```
s0[ssid_variable_length]00p0[password_variable_length]00
```

In this way, it is ensured that data stored is valid. If no valid data is found, it is requested or generated.

### Used libraries

| Library + Link                                                             | Description                                                                                                                                                                                                                                                                                                    |
| -------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [ArduinoJson](https://docs.arduino.cc/libraries/arduinojson/)              | "A simple and efficient JSON library for embedded C++". Used for parsing incoming JSON data from the PlantieGuard API server. Not critical functionality, because the PlantieGuard does not actually use the response for taking actions. Would have been used if actual watering would have been implemented. |
| [LiquidCrystal](https://github.com/fmalpartida/New-LiquidCrystal)          | Standard Arduino library for the LCD. Several functions have been created to improve the LCD's functionality and allow text longer than the LCD's width to be displayed.                                                                                                                                       |
| [HTU2xD_SHT2x_Si70xx](https://github.com/enjoyneering/HTU2xD_SHT2x_Si70xx) | Library for the I2C Humidty & Temperature sensor. Provides functions to greatly ease the use of the I2C sensor, which has rather complicated functions.                                                                                                                                                        |

### Functionalities from the labs

1. The Serial Monitor was extensively used for debugging the project (Lab 1 - USART. Debugging)
2. The Soil Humidty sensor sends its sensor data as an analog value, which is parsed to transform from a 0% to a 100% humidity. (Lab 4 - ADC)
3. The Humidity & Temperature sensor uses I2C to function. (Lab 6 - I2C)

### Calibration of Sensors

The I2C sensor (Humidity & Soil) did not need calibration.

The Soil Humidty sensor's output is an analog value. The device's (very very concise) datasheet proposes measuring the output value in air and the output value while submerged in water. These values are used as edges for a mapping between 0 and 100, representing 0 (dry) and 100 (water) to use for soil measurements. As seen in the PG_Sensors.h file

```
const uint16_t MOISTURE_UPPER_DRY = 500;
const uint16_t MOISTURE_LOWER_WET = 200;

float PG_Sensors::getSoilHumidity(uint8_t *error)
{
    *error = 0;
    uint16_t soil_moisture_out = analogRead(MOISTURE_PIN);

    float val_a = soil_moisture_out - MOISTURE_LOWER_WET;
    float val_b = MOISTURE_UPPER_DRY - MOISTURE_LOWER_WET;

    float percentage_value = (1 - (float)val_a / val_b) * 100;

    return percentage_value;
}
```

## API endpoints

The code for the API where the Arduino board sends acknowledgements and sensor data is found in the [html_api](HTTPServer/html_api/) folder.

The structure is very simplistic and exposes three endpoints:

- ack, where the server expects a UUID, checks it for validity and checks if it exists or not already on the server
- data, where the server expects sensor data from a specific UUId
- info, which offers server information, used as a fallback endpoint

! This document server can be tested locally by running the makefile in the [HTTPServer](HTTPServer/) folder. Requires docker-compose

## Web Application

The code for the Web Application is found in the [html_app](HTTPServer/html_app/) folder, and is written using a custom PHP MVC created by me.

The first page that the user will encounter is the register page, where they're sent once they first setup their PlantieGuard device. The controller expects a validated UUID, which it saves in to the session storage and uses to link the device to the account. Once registered, the user is automatically logged in.

If ever logged out, the user may connect to their account from the login page.

Once logged in, the user may see current live sensor information from their PlantieGuard only, on the home page, loaded by the data/data/current controller. They can also see their PlantieGuard device history, to get a sense of the past measurments of the plant's environment.

### Validating a UUID

A user may not register with an invalid UUID. The way the website validates a UUID is the following:

1. Once the PlantieGuard performs an ACK request to the /ack endpoint of the API, the server will verify the provided UUID. If the UUID is new and correct, it will be added to the pg_devices table. Providing an already existent UUID will not produce any change in the database.
2. The PlantieGuard will send the user to the /account/register/uuid/[uuid] endpoint of the application website. If the UUID is not present, they will be prompted to set up their PlantieGuard device first. If the UUID appears in the pg_devices table and there is no associated user to the UUID, it will allow the user to register. Otherwise, the user is sent to the login page to connect to their already-existent account.

# Results

(TODO)

# Future Implementations

## Automated Watering System

An extremely relevant system that is missing from the current form of the project is an automated watering system. Two variants are possible to implement, and both require various additions to both the software and the hardware of the project. The first one would be to have the PlantieGuard decide by itself whenever it should water the plant, and the other one would involve the user actioning a button on the application website to announce the PlantieGuard that it must water the plant.

### Hardware

A water tank needs to be added to the device, with an actionable water pump. Additionally, there should exist a sensor to verify the remaining quantity of water in the water tank, for prompting the user that they need to refill the water tank. An even more advanced implementation would connect to the water pumps of the house, but we're going a bit too far with this one...

### Software

The use of ArduinoJSON allows the Arduino Board's processor to read the responses from the API server. The proposed implementation is a polling one. As the watering is not a time-delicate operation, the server could, whenever the PlantieGuard sends parameter data, to add a response field announcing that the PlantieGuard should water the plant. If this field is received, the PlantieGuard would action the pump for a fixed amount of time (or a variable one, based on the Server's response). This method would be more reliable because different plants require different watering and humidity conditions, and having the PlantieGuard decide by itself whenever to water a plant would most likely fail without use of manual tuning tools.

## Power Management

The device should not have the WiFi and the LCD modules turned on at all times. A much more power-efficient implementation would completely turn off the device after every data send and restart it using a watchdog timer or through the existent reset button. The device saves connection data to its ROM, so the user need not worry about the PlantieGuard not being able to reconnect to the server to send data. If data is sent every 10 minutes, the device would be fully powered only for a few seconds during that time.

## Account Improvements

The account system lacks several important tools, such as account editing (e-mail, password, name), the "password forgotten" setting or the "remember me" tool. These are not difficult to implement (except the password forgotten, which involves using a mailing server), but as the project's scope is not Web Development, they were not a priority for the project.

## Multiple PlantieGuards per Account

In a real-use case, a user may desire to use multiple PlantieGuards and administer them all at once, through the same account. A future implementation would allow a user to associate a PlantieGuard to an existing account. Then, they could add images, names, or set at what parameters a plant should be watered by the PlantieGuard for more automation.
