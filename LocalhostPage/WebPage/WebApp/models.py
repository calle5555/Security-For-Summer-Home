from django.db import models

class Dht(models.Model):
    date = models.DateTimeField(blank=True, null=True)
    temp = models.FloatField(blank=True, null=True)
    hum = models.FloatField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'dht'

    def __str__(self):
        return f"{self.date}, {self.temp}, {self.hum}"

class DoorTrigger(models.Model):
    date = models.DateTimeField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'doortrigger'

class DoorUnlocked(models.Model):
    startdate = models.DateTimeField(blank=True, null=True)
    enddate = models.DateTimeField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'doorunlocked'
