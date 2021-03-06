/*
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
  Copyright (c) 2009 Michael Margolis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

 /* 
 ARDUINO SERVO LIBRARY MODIFIED ON 2015 BY LEON FOR ADDED SUPPORT OF POSTION FEEDBACK AND SPEED CONTROL.
 No Copyright Infringement Intended.

 This modified library is redistributed in hope that it will be useful but without any Warranties. All above limitations apply. 
 
 */

/* 
 
 A servo is activated by creating an instance of the Servo class passing the desired pin to the attach() method.
 The servos are pulsed in the background using the value most recently written using the write() method
 
 Note that analogWrite of PWM on pins associated with the timer are disabled when the first servo is attached.
 Timers are seized as needed in groups of 12 servos - 24 servos use two timers, 48 servos will use four.
 
 The methods are:
 
 Servo - Class for manipulating servo motors connected to Arduino pins.
 
 
 attach(pin )              				 - Attaches a servo motor to an i/o pin.
 attach(pin, min, max  )   				 - Attaches to a pin setting min and max values in microseconds //default min is 544, max is 2400  
 setFeed(pin)              				 - Sets a servo position feedback pin on any analog pin.
 setFeed(pin, min, max)    				 - Sets a servo position feedback pin on any analog pin and sets the minimum and maximum values on the internal potentiometer.
 write()                  			     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
 write(value,speed)                  	 - Sets the servo angle and speed.
 write(value,speed,waitToComplete)		 - Sets the servo angle and speed with wait to complete function.
 writeMicroseconds()       				 - Sets the servo pulse width in microseconds 
 read()                  			     - Gets the last written servo pulse width as an angle between 0 and 180. 
 readMicroseconds()      			     - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
 attached()              			     - Returns true if there is a servo attached. 
 detach()                                - Stops an attached servos from pulsing its i/o pin.
 getPos()                                - Gets position feedback from a servo's internal potentiometer and returns a output in degrees.
 
*/

#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

/* 
 * Defines for 16 bit timers used with  Servo library 
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the curent board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 *
 */

// Say which 16 bit timers can be used and in what order
#if defined(__AVR_ATmega1280__)  || defined(__AVR_ATmega2560__)
#define _useTimer5
#define _useTimer1 
#define _useTimer3
#define _useTimer4 
typedef enum { _timer5, _timer1, _timer3, _timer4, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_ATmega32U4__)
#define _useTimer3  
#define _useTimer1 
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define _useTimer3
#define _useTimer1
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_ATmega128__) ||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
#define _useTimer3
#define _useTimer1
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#else  // everything else
#define _useTimer1
typedef enum { _timer1, _Nbr_16timers } timer16_Sequence_t ;                  
#endif

#define Servo_VERSION           2      // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds 

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t feedPin;
  int maxFeed :472;
  int minFeed :101;
  int fdvalue;
} feedback_t ;

typedef struct {
  ServoPin_t Pin;
  unsigned int ticks;
  feedback_t Feed;
  unsigned int target;			
  uint8_t speed;	
} servo_t;


class Servo
{
public:

  Servo();
  uint8_t attach(int pin);                         // Attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max);       // As above but also sets min and max values for writes. 
  void detach();                            	   // Detaches the Servo
  int getPos();                             	   // Gets the feedback from servos using analog input.   
  void setFeed(int pin);                    	   // Sets a i/o pin as the analog feedback input pin.
  void setFeed(int pin, int min, int max);		   // Sets a i/o pin as the analog feedback pin and sets the minimum and maximum voltage values in the wiper wire.
  void write(int value);                     	   // If value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void write(int value, uint8_t speed); 		   // Modified Write function with Speed control.
  void write(int value, uint8_t speed, bool wait); // Modified Write function with Speed control and Wait to complete function.
  void writeMicroseconds(int value);			   // Write pulse width in microseconds 
  int read();                      				   // Returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();        			       // Returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                                 // Return true if this servo is attached, otherwise false 
  void stop();                                     // Stops the servo instantly.

private:

   uint8_t servoIndex;                             // index into the channel data for this servo
   int8_t min;                                     // minimum is this value times 4 added to MIN_PULSE_WIDTH    
   int8_t max;                                     // maximum is this value times 4 added to MAX_PULSE_WIDTH 

     
};

#endif
