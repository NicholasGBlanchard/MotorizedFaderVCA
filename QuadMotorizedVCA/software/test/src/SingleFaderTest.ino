#include <CapacitiveSensor.h>        
const int faderDown    = 4;
const int faderUp      = 3;

const int wiper        = A0;
const int pot          = A1;
const int sendtouch    = 5;
const int readtouch = 6;

double wiperMax        = 0;
double wiperMin        = 0;

CapacitiveSensor touchLine = CapacitiveSensor(sendtouch, readtouch);

volatile bool isTouched  = false;

void setup() {
    pinMode (faderUp, OUTPUT);
    pinMode (faderDown, OUTPUT);

    calibrateFader();
}

void loop() {
    int state = analogRead(pot);
    checkTouch();

    if (state < analogRead(wiper) - 10 && state > wiperMin && !isTouched) {
        digitalWrite(faderDown, HIGH);
        while (state < analogRead(wiper) - 10 && !isTouched) {};
        digitalWrite(faderDown, LOW);
    }
    else if (state > analogRead(wiper) + 10 && state < wiperMax && !isTouched) {
        digitalWrite(faderUp, HIGH);
        while (state > analogRead(wiper) + 10 && !isTouched) {};
        digitalWrite(faderUp, LOW);
    }
}


void calibrateFader() {
    
    digitalWrite(faderUp, HIGH);
    delay(250);
    digitalWrite(faderUp, LOW);
    wiperMax = analogRead(wiper);

    
    digitalWrite(faderDown, HIGH);
    delay(250);
    digitalWrite(faderDown, LOW);
    wiperMin = analogRead(wiper);
}


void checkTouch() {
    isTouched = touchLine.capacitiveSensor(30) > 700;  
                                             
}
