/* ---------------------------------------------------------------------------
* This code waits for signal from RP1 to begin measurements. When signal is received, 
* LED is lit and arduino takes 20 samples with HC-RS04 ultrasonic sonar.
* When sampling complete, it calculates the average and prints it to Serial, to be received back by
* RP1. LED turns off.
* 
* Includes NewPing.h by...
* ---------------------------------------------------------------------------
*/

#include <NewPing.h>

#define trigger_pin  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define echo_pin     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define LED_pin 3  // start button
#define no_of_samples 20 //Number of samples per measuring session

volatile int samples[no_of_samples]; //array to store distance samples

NewPing sonar(trigger_pin, echo_pin); // Making NewPing sonar object

void setup() {
  Serial.begin(115200); // Open serial port at 230400 baud rate.
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  //Wait for button to be pushed
  while (Serial.available() > 0){ //waiting for data, 0 means no data
    
    if(Serial.readString() == "start"){
      digitalWrite(LED_pin, HIGH); //LED on, while measurements taken
      take_measurements();  //start measurement routine
    }
  }
}

void take_measurements(){
  //Fill array with measurement samples
  for(int i = 0 ; i < no_of_samples; i++){
    delay(50); // wait 50 ms between each sample to avoid cross reading
    samples[i] = sonar.ping_cm(); //ping_cm() returns int sample (distance in cm)
  }
  
  find_average(); 
}

void find_average(){
  float sum{0}; //sum as float makes division more accurate
  
  //sum of samples
  for(int i = 0 ; i < no_of_samples; i++){
    sum += samples[i];
  }

  
  int average{0}; // to store average distance
  average = round(sum/no_of_samples); //Round float division to nearest whole number. 

  
  //Print average to Serial
  //Serial.write("Average: ");
  Serial.print(average);
  //Serial.write(" cm \n");

  digitalWrite(LED_pin, LOW); //LED off, when measurement sent
}
