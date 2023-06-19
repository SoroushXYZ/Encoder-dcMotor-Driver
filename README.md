# Driver for DC Motors With Encoders

This class can be used to easily control DC motors that have encoders.
It can be used for the motors that are using L298N driver module.
There is a example provided to help with the setup.

## Setup
1) Copy the dcMotor.h file in the directory of your sketch
2) Add the following lines to at the top of your sketch
```C++
#include <Encoder.h>
#include "dcMotor.h"
```
3) Construct a dcMotor object using the command like the following
```C++
dcMotor newMotor(28, 29, 3, 42, 43); //(in1, in2, pwm, enc1, enc2)
````
4) Use the methods below to control your motor

## Methods
            
Method Name  | Description
------------- | -------------
`dcMotor(int in1, int in2, int pwm, int enc1, int enc2)`  | Constructor. Used to create a dcMotor object
`void moveTo(double Target)`  | Sets a new target for the motor that equals (Target * cRatio)
`void go()` | Will start/stop/change-direction of the motor rotation. should be called in a loop
`void run()` | Same as go() will rotate the motor to get to the target; But just one step(pulse)
`void stop()` | Stops the motor rotation and set the current position as the target
`void setCurrentPosition(int newPos)` | Lets you override the position of the motor and the encoders.
`int currentPosition()` | Returns the current position based on the calibration ratio
`int read()` | Returns the encoder readings(like current position but no cRatio involved)
`double getTarget()` | Returns the target
`bool reachedTarget()` | Tells you if you have reached your target

### Attributes
Attribute  | Description
------------- | -------------
`double cRatio` | Lets you calibrate your motor with the gear ratio to make it easier to rotate in any metrics you want.(Default is `1` so position is mapped to the encoder reading)
`int pwm = 255` | Strength of the PWM signal that we send to the driver
`int targetOffset` | Lets you determine a range of positions acceptibale for the motor to stop in. Since dcMotors are fast we might not be able to stop them exactly wherever we want. This will tell the motor to stop within this number of encoder readings of the target. Default is `15`

##### Developed by SoroushXYZ <3
[MIT](https://choosealicense.com/licenses/mit/)