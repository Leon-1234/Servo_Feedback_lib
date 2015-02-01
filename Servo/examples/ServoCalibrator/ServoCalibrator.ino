#include <Servo.h>

Servo servo;

int minimum[20], maximum[20];
int minTotal = 0, maxTotal =0;
void setup() {
  Serial.begin(9600);
  servo.attach(5);
  pinMode(A5,INPUT);
  delay(1000);
  Serial.print("Checking...");
  servo.write(0);
  delay(3000);
  for(int i =0; i<20; i++) {
    minimum[i] = analogRead(A5);
  }
  servo.write(180);
  delay(3000);
  for(int j=0;j<20;j++) {
    maximum[j] = analogRead(A5);
  }
  for(int k = 0; k<20; k++) {
    minTotal = minTotal + minimum[k];
    maxTotal = maxTotal + maximum[k];
  }
   minTotal = minTotal/20;
   maxTotal = maxTotal/20;
}

void loop() {
   Serial.print("Minimum: ");
   Serial.print(minTotal);
   Serial.print("Maximum: ");
   Serial.print(maxTotal);
   Serial.println("");
}


