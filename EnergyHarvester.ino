
#define INA1 6
#define INA2 5
#define ENA 4
//----------------
#define INB1 11
#define INB2 3
#define ENB 2
//----------------
#define ON_OPT 8
#define ON_GYRO 9
#define VBAT A0
#define INT_G A3
//----------------
#define SL A7
#define SR A6

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

  pinMode(INT_G,INPUT);
}

void loop() {
  Serial.print(analogRead(SL));
  Serial.print("  ");
  Serial.println(analogRead(SR));
  digitalWrite(ON_OPT,HIGH);
  digitalWrite(ENA,HIGH);
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  delay(1000);
  digitalWrite(ENA,HIGH);
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(ENB,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  delay(1000);
}
