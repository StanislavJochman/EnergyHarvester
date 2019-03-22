//SMCR &= ~(1<<SM0)//nastavenie na 0
//SMCR |= (1<<SM0)//nastavenie na 1

#define INA1 11
#define INA2 3
#define ENA 2
//----------------
#define INB1 6
#define INB2 5
#define ENB 4
//----------------
#define ON_OPT 8
#define ON_GYRO 9
#define VBAT A0
#define INT_G A3
//----------------
#define SL A7
#define SR A6
//----------------
#define led 7
//----------------
#define button 10

int line_value;
long time_elapsed = millis();
bool low_battery = 0;
int speed = 0;
int speed_backward = 0;
void setup() {
  Serial.begin(9600);
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(ON_OPT,OUTPUT);
  pinMode(ON_GYRO,OUTPUT);
  pinMode(led,OUTPUT);
  //----------------
  pinMode(INT_G,INPUT);
  pinMode(button,INPUT_PULLUP);
  //----------------  
  digitalWrite(ON_OPT,HIGH);
  ChangeLed(0);
  bool high_battery = 0;
  while(true){
    if(ReadButton()==1){
      CalibrateLine(10);
      for(int x=0;x<3;x++){
          ChangeLed(1);
          delay(300);
          ChangeLed(0);
          delay(300);
        }
      break;  
    }
    else if(ReadBatteryVoltage()>81){
      if(high_battery == 0){    
        for(int x=0;x<10;x++){
          ChangeLed(1);
          delay(50);
          ChangeLed(0);
          delay(50);
        }
        high_battery = 1;
      }
    }
    Glow(1);
    Serial.print(analogRead(SR));
    Serial.print(" ");
    Serial.println(analogRead(SL));
  }
  while(true){
        if(ReadButton()==1){
          break;
        }
      }
}

void loop() {
  speed = 230 + (160-ReadBatteryVoltage()*1.5);
  speed_backward = -speed/3;
  if(millis() - time_elapsed > 5000){
    time_elapsed = millis();
    if(ReadBatteryVoltage()<20){
      low_battery = 1;
      RunMotor("AB",0);
      Glow(0);
      ChangeLed(1);
      delay(50);
      ChangeLed(0);
    }
    else{
      low_battery = 0;  
    }
  }
  else{
    if(low_battery == 0){
      Glow(1);
      if(analogRead(SL)>line_value){
        RunMotor("A",speed_backward);
      }
      else if(analogRead(SR)<line_value){
        RunMotor("B",speed_backward);
      }
      else{
        RunMotor("AB",speed);
      }
    }
  }
}
void RunMotor (String motor_select,int speed) {
  if (motor_select == "A") {
    if (speed > 0) {
      digitalWrite(ENA,HIGH);
      digitalWrite(INA2,LOW);
      analogWrite(INA1,speed);
    }
    else if (speed < 0) {
      digitalWrite(ENA,HIGH);
      digitalWrite(INA1,LOW);
      analogWrite(INA2,abs(speed));
    }
    else {
      digitalWrite(ENA,LOW);
      digitalWrite(INA1,LOW);
      digitalWrite(INA2,LOW);  
    }     
  }
  else if (motor_select == "B") {
    if (speed > 0) {
      digitalWrite(ENB,HIGH);
      digitalWrite(INB2,LOW);
      analogWrite(INB1,speed);
    }
    else if (speed < 0) {
      digitalWrite(ENB,HIGH);
      digitalWrite(INB1,LOW);
      analogWrite(INB2,abs(speed));
    }
    else {
      digitalWrite(ENB,LOW);
      digitalWrite(INB1,LOW);
      digitalWrite(INB2,LOW);  
    }
  }
  else {
    if (speed > 0) {
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(INA2,LOW);
      digitalWrite(INB2,LOW);
      analogWrite(INA1,speed);
      analogWrite(INB1,speed);
    }
    else if (speed < 0) {
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB,HIGH);
      digitalWrite(INA2,LOW);
      digitalWrite(INB2,LOW);
      analogWrite(INA1,abs(speed));
      analogWrite(INB1,abs(speed));
    }
    else {
      digitalWrite(ENA,LOW);
      digitalWrite(ENB,LOW);
      digitalWrite(INA1,LOW);
      digitalWrite(INB1,LOW);
      digitalWrite(INA2,LOW);  
      digitalWrite(INB2,LOW);  
    }
  }
}
void ChangeLed(bool state){
  digitalWrite(led,!state);
}
void Glow(bool state){
  digitalWrite(ON_OPT,!state);  
}
int ReadBatteryVoltage(){
  int battery_voltage = map(analogRead(VBAT),0,320,0,100);
  return battery_voltage;
}
bool ReadButton(){
  return !digitalRead(button);  
}
void CalibrateLine(int calibration){
  line_value = (analogRead(SR) + analogRead(SL))/2 + calibration; 
}
void ADCNoiseReduction(){
  SMCR |= (1<<SM0);
  SMCR &= ~(1<<SM1 | 1<<SM2);
}
