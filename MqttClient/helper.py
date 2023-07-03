from database import dbHandler
import json

class HelperClass:

    def __init__(self):
        self.dbClient = dbHandler()

    def onDHT(self, msg):
        payload = json.loads(msg.payload)
        values = {}
        values["temp"] = float(f'{payload["Temp"]["int"]}.{payload["Temp"]["dec"]}')
        values["hum"] = float(f'{payload["Hum"]["int"]}.{payload["Hum"]["dec"]}')
        self.dbClient.logDHTValues(values)
        
    def onMag(self):
        self.dbClient.logMagnetTrigger()

    def getDhtStats(self):
        return self.dbClient.readDHTData()
    
    def getMagStats(self):
        return self.dbClient.readMagnetData()
    
    def getDoorDates(self):
        return self.dbClient.readDoorDates()
    
    def addNoAlarmToday(self):
        self.dbClient.addDoorDateToday()