# Servo_Feedback_lib
Modified Arduino Servo library with methods for Servo Position feedback.

Changelog:

29-01-2015:
    Added getPos() function to the existing Servo library. getPos() reads the analog potentiometer output and returns the output as degrees. This will work in case of a Robotics servo with position feedback. This will work with a ordinary hobby servo if the internal potentiometer's wiper pin is brought out and connected to an analog pin. The readings have a bit of noise. Working on filtering the noise and creating a stable output. 
