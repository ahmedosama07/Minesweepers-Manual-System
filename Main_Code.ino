/**
 * Minesweepers'18 Manual System
*/

/**
 * Sirens
 */
int LeftSiren = 22;
int RightSiren = 24;
int MiddleSiren = 26;

/**
 * Leds
 */
int LeftLed = 23;
int RightLed = 25;
int MiddleLed = 27;
int MajorLed = 28;

/**
 * Metal Detectors
 */
int LeftDetector = 30;
int RightDetector = 31;
int MiddleDetector = 32;

bool isLeft = false;
bool isRight = false;
bool isMiddle = false;
/**
 * Motors
 */
//Left Motors
int Lpwm1 = 2;
int Rpwm1 = 3;
int Lpwm2 = 4;
int Rpwm2 = 5;

//Right Motors
int Lpwm3 = 6;
int Rpwm3 = 7;
int Lpwm4 = 8;
int Rpwm4 = 9;

int rc_channel1 = 10;
int rc_channel3 = 11;
int switchD = 12;

void setup() {
  pinMode(Lpwm1,OUTPUT);
  pinMode(Rpwm1,OUTPUT);
  pinMode(Lpwm2,OUTPUT);
  pinMode(Rpwm2,OUTPUT);
  pinMode(Lpwm3,OUTPUT);
  pinMode(Rpwm3,OUTPUT);
  pinMode(Lpwm4,OUTPUT);
  pinMode(Rpwm4,OUTPUT);

  pinMode(LeftSiren,OUTPUT);
  pinMode(RightSiren,OUTPUT);
  pinMode(MiddleSiren,OUTPUT);

  pinMode(LeftLed,OUTPUT);
  pinMode(RightLed,OUTPUT);
  pinMode(MiddleLed,OUTPUT);
  pinMode(MajorLed,OUTPUT);

  pinMode(LeftDetector, INPUT);
  pinMode(MiddleDetector, INPUT);
  pinMode(RightDetector, INPUT);

  pinMode(rc_channel1, INPUT);
  pinMode(rc_channel3, INPUT);
  pinMode(switchD, INPUT);

  Serial.begin(9600);
}

void loop() {
  int pwm = 0;
  int swd = pulseIn(switchD, HIGH, 25000);
  int rc1 = pulseIn(rc_channel1, HIGH, 25000);
  int rc3 = pulseIn(rc_channel3, HIGH, 25000);
  
  Serial.print("switch: ");
  Serial.print(swd);
  Serial.print(",   channel1: ");
  Serial.print(rc1);
  Serial.print(",   channel3: ");
  Serial.println(rc3);

  Move(pwm, swd, rc1, rc3);
  Detect();
  
  delay(10);
}

//Detection
void Detect(){
  if(LeftDetector == 1 && RightDetector != 1 && MiddleDetector != 1){
    digitalWrite(LeftLed, HIGH);
    digitalWrite(LeftSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is left");
  }
  else if(RightDetector == 1 && LeftDetector != 1 && MiddleDetector != 1){
    digitalWrite(RightLed, HIGH);
    digitalWrite(RightSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Serial.println("Mine is right");
  }
  else if(MiddleDetector == 1 && LeftDetector != 1 && RightDetector != 1){
    digitalWrite(MiddleLed, HIGH);
    digitalWrite(MiddleSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is middle");
  }
  else if(LeftDetector == 1 && RightDetector == 1 && MiddleDetector != 1){
    digitalWrite(LeftLed, HIGH);
    digitalWrite(LeftSiren, HIGH);
    digitalWrite(RightLed, HIGH);
    digitalWrite(RightSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is right and left");
  }
  else if(LeftDetector == 1 && MiddleDetector == 1 && RightDetector != 1){
    digitalWrite(LeftLed, HIGH);
    digitalWrite(LeftSiren, HIGH);
    digitalWrite(MiddleLed, HIGH);
    digitalWrite(MiddleSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is middle and left");
  }
  else if(RightDetector == 1 && MiddleDetector == 1 && LeftDetector != 1){
    digitalWrite(RightLed, HIGH);
    digitalWrite(RightSiren, HIGH);
    digitalWrite(MiddleLed, HIGH);
    digitalWrite(MiddleSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is middle and right");
  }
  else if(LeftDetector == 1 && MiddleDetector ==1 && RightDetector == 1){
    digitalWrite(RightLed, HIGH);
    digitalWrite(RightSiren, HIGH);
    digitalWrite(MiddleLed, HIGH);
    digitalWrite(MiddleSiren, HIGH);
    digitalWrite(LeftLed, HIGH);
    digitalWrite(LeftSiren, HIGH);
    digitalWrite(MajorLed, HIGH);
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
    Serial.println("Mine is all around the rover");
  }
  else{
    digitalWrite(RightLed, LOW);
    digitalWrite(RightSiren, LOW);
    digitalWrite(MiddleLed, LOW);
    digitalWrite(MiddleSiren, LOW);
    digitalWrite(LeftLed, LOW);
    digitalWrite(LeftSiren, LOW);
    digitalWrite(MajorLed, LOW);
    Serial.println("No Mine!");
  }
}


//Motion
void Move(int pwm, int swd, int rc1, int rc3){
  int swtch = map(swd, 1000, 2000, 0, 255);
    if(rc1 == 0 || rc3 == 0){
    Serial.println("No Signal yasta");
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
  }
  else if(rc1 > 1530){
      pwm = map(rc1, 1530, 2000, 0, 255);
      Forward(pwm);
      Serial.print("Moving forward:     Speed = ");
      Serial.println(pwm);
    }
  else if(rc1 < 1460){
      pwm = map(rc1, 1460, 1000, 0, 255);
      Backward(pwm);
      Serial.print("Moving backward:     Speed = ");
      Serial.println(pwm);
  }
  else if(rc3 > 1530){
      pwm = map(rc3, 1530, 2000, 0, 255);
      Right(pwm);
      Serial.print("Moving Left:     Speed = ");
      Serial.println(pwm);
    }
  else if(rc3 < 1460){
      pwm = map(rc3, 1460, 1000, 0, 255);
      Left(pwm);
      Serial.print("Moving Left:     Speed = ");
      Serial.println(pwm);
  }
  else if(swtch == 255){
    //TODO
  }
  else{
    Serial.println("At rest");
    Forward(0);
    Backward(0);
    Right(0);
    Left(0);
  }

}

void Forward(int velocity){
  analogWrite(Lpwm1,0);
  analogWrite(Rpwm1,velocity);
  analogWrite(Lpwm2,0);
  analogWrite(Rpwm2,velocity);
  analogWrite(Lpwm3,0);
  analogWrite(Rpwm3,velocity);
  analogWrite(Lpwm4,0);
  analogWrite(Rpwm4,velocity);
}
void Backward(int velocity){
  analogWrite(Lpwm1,velocity);
  analogWrite(Rpwm1,0);
  analogWrite(Lpwm2,velocity);
  analogWrite(Rpwm2,0);
  analogWrite(Lpwm3,velocity);
  analogWrite(Rpwm3,0);
  analogWrite(Lpwm4,velocity);
  analogWrite(Rpwm4,0);
}
void Right(int velocity){
  analogWrite(Lpwm1,0);
  analogWrite(Rpwm1,velocity);
  analogWrite(Lpwm2,0);
  analogWrite(Rpwm2,velocity);
  analogWrite(Lpwm3,velocity);
  analogWrite(Rpwm3,0);
  analogWrite(Lpwm4,velocity);
  analogWrite(Rpwm4,0);
}
void Left(int velocity){
  analogWrite(Lpwm1,velocity);
  analogWrite(Rpwm1,0);
  analogWrite(Lpwm2,velocity);
  analogWrite(Rpwm2,0);
  analogWrite(Lpwm3,0);
  analogWrite(Rpwm3,velocity);
  analogWrite(Lpwm4,0);
  analogWrite(Rpwm4,velocity);
}
