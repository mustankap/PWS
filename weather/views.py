from django.shortcuts import render
from rest_framework import viewsets
from .serializers import WeatherSerializer
from .models import Weather


class WeatherView(viewsets.ModelViewSet):
    serializer_class = WeatherSerializer
    queryset = Weather.objects.all()