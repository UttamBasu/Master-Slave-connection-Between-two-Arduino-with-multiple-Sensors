//This is the Slave Board Program (Arduino Uno)

int rpmsensor = 12;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps = 0;
float steps_old = 0;
float temp = 0;
float rps = 0;
float kmph1 = 0.0;

//define a character for transfer data to serial
char a[20];

void setup()
{
  Serial.begin(9600);
  pinMode(rpmsensor, INPUT_PULLUP);
}
void loop()
{
  start_time = millis();
  end_time = start_time + 1000;
  while (millis() < end_time)
  {
    if (digitalRead(rpmsensor))
    {
      steps = steps + 1;
      while (digitalRead(rpmsensor));
    }

  }
  temp = steps - steps_old;
  steps_old = steps;
  rps = (temp);
  float spd = 3.14 * 0.135 * rps; // speed = 3.14159*(D/100)*(rpm/60) // speed in m/s
  int spd1 = ((3.14 * 0.000135 * rps * 60 * 1000 * 2.5) / 1); //RPM use 1 number of reflector connected
  int kmph1 = (spd1 * 0.1885 * 0.45);

  sprintf(a, "%d%d", spd1, kmph1);
  Serial.write(a);
  Serial.println();

  delay(100);
}
