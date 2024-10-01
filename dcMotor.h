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
    double nRatio = 0; // Negative Calibration Ratio - 0 If not needed
    int pwm = 255; // pwmPin signal amount
    int targetOffset = 15; // Target offset
    
    dcMotor (int A, int B, int P, int enc1, int enc2): enc(enc1, enc2) {
      in1 = A;
      in2 = B;
      pwmPin = P;
      pinMode (A, OUTPUT);
      pinMode (B, OUTPUT);
      pinMode (P, OUTPUT);
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

    void freeSpin(int _direction, int _pwm){
      if(_direction == 1){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
      }else if(_direction == 0){
        analogWrite(pwmPin, _pwm);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
      }else if(_direction == -1){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
      }

      analogWrite(pwmPin, _pwm);
    }

    void stop(){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(pwmPin, 0);

      target = read();
    }

    void pause(){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(pwmPin, 0);
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
      return(target / cRatio);
    }

    bool reachedTarget(){
      return(abs(pos - target) < targetOffset);
    }
};
