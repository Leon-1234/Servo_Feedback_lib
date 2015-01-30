#include <Servo.h>

Servo servo;

int minimum, maximum;

void setup() {
  Serial.begin(9600);
  servo.attach(5);
  pinMode(A5,INPUT);
  delay(1000);
  servo.write(0);
  delay(2000);
  minimum = analogRead(A5);
  servo.write(180);
  delay(2000);
  maximum = analogRead(A5);
}

void loop() {
   Serial.print("Minimum: ");
   Serial.print(minimum);
   Serial.print("Maximum: ");
   Serial.print(maximum);
   Serial.println("");
}


