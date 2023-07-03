import psycopg2
from datetime import datetime as dt, date, timedelta
from secrets import dbUser, dbPass

class dbHandler:
    def __init__(self):
        self.conn = psycopg2.connect(f"dbname=sensordata user={dbUser} port=5432 host=localhost password={dbPass}")
        self.cur = self.conn.cursor()

    def __del__(self):
        self.cur.close()
        self.conn.close()

    def logMagnetTrigger(self):
        self.cur.execute("INSERT INTO DoorTrigger (date) VALUES (%s);", (dt.now(),))
        self.conn.commit()

    def readMagnetData(self):
        self.cur.execute("SELECT * FROM DoorTrigger;") 
        dbData = self.cur.fetchall()
        data = {i: 0 for i in range(1, len(dbData)+1)}
        for tup in dbData:
            data[tup[0]] = str(tup[1])[:19]
        return data

    def logDHTValues(self, values):
        self.cur.execute("INSERT INTO DHT (date, temp, hum) VALUES (%s, %s, %s);", \
                        (dt.now(), values['temp'], values['hum']))
        self.conn.commit()

    def readDHTData(self):
        self.cur.execute("SELECT * FROM Dht;") 
        dbData = self.cur.fetchall()
        data = {i: {'date': 0, 'temp' : 0, 'hum': 0} for i in range(1, len(dbData)+1)}
        for tup in dbData:
            data[tup[0]] = {'date' : str(tup[1])[:19],
                            'temp' : tup[2],
                            'hum'  : tup[3]}
        return data

    def readDoorDates(self):
        self.cur.execute("SELECT * FROM DoorUnlocked;")
        dbData = self.cur.fetchall()
        data = {}
        for tup in dbData:
            startYear, startMonth, startDay = str(tup[1]).split(' ')[0].split('-')
            endYear, endMonth, endDay = str(tup[2]).split(' ')[0].split('-')

            startDate = date(int(startYear), int(startMonth), int(startDay))
            endDate = date(int(endYear), int(endMonth), int(endDay))

            for i in range((endDate-startDate).days + 1):
                tmp = startDate + timedelta(days = i)
                year = str(tmp.year)
                month = str(tmp.month)
                day = str(tmp.day)

                if year not in data.keys():
                    data[year] = {}

                if month not in data[year].keys():
                    data[year][month] = ""

                if day not in data[year][month]:
                    data[year][month] += day + ' '
        return data
    
    def addDoorDateToday(self):
        self.cur.execute("INSERT INTO DoorUnlocked (startdate, enddate) VALUES (%s, %s)", \
                        (dt.now(), dt.now()))
        self.conn.commit()