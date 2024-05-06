# Welcome to the Weather Arduino Wi-Fi project.

This project is a small demonstration of many networking concepts put in practice, such as Edge Computing and MQTT.

# Acknowledgment
We would like to thank [rsaikali](https://github.com/rsaikali/openweather-mqtt) for providing the Python script that allows us to get weather information of a city.

## Dependencies
To fully run this project, you'll need the following
* [Arduino IDE](https://www.arduino.cc/en/software)
* [Docker](https://www.docker.com/products/docker-desktop/)

You'll also need the Python dependencies needed to run rsaikali's code. Please refer to their repository to install them.

### Arduino Libraries
You might need to install a few Arduino libraries to successfully compile the code. These are the libraries that you should install. You may do this in the Arduino IDE itself.
* Arduino Uno WiFi DevEd Library by Arduino.
* LiquidCrystal I2C by Frank de Brabander.
* Adafruit Unified Sensor by Adafruit.
* DHT sensor library by Arduino
* HC-SR04 by Dirk Sarodnick.
* PIR by Rob Tillaart.

Once you have successfully installed all these programs and librearies, it's time to configure your project.

## Configuration
Before running the project, you'll need to configure the Arduino's Wifi as it is intended. You are free to configure however you feel fit.
### Arduino Wifi
1. First off, connect your laptop to the Arduino's Wifi.
2. Enter into your browser the gateway address of the Arduino.
3. Go to `Wifi` and connect your Arduino to a router with an Internet connection and that you have control. It's recommended to use a mobile hotspot.
4. Note down the IP address that it was assigned into the network.
5. Connect your laptop or computer into the same network as the Arduino's.
6. Go into the browser again and navigate into the Arduino's new IP.
7. In the Arduino's control panel, go to `Connectivity` and enable `MQTT`.
8. The `Server hostname or IP` will be the same as the one where the docker will be running. Most probably you'll end up entering your laptop's IP.

In the `openweather/export_mqtt.sh` have some configuration variables that you'll need to set up. 
* For instance, you'll need an [Openweather](https://openweathermap.org/) account and obtain an App_ID. When you have the export_mqtt.sh open, you'll know where to place it.
* Next, you'll need the city's ID that you want to request the information. For that, I suggest you look up more in [Openweather's website](https://openweathermap.org/current#geocoding) for more details.
* `MQTT_SERVICE_HOST` will be the IP or hostname of the MQTT publisher.
* The rest of the parameters are pretty much self explanatory.

### Arduino Circuit
Please take a look at the code in mqtt/mqtt.ino. This code, especially in the first lines where the `#define` declarations are, give a hint of how the circuit will be mounted.

## Running the Docker
For the commands related to the docker, we recommend running them with privileges or `sudo`.
We utilize an already built-up Docker for the MQTT services: [eclipse-mosquitto](https://hub.docker.com/_/eclipse-mosquitto). To download it and install it, you can simply do the following:
```
docker pull eclipse-mosquitto
```
We already added a configuration file for you (`mosquitto.conf`) so you don't have to worry about that.

To run it, you'll have to use the following command:
```
docker run -p 1883:1883 -v ./mosquitto.conf:/mosquitto/config/mosquitto.conf eclipse-mosquitto:latest
```
Hopefully by now, you'll be seeing a ton of messages of the Arduino connecting and disconnecting from the MQTT. This is fine.

To see the process ID of the running docker:
```
docker ps
```
To subscribe to a `TOPIC`:
```
docker exec -it <DOCKER_PID> mosquitto_sub -h IP_HOST -t “TOPIC”
```
To publish a message:
```
docker exec -it <DOCKER_PID> mosquitto_pub -h IP_HOST -t “TOPIC” -m “MESSAGE”
```
