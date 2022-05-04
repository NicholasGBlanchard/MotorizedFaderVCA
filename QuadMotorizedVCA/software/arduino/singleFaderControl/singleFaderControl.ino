#include <ezButton.h>
#include <CapacitiveSensor.h>
#include <EEPROM.h>


//Motor Outputs
const int faderDown    = 4;
const int faderUp      = 3;

//Fader Inputs
const int wiper        = A0;
//const int pot          = A1;
const int sendtouch    = 5;
const int readtouch = 6;

//Variables
double wiperMax        = 0;
double wiperMin        = 0;
float COEF_CONV        = 0.0;
int faderValue = map(analogRead(wiper), 0, 1023, 0, 255); 

//Button Inputs and Variables
ezButton button(2);
const int BTN_SHORT_PRESS = 2000;
const int BTN_LONG_PRESS  = 2000;
bool _PRESSING = false;
bool _LONG_PRESS_DETECTED = false;
unsigned long timePressed = 0;
unsigned long timeReleased = 0;


//Timer
// unsigned long timer;

//EEPROM
int address = 0;

CapacitiveSensor touchLine = CapacitiveSensor(sendtouch, readtouch);
volatile bool isTouched  = false;

void setup() {
    button.setDebounceTime(50);
    pinMode (faderUp, OUTPUT);
    pinMode  (faderDown, OUTPUT);
    COEF_CONV = 5.0/1023.0;
    calibrateFader();
}

void loop() {
    button.loop();

    if(button.isPressed())
    {
      timePressed = millis();
      _PRESSING = true;
      _LONG_PRESS_DETECTED = false;
    }

    if(button.isReleased())
    {
      _PRESSING = false;
      timeReleased = millis();

      long totalPress = timeReleased - timePressed;

      if(totalPress < BTN_SHORT_PRESS)
      {
        READ_EEPROM();
      }
    }
    if(_PRESSING == true && _LONG_PRESS_DETECTED == false)
    {
      long totalPress = millis() - timePressed;

      if(totalPress > BTN_LONG_PRESS)
      {
        WRITE_EEPROM();
      }
    }

/*    if (state < analogRead(wiper) - 10 && state > wiperMin && !touched) {
        digitalWrite faderDown, HIGH);
        while (state < analogRead(wiper) - 10 && !touched) {};
        digitalWrite faderDown, LOW);
    }
    else if (state > analogRead(wiper) + 10 && state < wiperMax && !touched) {
        digitalWrite(faderUp, HIGH);
        while (state > analogRead(wiper) + 10 && !touched) {};
        digitalWrite(faderUp, LOW);
    }
*/
}

//Calibrates the min and max position of the fader
void calibrateFader() {
    
    digitalWrite(faderUp, HIGH);
    delay(250);
    digitalWrite(faderUp, LOW);
    wiperMax = analogRead(wiper);

    
    digitalWrite (faderDown, HIGH);
    delay(250);
    digitalWrite (faderDown, LOW);
    wiperMin = analogRead(wiper);
}

//Check to see if the fader is being touched
void _TOUCH() {
    isTouched = touchLine.capacitiveSensor(30);                                        
}

void WRITE_EEPROM()
{
  int faderValue = map(analogRead(wiper), 0, 1023, 0, 255);
  EEPROM.put(address, faderValue);
}

void READ_EEPROM()
{
    int faderValue = map(analogRead(wiper), 0, 1023, 0, 255);
    int fader = EEPROM.get(address, faderValue);
    int mapValue = map(fader, 0, 255, 0, 1023);
    _TOUCH();
    if (mapValue < analogRead(wiper) && mapValue > wiperMin && !isTouched) 
    {
      digitalWrite (faderDown, HIGH);
      while (mapValue < analogRead(wiper) && !isTouched) {};
      digitalWrite (faderDown, LOW);
    }
    else if (mapValue > analogRead(wiper) && faderValue < wiperMax && !isTouched) 
    {
      digitalWrite(faderUp, HIGH);
      while (mapValue > analogRead(wiper) && !isTouched) {};
      digitalWrite(faderUp, LOW);
    }


}
