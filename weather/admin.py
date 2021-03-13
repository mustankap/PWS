from django.contrib import admin
from .models import Weather


class WeatherAdmin(admin.ModelAdmin):
    list_display = ("weather_string", "created")


# Register your models here.
admin.site.register(Weather, WeatherAdmin)