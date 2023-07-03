from rest_framework import viewsets
from .serializers import DhtSerializer
from .models import Dht

class DhtView(viewsets.ModelViewSet):
    serializer_class = DhtSerializer
    queryset = Dht.objects.all()