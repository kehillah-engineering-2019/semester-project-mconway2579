
#include <dht.h>
#include <Servo.h>
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
Servo servo1;
int temp;
boolean isopen;

void setup(){
  servo1.attach(9);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT22 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor

 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read22(dht_apin);
    temp = (DHT.temperature * (9/5)) + (32);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(temp); 
    Serial.println("F  ");
    if(temp >= 102){
      open();
      isopen = true; 
    }
    if(isopen && temp <=99){
      close();
      isopen = false;
    }
    delay(2000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 

void open(){
  for (int pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos); // tell servo to go to position in variable 'pos'
  }

}
void close(){
  for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
  }
}

