// 
//   FILE:  RHTEMPer.ino
// PURPOSE: DHT11-style library test sketch for Arduino and Xinda RH/TEMP sensor similar to DHT11
//

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

// fast integer version with rounding
//int Celcius2Fahrenheit(int celcius)
//{
//  return (celsius * 18 + 5)/10 + 32;
//}


//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
  return celsius + 273.15;
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}


#include <dht11xinda.h>    //modified for xinda sensor
#include <dht11xinda.cpp>  //modified for xinda sensor
dht11 DHT11;

#define DHT11PIN 4

void setup()
{
  Serial.begin(115200);

  Serial.println();
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
  case 0: 
    Serial.println("OK"); 
    break;
  case -1: 
    Serial.println("Checksum error"); 
    break;
  case -2: 
    Serial.println("Time out error"); 
    break;
  default: 
    Serial.println("Unknown error"); 
    break;
  }

  Serial.print("Humidity \t (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature \t(\xb0\x43): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Temperature \t(\xb0\x46): ");
  Serial.println(Fahrenheit(DHT11.temperature), 2);

  Serial.print("Temperature \t(\xb0\x4b): ");
  Serial.println(Kelvin(DHT11.temperature), 2);

  Serial.print("Dew Point \t(\xb0\x43): ");
  Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));

  Serial.print("Dew PointFast \t(\xb0\x43): ");
  Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));

  delay(1500);
}
//
// END OF FILE
//
