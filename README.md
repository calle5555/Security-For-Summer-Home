<!-- This is a readme file -->
# QOL and small security for a summer home
Carl-William Lindkvist cl224di

This is an IoT project that is to be used to better understand how the humidity and temperature fluctuate in a summer home during the year. In addition, there will be an additional feature to detect the opening of a door to detect a possible break-in. The data collected from the different sensors are sent via wifi and stored in a database on a remote server and the climate data is visualized on a dedicated website. The alert of a possible break-in is done by a microcontroller with an attached display. I estimate that it takes approximately 10-20 hours to replicate this project by following this guide. 

# Objective

I decided upon this project because my summer home is located a couple of hours away from my house and if there would be a break-in, there would be no way of knowing until either a neighbor noticed or someone in the family travels there. This was the main idea for the project, then came the idea to have temperature and humidity readings of the indoor environment and to see how it changes throughout the year. These measurements can then be used during the winter to decide which setting the radiators should be on to prevent the water pipes from freezing thus causing them to break.

# Material

The following table includes all the components used in this project, a brief description of each component, and the cost. The name of the component includes a hyperlink to the page where it is bought.

| Component  | Description | Cost |
| ------------- | ------------- | ------------- |
| [Starter kit](https://www.electrokit.com/produkt/start-kit-applied-iot-at-linnaeus-university-2023/)  | Starter kit for IoT course at Linnaeus University  | 399 SEK |
| [Rasbperry Pi Pico WH*](https://www.electrokit.com/produkt/raspberry-pi-pico-wh/)  | Microcontroller  |  |
| [ESP32](https://hitechchain.se/iot/ttgo/esp32-wifi-och-bluetooth-module-utvecklingskort-114-tums-lcd-skarm?gclid=CjwKCAjw44mlBhAQEiwAqP3eVuI8uFM8jQ0SkkTwqAWlrtL0_nbd6GTcObtFHGdmxQUSzshVb5UaoBoCtJsQAvD_BwE)  | Microcontroller with tft display  | 275 SEK  |
| [USB A-Micro USB*](https://www.clasohlson.com/se/USB--kabel-USB-A-till-Micro-USB-Clas-Ohlson/p/39-2043)  | Data transfer cable Raspberry Pi Pico |  |
| [USB A-USB C](https://www.clasohlson.com/se/Kort-USB-kabel-0,3m-USB-A-till-USB-C-Clas-Ohlson/p/39-2039)  | Data transfer cable for ESP32  | 129  |
| [Raspberry powersupply micro USB](https://www.dustinhome.se/product/5010909896/micro-usb-power-supply-white?gclid=CjwKCAjw44mlBhAQEiwAqP3eVrXVGrr2Oz6APABtZlbEDU1-okSPfWW7zhps4Rwa4llhLa8Nx2YJVhoCzIAQAvD_BwE)  | Powersupply for Raspberry Pi Pico  | 155 SEK  |
| [Raspberry powersupply USB C](https://www.dustinhome.se/product/5011172987/power-supply-153w-51v3a-eu-usb-c-black?ssel=true&gclid=CjwKCAjw44mlBhAQEiwAqP3eVu8B7xs51u0gUIL8eGargk7CXEYNuMRn2d_lWyXU77gdcn6OJhOTdxoCMPUQAvD_BwE)  | Powersupply for ESP32  | 125  |
| [DHT11*](https://www.electrokit.com/produkt/digital-temperatur-och-fuktsensor-dht11/)  | Temperature and humidity sensor  |  |
| [Window Magnet Contact](https://www.electrokit.com/produkt/magnetisk-dorrkontakt-no/)  | Sensor to detect opening of door or window  | 55 SEK  |
| [Breadboard*](https://www.electrokit.com/produkt/kopplingsdack-840-anslutningar/)  | Breadboard with 840 connectors  | 69 SEK  |
| [Male to male jumper cables*](https://www.electrokit.com/produkt/labbsladd-40-pin-30cm-hane-hane/)  | Jumper wires to wire the breadboard  |  |
| [Resistor*](https://www.electrokit.com/produkt/kopplingsdack-840-anslutningar/)  | Resistor to regulate voltage  |  |
|   |   | **1207 SEK**  |

> **NOTE:** Objects marked with * are included in the starterkit and therefor have no unit price on it

The reason why I used an ESP32 with a TFT display in order to visualize the data is because I had one at home since before. A cheaper choice for this would be another Raspberry Pi Pico W and attach colored LEDs and have them blinking when the alarm is triggered. The code does need to change for this which is not included in the repository.

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

To develop the website and also the server-side mqtt client, I used [visual studio code](https://code.visualstudio.com/). I used this IDE because it is plug-and-play, easy to use and it is easy to structure and keep track of the files and folders. It is also convenient that the IDE comes with many extensions that offer great quality-of-life services. The following steps describe how to download the IDE and also the plugins that I used.

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

In order to store the data, a [Postgresql](https://www.postgresql.org/) database is used. I chose to create my own database instead of using a ready-made one such as [InfluxDB](https://www.influxdata.com/). I decided upon this based on my previous knowledge of [SQL](https://en.wikipedia.org/wiki/SQL) and because a server at [Certit Hosting](https://www.certit.se/) will be used to host the website and also store the sensor data. The reason why I chose Postgresql as the database handler instead of others such as [Mimer](https://www.mimer.com/) or [MySQL](https://www.mysql.com/) is solely due to personal preference. This section covers the installation of the database handler and the setup of the database and user.

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
pip install django djangorestframework django-cors-headers tzdata psycopg2
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

For this project, I am using a self-hosted MQTT broker. I chose to use the [Mosquitto](https://mosquitto.org/) broker for this project. Because I will be running the backend part of the program on a server, I chose to use a self-hosted broker because it allows me to create a client on the server and store the data collected by the sensors directly in the database. I chose Mosquitto because it is a lightweight protocol that has libraries both for the Arduino IDE and for Python. This section will cover how to set up the MQTT broker.

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

# Hardware setup

breadboard with nice figure

# Platform

The choice of platform for this project was clear from the beggining and the reason for this is due to having access to a dedicated server. I created a self-hosted broker and on the same machine created a client that collects the data that is sent through MQTT and store it in a local database. This client is also able to publish the stored data to the MQTT broker which forwards it to subscribing clients.

This platform is very easy to expand and is something I wanted to do during this project but ran out of time. As of this moment, the project is running on my computer which is not what I originally planned since I am not able to place the Raspberry Pi Pico and access the platform at the same time. I am going to put this code on the dedicated server and implement MQTTS so that the messages are transfer with [TLS](https://sv.wikipedia.org/wiki/Transport_Layer_Security). 

# The code

This section will cover how the 

## Data acquisition

sensordata

## Data transportation

mqtt setup

## Visualisation

website
