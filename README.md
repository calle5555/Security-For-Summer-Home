<!-- This is a readme file -->
# QOL and small security for a summer home
Carl-William Lindkvist cl224di

This is an IoT project that is to be used to better understand how the humidity and temperature fluctuate in a summer home during the year. In addition, there will be an additional feature to detect the opening of a door to detect a possible break-in. The data collected from the different sensors are sent via wifi and stored in a database on a remote server and the climate data is visualized on a dedicated website. The alert of a possible break-in is done by a microcontroller with an attached display. I estimate that it takes approximately 10-20 hours to replicate this project by following this guide. 

# Objective

I decided upon this project because my summer home is located a couple of hours away from my house and if there would be a break-in, there would be no way of knowing until either a neighbor noticed or someone in the family travels there. This was the main idea for the project, then came the idea to have temperature and humidity readings of the indoor environment and to see how it changes throughout the year. These measurements can then be used during the winter to decide which setting the radiators should be on to prevent the water pipes from freezing thus causing them to break.

# Material

The following table includes all the components used in this project, a brief description of each component, and the cost. The name of the component includes a hyperlink to the page where it is bought.

| Component  | Image | Description | Cost |
| ------------- | ------------- | ------------- | ------------- |
| [Starter kit](https://www.electrokit.com/produkt/start-kit-applied-iot-at-linnaeus-university-2023/)  | ![No Imange](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/ac1fec45-1222-456c-a767-d94def8b2f1e) | Starter kit for IoT course at Linnaeus University  | 399 SEK |
| [Rasbperry Pi Pico WH*](https://www.electrokit.com/produkt/raspberry-pi-pico-wh/) | ![Raspberry Pi Pico WH](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/263d411e-f35d-4f7c-ac6e-512daa8f0a0c) | Microcontroller  |  |
| [ESP32](https://hitechchain.se/iot/ttgo/esp32-wifi-och-bluetooth-module-utvecklingskort-114-tums-lcd-skarm?gclid=CjwKCAjw44mlBhAQEiwAqP3eVuI8uFM8jQ0SkkTwqAWlrtL0_nbd6GTcObtFHGdmxQUSzshVb5UaoBoCtJsQAvD_BwE)  | ![ESP32](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/fcb042a4-15d6-4941-a676-385d580b3ebf) | Microcontroller with tft display  | 275 SEK  |
| [USB A-Micro USB*](https://www.clasohlson.com/se/USB--kabel-USB-A-till-Micro-USB-Clas-Ohlson/p/39-2043) | ![Micro USB cable](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/d02ab022-4450-4d88-9069-248ab195cb02) | Data transfer cable Raspberry Pi Pico |  |
| [USB A-USB C](https://www.clasohlson.com/se/Kort-USB-kabel-0,3m-USB-A-till-USB-C-Clas-Ohlson/p/39-2039) | ![USB C cable](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/9b5ae630-986b-4d22-ad0d-bc9624fb11ca) | Data transfer cable for ESP32  | 129 SEK |
| [Raspberry power supply micro USB](https://www.dustinhome.se/product/5010909896/micro-usb-power-supply-white?gclid=CjwKCAjw44mlBhAQEiwAqP3eVrXVGrr2Oz6APABtZlbEDU1-okSPfWW7zhps4Rwa4llhLa8Nx2YJVhoCzIAQAvD_BwE) | ![Power supply for pico](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/9c2f7bac-902d-4c3f-b5c6-c613e765bc17) | Power supply for Raspberry Pi Pico  | 155 SEK  |
| [Raspberry power supply USB C](https://www.dustinhome.se/product/5011172987/power-supply-153w-51v3a-eu-usb-c-black?ssel=true&gclid=CjwKCAjw44mlBhAQEiwAqP3eVu8B7xs51u0gUIL8eGargk7CXEYNuMRn2d_lWyXU77gdcn6OJhOTdxoCMPUQAvD_BwE) | ![Power supply ESP32](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/d841b6a3-711c-4b5c-9037-ce873b8a2c51) | Powersupply for ESP32  | 125 SEK |
| [DHT11*](https://www.electrokit.com/produkt/digital-temperatur-och-fuktsensor-dht11/) | ![DHT 11](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/8f1c6230-3b64-4955-a37d-d08f2089eb57) | Temperature and humidity sensor  |  |
| [Window Magnet Contact](https://www.electrokit.com/produkt/magnetisk-dorrkontakt-no/) | ![Magnet sensor](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/ec94c5ea-0a32-4425-baee-3dfe7aaa2795) | Sensor to detect opening of door or window  | 55 SEK  |
| [Breadboard*](https://www.electrokit.com/produkt/kopplingsdack-840-anslutningar/) | ![Breadboard](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/fe1f82b6-4591-4efc-8279-c6d9702492f7) | Breadboard with 840 connectors  |  |
| [Male to male jumper cables*](https://www.electrokit.com/produkt/labbsladd-40-pin-30cm-hane-hane/) | ![Jumper cables](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/e40a6134-6197-4686-99ad-6ea4124b1a07) | Jumper wires to wire the breadboard  |  |
| [330Ω Resistor*](https://www.electrokit.com/produkt/motstand-kolfilm-0-25w-330ohm-330r/) | ![Resistor](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/eac7213d-fba0-47f2-bb07-699f35f94f1a) | Resistor to regulate voltage  |  |
|   |  |   | **1138 SEK**  |

> **NOTE:** Objects marked with * are included in the starter kit and therefore have no unit price on it

The reason why I used an ESP32 with a TFT display in order to visualize the data is because I had one at home before. A cheaper choice for this would be another Raspberry Pi Pico W and attach colored LEDs and have them blinking when the alarm is triggered. The code does need to change for this which is not included in the repository.

# Computer setup

This section will cover the steps needed to properly install and configure the software. I will provide steps specifically for the Linux distribution Ubuntu.

## Install and setup Arduino IDE

In this section, the Arduino IDE will be installed and the necessary configurations will be done so that both the Pico and ESP32 boards can be used. I chose to write the code for the microcontrollers in the Arduino IDE because I find it comfortable to use. The Arduino IDE offers a stable environment for developing code and it is easy to upload and test the code on a microcontroller. I have previous experience with C and C++ which is another reason for my decision. I used [Arduino IDE 1](https://docs.arduino.cc/software/ide-v1) for this project but for future projects, I will be sure to use [Arduino IDE 2](https://docs.arduino.cc/software/ide-v2) which is an upgraded version of the IDE that is quite similar to VSCode.

1. Run the command `sudo apt update` to ensure that the source repositories for all packages are up to date

2. Run the command `sudo apt install arduino` to install the IDE

3. Launch Arduino IDE

4. Go to `File -> Preferences`

5. Click on the linked folder that ends with a `.txt` located at the bottom of the window, this is shown in the picture below
![Url to additional boards manager](https://github.com/calle5555/Portfolio/assets/84193411/d3d2bc18-696a-42a9-9c8b-5e6dc0f4d170)

7. Close the Arduino IDE

8. Open the file `preferences.txt` and find the line ´boardsmanager.additional.urls=´

9. Add these two links after the `=` with commas in between:
    - https://dl.espressif.com/dl/package_esp32_index.json
    - https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

10. Save and close the file

### Installations for Raspberry Pi Pico W

This section will cover the necessary parts in installing the software needed to connect the Raspberry Pi Pico W to the Arduino IDE.

1. Connect your device to a computer via a USB cable

2. Open up your Linux terminal

3. Run the following commands in the order they are written:
```bash
  wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh
```
```bash
  chmod +x pico_setup.sh
```
```bash
  ./pico_setup.sh
```
```bash
  sudo usermod -a -G dialout “$USER”
```

4. Reboot your computer

5. Open the Arduino IDE

6. Go to `Tools -> Board -> Raspberry Pi RP2040 Boards` and select `Raspberry Pi Pico W`

7. Go to `Files -> Examples -> Basics -> Blink`

8. Connect your ESP32 via USB and press upload. Upload is the second button from the left in the picture below

![Buttons in Arduino IDE](https://github.com/calle5555/Portfolio/assets/84193411/63300246-21ac-43d0-8901-9cfcd0f2e761)

9. If your onboard LED is not blinking or you get an error, see that you are using the correct serial port in `Tools -> Port`

### Installations for ESP32

This section will cover the necessary parts in installing the software needed to connect the ESP32 to the Arduino IDE and also how to install the libraries to be able to use the TFT display.

1. Open the Arduino IDE

2. Go to `Tools -> Board -> Boards Manager`

3. Search for ESP32 and install

4. Go to `Sketch -> Include Library -> Manage Libraries`

5. Search for ESP_eSPI and install

6. Go to the Arduino installation directory. My path for that is `Home/snap/arduino/85/Arduino`

7. Go to the `libraries/TFT_eSPI` folder and open the `User_Setup_Select.h`

8. Locate the line `#include <User_Setup.h>` and add `//` in front of it

9. Locate the line `//#include <User_Setups/Setup25_TTGO_T_Display.h>` and remove `//` in front of it

10. Go to `Tools -> Board -> ESP32 Arduino` and select the board `TTGO LoRa32-OLED`

11. Go to `Files -> Examples -> TFT_eSPI -> 160 x 128 -> TFT_Print_Test`

12. Connect your ESP32 via USB and press upload. Upload is the second button from the left in the picture below

![Buttons in Arduino IDE](https://github.com/calle5555/Portfolio/assets/84193411/63300246-21ac-43d0-8901-9cfcd0f2e761)

13. If your display is not showing data or you get an error, see that you are using the correct serial port in `Tools -> Port`

### Installation of libraries

This section covers the steps in order to install the Arduino libraries used in this project.

1. Open the Arduino IDE

2. Go to `Sketch -> Include Library -> Manage Libraries`

3. Search for the following libraries and install them:
```
WiFi
```
```
NTPClient
```
```
ArduinoJson
```
```
ArduinoMqttClient
```

## Visual Studio Code

To develop the website and also the server-side MQTT client, I used [visual studio code](https://code.visualstudio.com/). I used this IDE because it is plug-and-play, easy to use and it is easy to structure and keep track of the files and folders. It is also convenient that the IDE comes with many extensions that offer great quality-of-life services. The following steps describe how to download the IDE and also the plugins that I used.

1. Download dependencies
```bash
sudo apt install software-properties-common apt-transport-https
```
2. Import Microsoft’s GPG key
```bash
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
```
3. Enable the Vs Code repository
```bash
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
```
4. Install Vs Code
```bash
sudo apt install code -y
```
5. Open Vs Code by opening your terminal and running the command `code`

6. Open the extensions tab in Vs Code. To open, click on the icon that looks like the selected icon from the picture below

![Vs Code extension tab](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/1f03831b-2ac0-4c55-891d-305f803a071c)

7. Search for `Python` and press install on the extension published by Microsoft

## Install and setup Postgresql database

This section covers the installation of the database handler and the setup of the database and user.

1. The first step is to install the Postgresql packages by running the following command
```bash
sudo apt install postgresql postgresql-contrib
```
2. Next, log into the Postgresql prompt
```bash
sudo -u postgres psql
```
3. Create a new database with the default role. In the program, a database named `sensordata` is used, if you want to name the database differently you are free to do so, just remember to change it in the code as well.
```postgresql
CREATE DATABASE sensordata;
```
5. Next up is creating a new user and applying permissions so that the user can change the newly created database. Change the `<username>` and `<password>` to what you want
```postgresql
CREATE USER <username> WITH ENCRYPTED PASSWORD <password>;
GRANT ALL PRIVILEGE ON DATABASE sensordata TO <username>;
```
6. Exit the Postgresql terminal and log into the database with the newly created user
```postgresql
exit
```
```bash
psql -h localhost -d sensordata -U <username>
```
7. Create the tables that will be used in the project
```postgresql
CREATE TABLE DoorTrigger(id SERIAL PRIMARY KEY, Date TIMESTAMP);
CREATE TABLE DHT(id SERIAL PRIMARY KEY, Date TIMESTAMP, Temp DOUBLE PRECISION, Hum DOUBLE PRECISION);
CREATE TABLE DoorUnlocked(id SERIAL PRIMARY KEY, StartDate TIMESTAMP, EndDate TIMESTAMP);
```

## Install and setup Python libraries

This section will cover which Python libraries are needed for the program to work and how to install them. Since this tutorial assumes a Linux operating system, steps to install Python will not be included since it is pre-installed in the operating system.

### Installing pip

In order to install Python packages, the Python package installer [pip](https://pypi.org/project/pip/) must be installed. Run the following commands in order to install the latest version of pip.

```bash
sudo apt install python3-pip
```
```bash
sudo pip3 install --upgrade pip
```

### Install the required Python libraries

This project is broad and includes a wide range of libraries. The following steps are used in order to install all the packages that are required to run the full project.

1. Firstly, the prerequisites for the [psycopg2](https://www.psycopg.org/docs/) library must be installed by running the following command. This library is used to communicate with the Postgresql database
```bash
sudo apt install build-essential libpq-dev python3-dev
```
3. After the prerequisites are downloaded, the libraries can be installed with the following command
```bash
pip install django djangorestframework django-cors-headers tzdata psycopg2 paho-mqtt
```

## Install NPM and NodeJS
  
Installing NPM and NodeJS can be done in different ways. My preferred method is using the [Node Version Manager](https://github.com/nvm-sh/nvm), nvm for short. This allows the user to quickly change and install new versions of Node and NPM. The NPM libraries that I used will be installed once the repository is cloned.

1. Download the script that installs nvm
```bash
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.3/install.sh | bash
```
2. Close and reopen your terminal window in order to use nvm

3. Run the following command in order to list the available versions
```bash
nvm list-remote
```
4. Install the version you want. The latest [LTS](https://en.wikipedia.org/wiki/Long-term_support) version as of writing this is 18 which is what I use.
```bash
nvm install <version_number>
```
5. Switching between installed versions can be done by running
```bash
nvm use <version_number>
```

## Installing and setting up the MQTT broker

This section will cover how to set up the MQTT broker.

1. Install and activate the mosquitto broker service
```bash
sudo apt-get install mosquitto
```
2. Check if the service is running
```bash
service mosquitto status
```
3. Check the local IP address the broker is using by running the `ifconfig` command, this is used in the next section so keep it close by. Then look for the `inet` ip that is used by the broker. For me, this is the wireless network interface `wlo1` with ip `192.168.0.7`, the picture below shows how it looks for me

![Picture showing terminal running ifconfig command](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/a1c78aae-bdc4-42e4-bc61-e08395fcc52a)


## Cloning the repository and updating the code

It is now time to clone the repository and make the changes needed to run the program. These changes include, among other things, adding the secrets files, and changing the IP for the MQTT broker. I have used [Git](https://git-scm.com/) to handle [version control](https://www.atlassian.com/git/tutorials/what-is-version-control), and to much surprise, the code has been uploaded to [Github](https://en.wikipedia.org/wiki/GitHub). Much like Python, I will not show how to install Git seeing as it is included in most Linux distributions.

1. In order to pull the code to your computer, start by using the [cd](https://www.educative.io/answers/what-is-cd-in-linux) command to traverse to the directory where you want the directory of the project repository to be located

2. Clone the repository
```bash
git clone https://github.com/calle5555/Security-For-Summer-Home.git
```
3. Move into the repository
```bash
cd Security-For-Summer-Home
```
4. In this section I will provide the commands to create the files that hold the passwords and usernames. In the `<editor>` field, use your preferred editor like nano or gedit. I chose to create different wifi credential files for the ESP32 and the Pico since they will be located on different networks when the project is deployed. If you did not name the database `sensordata`, go into the `MqttClient/database.py` and change value of `dbname` to the name of your database
    1. Create the file for the database connection
        ```bash
        <editor> MqttClient/secrets.py
        ```
   2. Add the username and password
        ```bash
        dbUser = "<username for database user>"
        dbPass = "<password for database user>"
        ```
   4. Save and close file

   5. Create the file for the Raspberry Pi Pico W wifi credentials
        ```bash
        <editor> DataCollection/value_collection/secrets.h
        ```
   6. Add the wifi credentials
       ```python
       #define SSID "<wifi SSID>"
       #define password "<wifi password>"
       #define BROKER "<IP to MQTT broker>"
       ```
   7. Save and close file

   8. Create the file for the ESP32 wifi credentials
        ```c
        touch EspDoorAlarm/ShowOpenDoor/secrets.h
        ```
   9. Add the wifi credentials
       ```c
       #define SSID "<wifi SSID>"
       #define password "<wifi password>"
       #define BROKER "<IP to MQTT broker>"
       ```
   10. Save and close file

5. This section will show how to edit the setting file from django
    1. Open the settings file
        ```bash
        <editor> LocalHostPage/WebPage/WebPage/settings.py
        ```
    2. Find the lines that include `SECRET_KEY` and remove the `with open()` lines. Replace with
       ```python
       SECRET_KEY = "<my secret key>"
       ```
    3. Find the lines that handles the database connection and remove the `with open()` lines. Replace that and the `DATABASES` dictionary with
       ```python
       DATABASES = {
           'default': {
               'ENGINE': 'django.db.backends.postgresql',
               'NAME': '<name of database>',
               'USER' : '<name of database user>',
               'PASSWORD' : '<password of database user>',
               'HOST' : '127.0.0.1',
               'PORT' : '5432',
           }
       }
       ```
6. This section will show how to download the npm packages used to build the front end
    1. Use the `cd` command to go into the folder `Security-For-Summer-Home/LocalHostPage/frontend`
  
    2. Run the following command
       ```bash
       npm install
       ```

## Running the code

This section will showcase how to run the different parts of the program to be able to collect sensor data, visualize the data on the website, and also be able to see when the alarm is triggered. This section only covers the software and assumes that the hardware is set up as shown in the next section.

1. Starting the server MQTT client

    1. Open a new terminal window
  
    2. Use the `cd` command to get to the folder `Security-For-Summer-Home/MqttClient`
  
    3. Run the following command
       ```bash
       python3 mqtt_client.py
       ```
2. Start the backend of the website
   
    1. Open a new terminal window
  
    2. Use the `cd` command to get to the folder `Security-For-Summer-Home/LocalhostPage/WebPage`
  
    3. Run the following command
       ```bash
       python3 manage.py runserver
       ```
4. Start the frontend of the website
  
    1. Open a new terminal window
  
    2. Use the `cd` command to get to the folder `Security-For-Summer-Home/LocalhostPage/frontend`
  
    3. Run the following command
       ```bash
       npm run start
       ```
    4. A web page should open automatically
       
6. Flash the code to the Raspberry Pi Pico WH
    1. Open the file `Security-For-Summer-Home/DataCollection/value_collection/value_collection.ino`
  
    2. Connect the microcontroller to the computer
  
    3. Ensure that you have selected the correct port in the Arduino IDE

    4. Use the upload button to upload the code to the board
  
    5. Unplug the microcontroller from the computer
  
    6. Use the power supply to plug the controller into a wall outlet
  
7. Flash the code to the ESP32
    1. Open the file `Security-For-Summer-Home/EspDoorAlarm/ShowOpenDoor/ShowOpenDoor.ino`
  
    2. Connect the microcontroller to the computer
  
    3. Ensure that you have selected the correct port in the Arduino IDE

    4. Use the upload button to upload the code to the board
  
    5. Unplug the microcontroller from the computer
  
    6. Use the power supply to plug the controller into a wall outlet

# Hardware setup

This section will cover the wiring of the sensors via a circuit diagram and the electrical calculations for both microcontrollers and sensors.

## Circuit diagram
The picture below illustrates the circuit diagram for the Raspberry Pi Pico W. The ESP32 has no sensors connected to it so no diagram has been designed for it.

![hardwareSetup png](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/3c3b8efb-e9b0-4f12-9ab8-581718fefaa0)

This is a very simple and straightforward sketch since there are only two sensors connected to the microcontroller. The DHT in the diagram does, however, have the pins in a different order than the one used for the project. The pin order that is on the DHT used for this project is linked [here](https://www.electrokit.com/uploads/productfile/41015/DHT11.pdf). The door sensor has one pin in the power supply running along the breadboard. The other pin is connected to a 330Ω resistor which is connected to the ground, this pin is also connected to the data pin. The reason for connecting the pin to both the data pin and ground is to ensure proper data reading by creating a [pull-down](https://www.electronics-tutorials.ws/logic/pull-up-resistor.html) resistor. 

## Electrical calculations

This electrical calculation will be of the entire system, meaning, both microcontrollers and all sensors.

| Component  | Active | Standby
| ------------- | ------------- | ------------- |
| ESP 32 | 100mA |  |
| Raspberry Pi Pico WH | 60mA  |  |
| DHT 11 | 0.5mA - 2.5mA | 100uA-150uA |
| Magnetic Door Switch | - | - |

These following calculations are made under the assumption that the microcontrollers are running at all times and that the DHT 11 is running for 3 seconds every 10 minutes and is using the maximum current. 

$$ {{(100 + 60) \times 600 + 2.5 \times 3 + 0.15 + 597} \over 600} = 160.2$$ 

This means that the circuit is using approximately 160.2mA when active. Since I will not be using a battery, I will not calculate how long the circuit can operate using a battery.

# Platform

The choice of platform for this project was clear from the beginning and the reason for this is due to having access to a dedicated server. I created a self-hosted broker and on the same machine created a client that collects the data that is sent through MQTT and stores it in a local database. This client is also able to publish the stored data to the MQTT broker which forwards it to subscribing clients. I am using the [Mosquitto](https://mosquitto.org/) broker for this project and I chose Mosquitto because it is lightweight and has libraries both for the Arduino IDE and for Python.

This platform is very easy to expand and is something I wanted to do during this project but ran out of time. As of this moment, the project is running on my computer which is not what I originally planned since I am not able to place the Raspberry Pi Pico and access the platform at the same time. I am going to put this code on the dedicated server and implement MQTTS so that the messages are transferred with [TLS](https://sv.wikipedia.org/wiki/Transport_Layer_Security). 

# The code

This section will cover how the code

# Transmitting the data

I have used wifi as a network protocol to transfer the data. Since there is wifi both at my home and in my summer cabin, there is no need for LoRa to transmit data. MQTT is used as a transport protocol since it is easy to set up and also very lightweight. Since the broker is running locally on my computer, I did not need to make any changes to the config file for it to function. The microcontrollers are not sleeping at any point and that is because they are connected to power supplies which, in turn, are connected to wall outlets. The wifi range is also a non-issue since the microcontrollers are stationary at all times leading to them always having a network to connect to.

The temperature and humidity sensor is reading values every 10 minutes and transmits them via MQTT. The code below shows the sensor data being packeted into a JSON document and then published via the MQTT client.
```cpp
mqttClient.beginMessage(topicDht);
StaticJsonDocument<256> doc;
doc["Hum"]["int"] = int(dhtData[0]);
doc["Hum"]["dec"] = int(dhtData[1]);
doc["Temp"]["int"] = int(dhtData[2]);
doc["Temp"]["dec"] = int(dhtData[3]);
serializeJson(doc, mqttClient);
mqttClient.endMessage();
```
The sensor data is then routed by the broker to clients subscribing to the topic, which is only the server MQTT client running on my computer. I chose to use the JSON format because it is simple to both use and understand. Python dictionaries are much like JSON documents which leads to great compatibility and a simple way of parsing the incoming message for the server client that stores the data in the database.

The data from the window contact magnet is not published at a set interval, it is published when the two contacts are separated. The value published to the broker is only the number 1 since it only acts as a trigger, the exact value is not interesting. The code below shows how the values are published.
```cpp
mqttClient.beginMessage(topicMag);
mqttClient.print(1);
mqttClient.endMessage();
```
The Pico is not the only client that is publishing data. Both the ESP32 and the server client are publishing values as well. The ESP32 is publishing a value when the option of *No more alarms today* has been chosen and the server client publishes the dates that the alarm should not be triggered even if the door is opened. The dates are published every time the server client receives sensor data which is not optimal but the only semi-good idea that I could come up with. The reason why the dates are published that frequently is because updates to the dates needing to reach the Pico as soon as possible to not have an unwanted alarm triggered. The code for this looks much like the code for the other messages so they are not included here.

# Presenting the data

This section covers the different ways data is being visualized. The first section will be brief about the choice of database, the second section will cover the website used to display the data gathered from the DHT11 sensor and the third section will cover the visual alarm created on the ESP32.

## Choice of database

In order to store the data, a [Postgresql](https://www.postgresql.org/) database is used. I chose to create my own database instead of using a ready-made one such as [InfluxDB](https://www.influxdata.com/). I decided upon this based on my previous knowledge of [SQL](https://en.wikipedia.org/wiki/SQL) and because a server at [Certit Hosting](https://www.certit.se/) will be used to host the website and also store the sensor data so I will be able to store a large amount of data. The reason why I chose Postgresql as the database handler instead of others such as [Mimer](https://www.mimer.com/) or [MySQL](https://www.mysql.com/) is solely due to personal preference. 

The data is stored in the database the moment they are picked up by the server MQTT client. The following code shows the DHT11 values being stored.
```python
def logDHTValues(self, values):
        self.cur.execute("INSERT INTO DHT (date, temp, hum) VALUES (%s, %s, %s);", \
                        (dt.now(), values['temp'], values['hum']))
        self.conn.commit()
```
Here, the `conn` variable holds the connection to the database while the `cur` variable is the [database cursor](https://en.wikipedia.org/wiki/Cursor_(databases)). The database also has a table for dates that the alarm has been triggered and a table that keeps track of dates when the alarm is not to be triggered if the door is opened.

## Display of temperature and humidity
![Web page](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/e7daae49-eba5-43e1-91f9-b85237e53518)

The previous image shows what the web page looks like. As you can see, there are a few spikes in the data and that is due to the DHT11 sensor. I build this website using a [django](https://www.djangoproject.com/) backend and a [react](https://react.dev/) frontend. To communicate between the frontend and the backend, I use the [django rest framework](https://www.django-rest-framework.org/) to create the backend part of the api and [axios](https://axios-http.com/docs/intro) to create the frontend part. The code for this is included in quite a few files and it is located [here](https://github.com/calle5555/Security-For-Summer-Home/tree/main/LocalhostPage). The graph is created using a line chart from [CanvasJS](https://canvasjs.com/react-charts/).

The following code shows how the backend part of the API is created. The following lines are contained in different files but I place them in the same block for ease of reading.
```python
router = routers.DefaultRouter()
router.register(r'dhts', views.DhtView, 'dht')

urlpatterns = [
    path('api/', include(router.urls)),
]

from .models import Dht

class DhtView(viewsets.ModelViewSet):
    serializer_class = DhtSerializer
    queryset = Dht.objects.all()
```
Here we can see that a `router` object is created that registers the path `dhts` and attach the data from the `DhtView` in the `urlpatterns` variable, the routers url is then attached to `api/` which makes the full api path `api/dhts`. The `DhtView` is calling a serializer class that decides which fields from the database table are supposed to be included in the API data. A `queryset` is then created containing all objects in the `Dht` database table.

```js
const getAllData = (lower, upper) => {
    axios.get("/api/dhts/")
        .then((res) => {
          const d = formatData(res.data, lower, upper)
          getData(d);
        })
        .catch((err) => console.log(err));
  }
```
Here, a function called `getAllData` is created which includes the frontend API call using `axios`. The API url in this call is `/api/dhts/` and this matches the url created in the backend. The resulting data from the API call is then forwarded to the function `formatData` which has been discussed previously. This function is called when the page is loaded by the `useEffect` hook provided in React.
```js
useEffect(() => {
    getAllData(undefined, undefined);
  }, []);
```
The call to `getAllData` is with both the `lower` and `upper` values set to `undefined` meaning that all data points should be visualized. The [date pickers](https://mui.com/x/react-date-pickers/date-picker/) shown below are used to set the start and end date for which data points should be visualized.

![Date pickers](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/d2c3100f-aed8-42d0-8ffe-e3d6be22da3a)

A function, `handleChanges`, is called when either the start or end date picker window is exited. 
```js
function handleChanges(e){
    if(startDate.$d.getTime() === oldStart.$d.getTime() && endDate.$d.getTime() === oldEnd.$d.getTime()){
      return
    }
    
    setOldStart(startDate);
    setOldEnd(endDate);

    getAllData(startDate.$d.getTime(), endDate.$d.getTime());
}
```
The function checks if the date in the pickers has changed and if they have, the `getAllData` function is called with the lower bound being the [epoch](https://en.wikipedia.org/wiki/Unix_time) time of the start date picker and the upper bound is the epoch time for the end date picker. This way, the graph is updated with new data points. This also triggers the API call which will make sure that the most recent sensor readings are visualized, if they are in the time window specified, that is.

The picture below shows the date pickers in action.

![Date pickers in action](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/09b00dc4-b66c-4855-9568-5bda7335f72c)

I have also implemented tooltips that show temperature, humidity, and the date and time when the measurement was taken.
```js
toolTip: {
        shared: true,
        contentFormatter: function(e){
            var content = " ";
            for (var i = 0; i < e.entries.length; i++) {
                content += e.entries[i].dataSeries.name 
                        + " " + "<strong>" 
                        + e.entries[i].dataPoint.y + "</strong>";
                content += "<br/>";
            }
            content += e.entries[0].dataPoint.x + "<br/>";
            return content
        }
},
```
This code creates a shared tooltip between the two measurements, this means that both "dots" will be highlighted when I hover over one of them. I then create the tooltip by adding one row for temperature, one row for humidity, and one row for the date. The tooltip is illustrated in the picture below.

![Tooltip in action](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/862a97db-d6c9-4274-a02b-056e11e85e6c)

## Alarm display

The ESP32 is being used to notify when an alarm has been triggered. It is connected as an MQTT client and subscribes to the topic used for alarm triggers. I will only provide pictures of the states, the code can be found [here](https://github.com/calle5555/Security-For-Summer-Home/blob/main/EspDoorAlarm/ShowOpenDoor/ShowOpenDoor.ino). There are four states of the microcontroller, the default state is that the display is black and static.![Default display](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/87cf389e-e792-4b68-81b7-25b6244b6915)

The second state is that the alarm has been triggered and the display is flashing red and yellow with a warning prompt. ![Red display](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/00249791-59c2-4ac4-a26c-9961f46b14bf) ![Yellow display](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/d709d953-0e09-43ae-b375-c2def6a44759)

The third state is that the alarm has been disabled and an option to remove triggers for that day is shown. ![Alarm disabled](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/5d0b9c34-0962-4046-9685-346a08f63f70)

The fourth and final state is that the alarm has been disabled for the day. ![No more alarms today](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/416c0b1e-f19d-4f16-b608-caef614ccaef)

The display will return to the default state if the user disables the alarm and another button is not pressed for 10 seconds.  

# Finalizing the design

![Final design](https://github.com/calle5555/Security-For-Summer-Home/assets/84193411/8df16b39-83a3-4fc0-a3d7-43e1830eeac7)

The image above shows the entire hardware setup for the project. This project works very well on a local level, the DHT11 collects data that is then stored in a database for the website to visualize it. The door alarm triggers when it is supposed to and accounts for the dates when it is not supposed to sound the alarm. I am very happy with the functionality of it all but I was not able to deploy the website on time. I spent a lot of time trying to place the front- and backend into Docker containers and use Nginx to deploy the website but I could not get the API to collect the data from the backend. This will be something that I continue working on to get it up and running. I will also have the dedicated server act as the MQTT broker and implement TLS both for MQTT as well as for the website. If I redid the project from scratch, I would have begun by using Docker containers for the different aspects of the server to simplify the transition from localhost to using a domain and actually deploying the website.

## Showcasing the design

[This](https://www.youtube.com/watch?v=qPqxxI4oH2U) is a video showcasing the full project.
