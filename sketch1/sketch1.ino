#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

#include <dht.h>

unsigned long time;

#define dht_apin A0
 
dht DHT;
int temp;


int fanpin = 8;
int transistorPin = 7;

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

//  pinMode(heatpin, OUTPUT);
 // digitalWrite(heatpin, heatsetting);

  
  delay(1000);//Wait before accessing Sensor



 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read22(dht_apin);
    temp = (DHT.temperature * (9/5) + (32));
    
    if(temp >= 102){
      cool();
      printTemp();
     }
     
    if(temp <=99){
      heat();  
      printTemp();
     }
    pulse();
    

    
    delay(2000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 




void cool(){
  digitalWrite(fanpin, HIGH);
  digitalWrite(transistorPin, LOW);
  }

void heat(){
  digitalWrite(fanpin, LOW);
  digitalWrite(transistorPin, HIGH); 
}

void printTemp(){
 Serial.print("Time: ");
 time = millis();

 Serial.println(time);

  
 Serial.print("%  ");
 Serial.print("temperature = ");
 Serial.print(temp); 
 Serial.println("F  ");

}


void pulse(){
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

 if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
 }
}





