import paho.mqtt.client as mqtt
from helper import HelperClass
import json

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("Cabin/Dht11",qos=1)
    client.subscribe("Cabin/Magnet/DoorOpen",qos=1)
    client.subscribe("Home/ESP32/NoAlarm",qos=1)

def on_message(client, userdata, msg):
    if "Dht11" in msg.topic:
        helper.onDHT(msg)
        pub_door_dates()
        #pub_dht_stats()

    if "Magnet" in msg.topic:
        helper.onMag()
       #pub_mag_stats()

    if "NoAlarm" in msg.topic:
        helper.addNoAlarmToday()
        pub_door_dates()

def pub_dht_stats():
    data = helper.getDhtStats()
    client.publish("Home/ESP32/DhtStats", payload=json.dumps(data), qos=1)

def pub_mag_stats():
    data = helper.getMagStats()
    client.publish("Home/ESP32/MagStats", payload=json.dumps(data), qos=1)

def pub_door_dates():
    data = helper.getDoorDates()
    client.publish("Cabin/Magnet/Date", payload=json.dumps(data), qos=1)


client = mqtt.Client(client_id="ServerClient")
client.connect("localhost", 1883, 60)

client.on_connect = on_connect
client.on_message = on_message

helper = HelperClass()

client.loop_forever()