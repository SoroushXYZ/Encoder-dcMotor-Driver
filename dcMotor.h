class dcMotor {
  private:
    int in1;  // A
    int in2;  // B
    int pwmPin;  //pwmPin
    double pos = 0;
    double target = 0;
    Encoder enc;
  
  public:
    double cRatio = 1; // Calibration Ratio
    int pwm = 255; // pwmPin signal amount
    int targetOffset = 15; // Target offset
    
    dcMotor(int in1, int in2, int pwm, int enc1, int enc2) : enc(enc1, enc2) {
      this->in1 = in1;
      this->in2 = in2;
      this->pwmPin = pwm;
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(pwm, OUTPUT);
    };
    
    void moveTo(double Target){
      target = Target * cRatio;
    }

    // Go towards the target(Must be put in a loop so there will be a stop mecahnism)    
    void go(){
    
      pos = enc.read();
  
      if(pos < target - targetOffset){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      }else if(pos > target + targetOffset){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
      }else{
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        return;
      }

      analogWrite(pwmPin, pwm);
    
    }

    // Run one step closer to the target and stop
    void run(){
      pos = enc.read();
      
      if(pos < int(target) - targetOffset){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      }else if(pos > int(target) + targetOffset){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
      }else{
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        return;
      }

      analogWrite(pwmPin, pwm);
      analogWrite (pwmPin, 0);
    }

    void stop(){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);

      target = read();
    }

    void setCurrentPosition(int newPos){
      pos = newPos * cRatio;
      enc.write(ceil(pos));
    }

    int currentPosition() {
      pos = enc.read();
      return(pos / cRatio);
    }

    int read(){
      return enc.read();
    }

    double getTarget(){
      return(target);
    }

    bool reachedTarget(){
      return(abs(pos - target) < targetOffset);
    }
};
