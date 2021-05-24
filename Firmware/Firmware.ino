// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "SFE_BMP180.h"
#include <Sim800L.h>
#include <ArduinoJson.h>

// Pin Definitions
#define AM2302_PIN_SIG 2
#define SIM800L_SOFTWARESERIAL_PIN_TX 10
#define SIM800L_SOFTWARESERIAL_PIN_RX 11

// Global variables and defines

// object initialization
DHT am2302(AM2302_PIN_SIG);
SFE_BMP180 bmp180;
StaticJsonBuffer<200> jsonBuffer;
SoftwareSerial myserial(11, 10); // RX, TX
#define BUFFER_RESERVE_MEMORY 2048

RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);

char t[32];
char deviceID[12] = "MYTEST56";

// define vars for testing menu
const int timeout = 10000; //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    myserial.begin(9600);
    DynamicJsonBuffer jsonBuffer;
    am2302.begin();
    //Initialize I2C device
    bmp180.begin();
    menuOption = menu();

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2020, 02, 29, 17, 50, 40));
    delay(5000);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
    // AM2302 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float am2302Humidity = am2302.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float am2302TempC = am2302.readTempC();
    Serial.print(F("Humidity: "));
    Serial.print(am2302Humidity);
    Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: "));
    Serial.print(am2302TempC);
    Serial.println(F(" [C]"));
    DateTime now = rtc.now();
    // BMP180 - Barometric Pressure, Temperature, Altitude Sensor - Test Code
    // Read Altitude from barometric sensor, note that the sensor is 1m accurate
    double bmp180Alt = bmp180.altitude();
    double bmp180Pressure = bmp180.getPressure();
    double bmp180TempC = bmp180.getTemperatureC(); //See also bmp180.getTemperatureF() for Fahrenheit
    Serial.print(F("Altitude: "));
    Serial.print(bmp180Alt, 1);
    Serial.print(F(" [m]"));
    Serial.print(F("\tpressure: "));
    Serial.print(bmp180Pressure, 1);
    Serial.print(F(" [hPa]"));
    Serial.print(F("\tTemperature: "));
    Serial.print(bmp180TempC, 1);
    Serial.println(F(" [°C]"));
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &object = jsonBuffer.createObject();

    object.set("deviceID", deviceID);
    object.set("humidity", am2302Humidity);
    object.set("temperature", am2302TempC);
    object.set("timedate", t);

    object.printTo(Serial);
    Serial.println(" ");
    String sendtoserver;
    object.prettyPrintTo(sendtoserver);
    delay(4000);

    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }

    myserial.println("AT+HTTPPARA=\"URL\",\"http://192.xxxxxxxxxxxxxxxxxxxxxxxx.php\""); //Server address
    delay(4000);
    ShowSerialData();

    myserial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
    delay(4000);
    ShowSerialData();

    myserial.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100000");
    Serial.println(sendtoserver);
    delay(6000);
    ShowSerialData();

    myserial.println(sendtoserver);
    delay(6000);
    ShowSerialData;

    myserial.println("AT+HTTPACTION=1");
    delay(6000);
    ShowSerialData();

    myserial.println("AT+HTTPREAD");
    delay(6000);
    ShowSerialData();

    myserial.println("AT+HTTPTERM");
    delay(10000);
    ShowSerialData;
}

// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) AM2302 Humidity and Temperature Sensor"));
    Serial.println(F("(2) BMP180 - Barometric Pressure, Temperature, Altitude Sensor"));
    Serial.println(F("(3) QuadBand GPRS-GSM SIM800L"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available())
        ;

    // Read data from serial monitor if received
    while (Serial.available())
    {
        char c = Serial.read();
        if (isAlphaNumeric(c))
        {

            if (c == '1')
                Serial.println(F("Now Testing AM2302 Humidity and Temperature Sensor"));
            else if (c == '2')
                Serial.println(F("Now Testing BMP180 - Barometric Pressure, Temperature, Altitude Sensor"));
            else if (c == '3')
                gsm.println(F("Now Testing QuadBand GPRS-GSM SIM800L - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

void ShowSerialData()
{
    while (myserial.available() != 0)
        Serial.write(myserial.read());
    delay(1000);
}
