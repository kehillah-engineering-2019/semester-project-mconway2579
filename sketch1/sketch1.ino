#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

#include <dht.h>


#define dht_apin A0
 
dht DHT;
int temp;


int fanpin = 8;
int heatpin = 9;
int heatsetting = 0;

const int PulseWire = A1;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup(){
  pinMode(fanpin, OUTPUT);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT22 Humidity & temperature Sensor\n\n");

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  
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

    if(temp >= 102){
      cool();
    }
    if(temp <=99){
      heat();
    }
    pulse();
    

    
    delay(2000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 




void cool(){
  digitalWrite(fanpin, HIGH);
  heatsetting += -10;
  analogWrite(heatpin, heatsetting);
  }

void heat(){
  digitalWrite(fanpin, LOW);
  heatsetting += 10;
  analogWrite(heatpin, heatsetting);
  
}

void pulse(){
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

 if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
 }
}





