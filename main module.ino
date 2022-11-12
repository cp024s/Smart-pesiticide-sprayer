#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define inputPin1  3
#define inputPin2  15
#define inputPin3  13
#define inputPin4  12

//enable pins
int EN1 = 1;           
int EN2 = 14;

char auth[] = "ATHORIZATION TOKEN ";  //Blynk Authentication Token
char ssid[] = "YOUR NETWORK SSID";           //WIFI Name
char pass[] = "YOUR PASSWORD";           //WIFI Password

int minRange = 312;
int maxRange = 712;

int minspeed = 250;
int maxspeed = 1020;
int nospeed = 0;

Servo servo1;
Servo servo2;
Servo servo3;

void control(int x, int y)
{
  //    FORWARD
    if(x >= maxRange && y >= minRange && y<= maxRange)
  {
    digitalWrite(inputPin1,HIGH);
    digitalWrite(inputPin3,HIGH);
    analogWrite(EN1,maxspeed);
    analogWrite(EN2,maxspeed);  
    
  }
  //LEFT
  else if(y >= maxRange && x>= minRange && x<= maxRange)
    {
    digitalWrite(inputPin2,HIGH);
    digitalWrite(inputPin3,HIGH);
    analogWrite(EN1,maxspeed);
    analogWrite(EN2,maxspeed);
    }
    //RIGHT
    else if(y <= minRange && x >= minRange && x<= maxRange)
    {
    digitalWrite(inputPin1,HIGH);
    digitalWrite(inputPin4,HIGH);
    analogWrite(EN1,maxspeed);
    analogWrite(EN2,maxspeed);
 }
    
    //STOP
    else if(x < maxRange && x > minRange && y < maxRange && y > minRange)
    {
     digitalWrite(inputPin1,LOW);
     digitalWrite(inputPin2,LOW);
     digitalWrite(inputPin3,LOW);
     digitalWrite(inputPin4,LOW);
    }
    
    //BACK
    else if(x <= minRange && y >= minRange && y <= maxRange)
    {
    digitalWrite(inputPin2,HIGH);
    digitalWrite(inputPin4,HIGH);
    analogWrite(EN1,maxspeed);
    analogWrite(EN2,maxspeed); 
    }
}
void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    
    pinMode(EN1, OUTPUT);   // where the motor is connected to
    pinMode(EN2, OUTPUT);   // where the motor is connected to
    
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);

    servo1.attach(16);
    servo2.attach(5);
    servo3.attach(4);


    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, LOW);
}

void loop()
{
    Blynk.run();
}

BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  control(x,y);
}

BLYNK_WRITE(V2)
{
  servo1.write(param.asInt());
  Serial.println(param.asInt());
}

BLYNK_WRITE(V3)
{
  servo2.write(param.asInt());
  Serial.println(param.asInt());
}

BLYNK_WRITE(V4)
{
  servo3.write(param.asInt());
  Serial.println(param.asInt());
}
