
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "SFE_BMP180.h"


// Pin Definitions
#define AM2302_PIN_SIG	2
#define SIM800L_SOFTWARESERIAL_PIN_TX	10
#define SIM800L_SOFTWARESERIAL_PIN_RX	11



// Global variables and defines

// object initialization
DHT am2302(AM2302_PIN_SIG);
SFE_BMP180 bmp180;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    am2302.begin();
    //Initialize I2C device
    bmp180.begin();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // AM2302 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float am2302Humidity = am2302.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float am2302TempC = am2302.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(am2302Humidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(am2302TempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2') {
    // BMP180 - Barometric Pressure, Temperature, Altitude Sensor - Test Code
    // Read Altitude from barometric sensor, note that the sensor is 1m accurate
    double bmp180Alt = bmp180.altitude();
    double bmp180Pressure = bmp180.getPressure();
    double bmp180TempC = bmp180.getTemperatureC();     //See also bmp180.getTemperatureF() for Fahrenheit
    Serial.print(F("Altitude: ")); Serial.print(bmp180Alt,1); Serial.print(F(" [m]"));
    Serial.print(F("\tpressure: ")); Serial.print(bmp180Pressure,1); Serial.print(F(" [hPa]"));
    Serial.print(F("\tTemperature: ")); Serial.print(bmp180TempC,1); Serial.println(F(" [°C]"));

    }
    else if(menuOption == '3')
    {
    // Disclaimer: The QuadBand GPRS-GSM SIM800L is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
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
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing AM2302 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing BMP180 - Barometric Pressure, Temperature, Altitude Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing QuadBand GPRS-GSM SIM800L - note that this component doesn't have a test code"));
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

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/