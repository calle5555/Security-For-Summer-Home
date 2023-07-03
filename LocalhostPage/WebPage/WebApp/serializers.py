from rest_framework import serializers
from .models import Dht
from .models import DoorTrigger

class DhtSerializer(serializers.ModelSerializer):
    class Meta:
        model = Dht
        fields = ('id', 'date', 'temp', 'hum')

class DoorTrigSerializer(serializers.ModelSerializer):
    class Meta:
        model = DoorTrigger
        fields = ('id', 'date')