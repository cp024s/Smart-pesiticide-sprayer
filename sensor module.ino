#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "YOUR AUTHOURIZATION TOKEN";
char ssid[] = "YOUR SSID";
char pass[] = "YOUR PASSWORD";

int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;

#define TRIGGERPIN 16
#define ECHOPIN    5
#define DHTPIN 4
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

WidgetLCD lcd(V4);
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V2, h); // humidity
  Blynk.virtualWrite(V1, t); // temperature
}
  
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  
  lcd.clear();
}

void loop()
{
  Blynk.run();
  timer.run();
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,0,1023,100,0); //100,0 pottupaaru
  delay(100);
  Blynk.virtualWrite(V3,outputvalue);  // Soil moisture

  lcd.clear();
  long duration, distance;
  
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("Cm");
  lcd.print(0,0, distance);
  Blynk.run();

  delay(100);
}
