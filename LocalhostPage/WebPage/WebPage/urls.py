from django.contrib import admin
from django.urls import include, path
from rest_framework import routers
from WebApp import views

router = routers.DefaultRouter()
router.register(r'dhts', views.DhtView, 'dht')

urlpatterns = [
    path('api/', include(router.urls)),
    path('admin/', admin.site.urls),
]
