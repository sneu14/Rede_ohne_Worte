#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 16
#define NUMPIXELS 3

char data[] = {'M', 'C', 'M', 'C', 'M', 'C', 'M', 'C', 'M', 'A', 'A', 'C', 'M', 'A', 'C', 'A', 'C', 'M', 'A', 'M', 'C', 'C', 'A', 'M', 'A', 'M', 'C', 'M', 'M', 'A', 'C', 'A', 'C', 'M', 'C', 'M', 'A', 'A', 'C', 'M', 'A', 'C', 'M', 'A', 'C', 'C', 'M', 'C', 'C', 'C', 'C', 'A', 'C', 'A', 'C', 'A', 'M', 'C', 'A', 'M', 'A', 'M', 'C', 'C', 'M', 'A', 'M', 'A', 'M', 'A', 'C', 'A', 'M', 'C', 'M', 'M', 'C', 'M', 'C', 'C', 'A', 'C', 'C', 'A', 'M', 'C', 'A', 'A', 'M', 'M', 'M', 'A', 'C', 'A', 'C', 'A', 'M', 'A', 'M', 'C', 'M', 'C', 'A', 'C', 'A', 'M', 'A', 'M', 'A', 'C', 'A', 'M', 'A', 'A', 'C', 'M', 'C', 'M', 'C', 'M', 'A', 'M', 'A', 'M', 'A', 'C', 'C', 'A', 'M', 'A', 'M', 'M', 'C', 'C', 'M', 'C', 'C', 'A', 'M', 'C', 'A', 'M', 'C', 'C', 'C', 'C', 'C', 'A', 'M', 'A', 'C', 'C', 'M', 'A', 'C', 'A', 'M', 'C', 'M', 'M', 'A', 'A', 'C', 'C', 'M', 'M', 'C', 'M', 'C', 'M', 'C', 'M', 'M', 'M', 'C', 'A', 'C', 'A', 'A', 'C', 'M', 'C', 'A', 'C', 'A', 'M', 'C', 'M', 'A', 'M', 'C'};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int next_button = data[0];
int counter = 0;
int button_prev[3] = {1, 1, 1};

void setup()
{
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(115200);
  pixels.begin();

  pixels.clear();
  pixels.setPixelColor(0,255,255,255);
  pixels.show();
}

void setLed(int led)
{
  pixels.clear();
  pixels.setPixelColor(led, 0, 0, 255);
  pixels.show();
  delay(2000);
  pixels.clear();
  pixels.setPixelColor(led, 127, 0, 0);
  pixels.show();
}

void nextLed(int button)
{
  int x = data[counter];
  if (button == next_button)
  {
    pixels.clear();
    if (x == 'A')
      setLed(2);
    else if (x == 'C')
      setLed(1);
    else if (x == 'M')
      setLed(0);
    next_button = data[counter];
    if (counter < sizeof(data))
      Serial.println(counter);
    counter++;
    ;
  }
}

void loop()
{
  if (!digitalRead(1))
  {
    if (button_prev[0] == 1)
    {
      nextLed('M');
      button_prev[0] = 0;
    }
  }
  else
  {
    button_prev[0] = 1;
  }
  if (!digitalRead(2))
  {
    if (button_prev[1] == 1)
    {
      nextLed('C');
      button_prev[1] = 0;
    }
  }
  else
  {
    button_prev[1] = 1;
  }
  if (!digitalRead(3))
  {
    if (button_prev[2] == 1)
    {
      nextLed('A');
      button_prev[2] = 0;
    }
  }
  else
  {
    button_prev[2] = 1;
  }
  delay(20);
}
