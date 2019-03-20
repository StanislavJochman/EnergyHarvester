#include "LowPower.h"

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

long time_elapsed = millis();

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
  //----------------  
  digitalWrite(ON_OPT,HIGH);
  ChangeLed(0);
}

void loop() {
  if(millis() - time_elapsed > 1000){
    time_elapsed = millis();
    if(ReadBatteryVoltage()<60){
      ChangeLed(1);
      delay(50);
      ChangeLed(0);
    }
  }
  else{
    ChangeLed(0);
    Glow(1);
    Serial.print(analogRead(SL));
    Serial.print("  ");
    Serial.print(analogRead(SL));
    Serial.print("  ");
    Serial.println(ReadBatteryVoltage());
  
    
    if(analogRead(SL)>50 && analogRead(SR)>50){
      RunMotor("AB",180);
    }
    else{
      RunMotor("AB",0);
      
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
