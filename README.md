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

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/block_diagram.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/block_diagram.png" width = "300"></a>

## Hardware: Circuit Diagram

<a href = "https://images.roberttakacs.ro/github/robotica_proiect/electrical_diagram.png" target = "_blank"><img src = "https://images.roberttakacs.ro/github/robotica_proiect/electrical_diagram.png" width = "300"></a>

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

(TODO)

# Results

(TODO)

# Conclusions

(TODO)
