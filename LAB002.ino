
#include<Wire.h>

char buzzervalue,sendbonus,sendpythonnew='\0', sendpythonold='x';
const int buzzer = 5;
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
const int MPU_addr = 0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);    //access the power management Register
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(SW_pin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(SW_pin,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x3B);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  if(AcZ>25000)
  {
    sendbonus = 'z'; 
    Serial.write(sendbonus);
    delay(400);
  }

    
if(analogRead(X_pin) < 200 ||GyY <= -10000)
  { 
    sendpythonnew = 'a';
  }
  else if(analogRead(X_pin) > 800 ||GyY >= 10000)
  {
    sendpythonnew = 'd';
  }
 else if(analogRead(Y_pin) < 200 ||GyX <= -10000)
  {
    sendpythonnew = 'w';
  }
  else if(analogRead(Y_pin) > 800|| GyX >= 10000)
  {
    sendpythonnew = 's';
  }



if(sendpythonold!=sendpythonnew)
{
 Serial.write(sendpythonnew);
 delay(400); 
sendpythonold=sendpythonnew;
}
if(Serial.available())
  { buzzervalue = Serial.read();
  if(buzzervalue == 'x')
    {digitalWrite(buzzer, HIGH);
    delay(400);
    digitalWrite(buzzer, LOW);
  }}
  }
