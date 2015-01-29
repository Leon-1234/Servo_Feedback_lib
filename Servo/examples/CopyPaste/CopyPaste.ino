#include <Servo.h>

Servo servo1;         //Servo to take in feedback.
Servo servo2;         //Servo to duplicate the feedback.

int servo1_pin = 5;
int servo1_feed = A5;   //Analog pin to which the feeback pin is connected.
int servo2_pin = 6;
int feedback;

void setup() {
  
   Serial.begin(9600);
   servo1.attach(servo1_pin, servo1_feed);
   servo2.attach(servo2_pin);
   
}

void loop()  {
  
   feedback = servo1.getPos();
   servo2.write(feedback);
   Serial.print("Input: ");           //Write the feedback to the Serial Monitor and to the second servo.
   Serial.print(feedback);
   Serial.println("");
   
}
   
   


