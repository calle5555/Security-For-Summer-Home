<!-- This is a readme file -->
# QOL and small security for a summer home
Carl-William Lindkvist cl224di

# Objective

# Materials used

# Computer setup

This section will cover the steps needed to properly install and configure the software. I will provide steps specifically for the Linux distribution Ubuntu.

## Install and setup Arduino IDE

In this section, the Arduino IDE will be installed and the necessary configurations will be done so that both the Pico and ESP32 boards can be used. I chose to write the code for the microcontrollers in the Arduino IDE because I find it comfortable to use. The Arduino IDE offers a stable environment for developing code and it is easy to upload and test the code on a microcontroller. I have previous experience with C and C++ which is another reason for my decision. 

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

## Cloning the repository

It is now time to clone the repository and make the changes needed to run the program. These changes include, among other things, adding the secrets files, and changing the IP for the MQTT broker. I have used [Git](https://git-scm.com/) to handle [version control](https://www.atlassian.com/git/tutorials/what-is-version-control), and to much surprise, the code has been uploaded to [Github](https://en.wikipedia.org/wiki/GitHub). Much like Python, I will not show how to install Git seeing as it is included in most Linux distributions.

1. 

# Hardware setup

breadboard with nice figure

# The code

general intro

## Data acquisition

sensordata

## Data transportation

mqtt setup

## Visualisation

website
