//This is the code for master (Arduino Mega)

//For Current Senssor
#include <Wire.h>
#include <Robojax_WCS.h>
#define MODEL 10 //see list above
#define SENSOR_PIN A7 //pin for reading sensor
#define SENSOR_VCC_PIN 13 //pin for powring up the sensor
#define ZERO_CURRENT_LED_PIN 19 //zero current LED pin

#define ZERO_CURRENT_WAIT_TIME 5000 //wait for 5 seconds to allow zero current measurement
#define CORRECTION_VLALUE 167 //mA
#define MEASUREMENT_ITERATION 100
#define VOLTAGE_REFERENCE  5000.0 //5000mv is for 5V
#define BIT_RESOLUTION 10
#define DEBUT_ONCE true

Robojax_WCS sensor(
  MODEL, SENSOR_PIN, SENSOR_VCC_PIN,
  ZERO_CURRENT_WAIT_TIME, ZERO_CURRENT_LED_PIN,
  CORRECTION_VLALUE, MEASUREMENT_ITERATION, VOLTAGE_REFERENCE,
  BIT_RESOLUTION, DEBUT_ONCE
);

// For Voltage Sensor (Total 4 Nos of Voltage Sensor)
int voltagePin1 = A3;
float vout1 = 0.0;
float vin1 = 0.0;
int value1 = 0;


//Declare all Reisitor Value

float R7 = 180000.0;
float R8 = 11730.0;

char a[20];
int i,value0, rpm, spd1;

void setup()
{
  Serial.begin(9600);

  //for Voltage Sensor
  pinMode(voltagePin1, INPUT);

  //for curreny sensor
  sensor.start();

  //Declare Columns Name of the Result
  Serial.println("LABEL,Date,Time,Current, Total Voltage,RPM,Speed (km/h)");
}

void loop()
{
  //for Hall Effect current sensor
  sensor.readCurrent();//this must be inside loop
  float c = sensor.getCurrent();
  float c_final = (c + c / 5);
  if (c_final < -0.5)
  {
    c_final = 0.0;
  }
  else
  {
    c_final = c_final;
  }

  // Now for all voltage sensors individually
  //For Sensor A3 Voltage (Total Voltage)
  value1 = analogRead(voltagePin1);
  vout1 = (value1 * 5.0) / 1024.0;
  vin1 = vout1 / (R8 / (R7 + R8));
  vin1 = (vin1 - 3.8);

  //Read data from serial port
  if (Serial.available() > 0)
  {
    i = 0;
    while (0 < Serial.available())
    {
      a[i] = Serial.read();
      i++;
    }
  }
  String s=String(a);
  //Serial.println(s);
  value0=s.toInt();
  rpm=value0/100;
  spd1=value0%100;

  //Print Result in serial monitor
  Serial.println( (String) "DATA,DATE,TIME" + "," + c_final + "," + vin1 + "," + rpm+ "," + spd1);
  //Serial.println(vin1);
  delay(500);
}
