# PlantieGuard

---

**PlantieGuard** is a tool that allows you to better take care of your plants at home, simply by using your smartphone.

### How does it do this?

The device, placed in the soil of your plant's pot, will measure atmospherical data from the ambient and the soil, and will transmit this data directly to your smartphone.
The device holds a small tank of water, and therefore allows you to water your plant simply by using your phone, at the press of a button.
Just in case you happen to forget, the device automatically waters the soil to keep your plantie well and healthy.

A detailed history of the plant's progress is kept in the memory of the application, so that from your phone you can see the intervals at which the plant has been watered, and the progress of the ambiental parameters.

Especially if your plant is water-dependant or you're away from home for a longer period of time, **PlantieGuard** can save you a lot of troubles!

### What did the idea start from?

I have many plants in my home, but I also happen to leave for longer periods of time rather often. Therefore, I always need someone to come in and water my plants once in a while, and it's not pleasant to always have to ask people to do this. This is what made me think of a device that could solve this problem, allowing me to take care of my plants from far away, or allowing it to take care of my plants by itself.

### Why do I think it's useful?

I think many people are in the situation that they simply forget to water their plants, because life is full and stressful and when something doesn't come up to your face to tell you what it needs, it's easy to forget. As we're connected more and more to our mobile devices, having push notifications to tell us that our plants are in trouble is something that for sure helps as a reminder.

# General Description

(TODO)

# Hardware Design

The hardware of the project consists of two device categories, one for the functionality and measurement, namely the sensors used, and one for the interactivity - an LCD to present the user with information about the device's status, or instructions to connect to its local access point.

## Hardware: Functionality and Measurement

Two sensors are used for data collection: the [SEN0193 Soil Moisture Sensor](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193) and the [HTU21D Temperature and Relative Humidity sensor](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf). These sensors allow periodic collection of air humidity, air temperature and soil humidity, information which is sent through the microcontroller's WiFi module to a remote server for storage and display through HTTP requests.

### SEN0193 Moisture Sensor

This sensor functions as a variable resistor, and therefore its information can be read constantly through the Analog data pin. Based on the documentation, analog output values are as following:

- Dry: 520 - 430
- Wet: 430 - 350
- Water: 350 - 260

These values have an inverse proportionality with the actual humidity of the soil, therefore a lower value represent more humid soil. In the process of setting up the device, its values were measured both in dry air (~480) and in water (~280)

### HTU21D Temperature and Relative Humidity sensor

This sensor communicates with the microcontroller through the I2C protocol

## Hardware: Interactivity

An [Arduino LCD](https://wiki-content.arduino.cc/documents/datasheets/LCDscreen.PDF) is used to display information to the user.

## Hardware: Block Diagram

(TODO)

## Hardware: Circuit Diagram

(TODO)

## Hardware: Bill of Materials

| Component                                       | Description                          | Links                                                                                                                                                                                                                  |
| ----------------------------------------------- | ------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Arduino Uno R4 Wifi                             | Arduino Board with WiFi capabilities | [Datasheet](https://docs.arduino.cc/resources/datasheets/ABX00087-datasheet.pdf)<br>[Arduino.cc](https://store.arduino.cc/en-ro/products/uno-r4-wifi?srsltid=AfmBOoqDBcUMsSjlqWBa6vhja294psPYgXWZh30cK8ZwA0iyJFgAmb-0) |
| SEN0193 Soil Moisture Sensor                    | Analog soil moisture sensor          | [Datasheet](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193)                                                                                                                                      |
| HTU21D Temperature and Relative Humidity sensor | Multimodal sensor, I2C connection    | [Datasheet](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf)<br>(Cleste.ro)[https://cleste.ro/senzor-temperatura-i-umiditate-htu21d.html]                                                                     |
| Arduino LCD                                     |                                      | [Datasheet](https://wiki-content.arduino.cc/documents/datasheets/LCDscreen.PDF)                                                                                                                                        |

# Software Design

(TODO)

# Results

(TODO)

# Conclusions

(TODO)

# Journal

(TODO)
