#include <NewPing.h>
#include <SPI.h>
#include <LoRa.h> 


#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 5 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int MaxDistance = 200;
int pot = A0;

NewPing sonar(trigPin, echoPin, MaxDistance); 

void setup() {

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Tes t"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  Serial.println("LoRa On!");  
 
  pinMode(pot,INPUT);
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }else{
    Serial.println("LoRa On!");  
  }
  

}
void loop() {

  
  delay(50);                      // esperar 50ms entre pings (29ms como minimo)
  Serial.print(sonar.ping_cm()); // obtener el valor en cm (0 = fuera de rango)
  Serial.println("cm");
  

  
  LoRa.beginPacket();  
  LoRa.print(sonar.ping_cm());
  LoRa.endPacket();
  delay(50);
  
  
}
