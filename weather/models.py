from django.db import models
from django.utils import timezone


class Weather(models.Model):
    weather_string = models.CharField(max_length=120)
    created = models.DateTimeField(default=timezone.now)

    # def __str__(self):
    #     return self.title

    def save(self, *args, **kwargs):
        self.created = timezone.now()
        super(Weather, self).save(*args, **kwargs)
