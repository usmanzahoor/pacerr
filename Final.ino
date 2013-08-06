/*  PACERR - Partially Arduino Controlred ENEX Rover Robot
    Easy robot build that is reprogamable to suit your needs.

    Copyright (C) 2013 Usman Zahoor

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    code.google.com/p/pacerr for more info
*/

#define trigPin 2 // trigPin of Ultrasonic
#define echoPin 3 // echoPin of Ultrasonic
#define red 11   // Red red for Ultrasonic
#define green 12  // Green red for Ultrasonic

char incomingByte;  // steering mode commands
int leftDrivePin = 4;      // left motor
int rightDrivePin = 6;      // right motor
int leftDirectionPin = 5;   // direction - left motor
int rightDirectionPin = 7;  // direction - right motor
int enable1 = 9;      // left motor
int enable2 = 10;      // right motor

//int sensorPin = 0; // setting the temperature pin for recieving data

void setup() 
{
  Serial.begin(9600);
  // Set all the pins  
  pinMode(leftDrivePin, OUTPUT);
  pinMode(rightDrivePin, OUTPUT);
  pinMode(leftDirectionPin, OUTPUT);
  pinMode(rightDirectionPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(enable1, HIGH);
  digitalWrite(enable2, HIGH);
  // Initial message
  Serial.println("connection successful. enter 'h' for list of commands.");
}

void loop() 
{  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    
    if (incomingByte == 'H'){ // Help command responce
      Serial.println("welcome to the help menue. here is a list of commands; for sensors: u - get distance to next object, t - get temperature; for steering: f - forwards, b - backwards, r - rotate right, l - rotate left, s - stop. visit project page for more info: code.google.com/p/pacerr - by usman zahoor");
    }   
    if (incomingByte == 'f') { // Forwards command
              digitalWrite(leftDirectionPin,HIGH);
              digitalWrite(leftDrivePin, LOW);
              digitalWrite(rightDirectionPin,HIGH);
              digitalWrite(rightDrivePin, LOW);
              Serial.println("Forwards");
    }
    if (incomingByte == 'b') {  //Backwards command
              digitalWrite(leftDirectionPin,LOW);
              digitalWrite(leftDrivePin, HIGH);
              digitalWrite(rightDirectionPin,LOW);
              digitalWrite(rightDrivePin, HIGH);
              Serial.println("Reverse");
    }
    if (incomingByte == 's') { // Brake command
              digitalWrite(leftDirectionPin,LOW);
              digitalWrite(leftDrivePin, LOW);
              digitalWrite(rightDirectionPin,LOW);
              digitalWrite(rightDrivePin, LOW);
              Serial.println("Brake");
    }  
    if (incomingByte == 'l') { //Left command
              digitalWrite(leftDirectionPin,LOW);
              digitalWrite(leftDrivePin, HIGH);
              digitalWrite(rightDirectionPin,HIGH);
              digitalWrite(rightDrivePin, LOW);
              Serial.println("Turning Left");
    } 
    if (incomingByte == 'r') { // Rightcommand
              digitalWrite(leftDirectionPin,HIGH);
              digitalWrite(leftDrivePin, LOW);
              digitalWrite(rightDirectionPin,LOW);
              digitalWrite(rightDrivePin, HIGH);
              Serial.println("Turning Right");
    }    
/*    if (incomingByte == 't') {  // Temperature sensor command
    Serial.println("temperature mode");
              int reading = analogRead(sensorPin);
              float voltage = reading * 5.0;
              voltage /= 1024.0;
              Serial.print(voltage); Serial.println(" volts");
              float temperatureC = (voltage - 0.5) * 100 ; 
              Serial.print(temperatureC); Serial.println(" degrees C");
              float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
              Serial.print(temperatureF); Serial.println(" degrees F");
              float temperatureK = (temperatureC + (273+(15/100)));
              Serial.print(temperatureK); Serial.println(" degrees K");
              float temperatureR = (temperatureC + (273+(15/100)) * (9/5));
              Serial.print(temperatureR); Serial.println(" degrees R");
              delay(1000); 
    } */       
    if (incomingByte == 'u') { // Ultrasonic sensor command
              Serial.println("ultrasonic mode");
              long duration, distance;
              digitalWrite(trigPin, LOW);  // Added this line
              delayMicroseconds(2); // Added this line
              digitalWrite(trigPin, HIGH);
            //  delayMicroseconds(1000); - Removed this line
              delayMicroseconds(10); // Added this line
              digitalWrite(trigPin, LOW);
              duration = pulseIn(echoPin, HIGH);
              distance = (duration/2) / 29.1;
              if (distance < 4) {  // This is where the red On/Off happens
              digitalWrite(red,HIGH); // When the Red condition is met, the Green red should turn off
              digitalWrite(green,LOW);
            }
              else {
                digitalWrite(red,LOW);
                digitalWrite(green,HIGH);
              }
              if (distance >= 200 || distance <= 0){
                Serial.println("Out of range");
              }
              else {
                Serial.print(distance);
                Serial.println(" cm");
              }
              delay(500);
     }    
   }
 }
  


