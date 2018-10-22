
#include <dht.h>
#include <Servo.h>
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
Servo servo1;
int temp;
boolean isopen;

int fanpin = 7;

void setup(){
  servo1.attach(9);
  pinMode(fanpin, OUTPUT);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT22 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor

 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read22(dht_apin);
    temp = (DHT.temperature * (9/5) + (32));
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("F  ");
    if(temp >= 55){
      open();
      isopen = true; 
    }
    if(isopen && temp <=54){
      close();
      isopen = false;
    }
    delay(2000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 

void open(){
  servo1.write(180); 
  digitalWrite(fanpin, HIGH);
  }

void close(){
  servo1.write(90);
  digitalWrite(fanpin, LOW);
}

