#include <Encoder.h>
#include "dcMotor.h"

//This is an example to show you how you can use the class.

//Initializing the motor
dcMotor newMotor(28, 29, 3, 42, 43); //(in1, in2, pwm, enc1, enc2)

void setup(){
  //Calibration Ratio is used to be paierd with gear ratio or ... to have precise control on the motor
  //For each rotation of the first shaft there are 28 encoder readings.
  //The motor below has a gear ratio of 150.5828
  //It is calibrated to move in degrees.
  newMotor.cRatio = (150.5828) * (28) * (1.0 * 360); //Gear ratio 150.5828:1

  //The driver lets you determine a range of positions acceptibale for the motor to stop in.
  //This will make sure the motor will not wiggle at the end of its movement to reach the exact position
  //The number for targetOffset is in encoder readings and has nothing to do the cRatio.  
  newMotor.targetOffset = 5;

  //Set the pwm signal amount
  newMotor.pwm = 240; //Default is 255(Full Speed)
  
  newMotor.moveTo(180); //Set the target to 180 degrees
}

void loop(){
  
  //Wait till the motor reaches its target
  if(newMotor.reachedTarget()){
    newMotor.moveTo(-1 * newMotor.getTarget());  
  }


  //The go function will trigger the movement. It must be put in loop so we can make sure
  //the motor will stop if it has reached its target.
  //To move the motor only one step you can use newMotor.run()
  newMotor.go();  

}
