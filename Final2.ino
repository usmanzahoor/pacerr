/* PACERR - Partially Arduino Controlled ENEX Rover Robot
Easy robot build that is reprogamable to suit your needs.

Copyright (C) 2013 Usman Zahoor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

code.google.com/p/pacerr for more info
*/

//include libraries
#include <Servo.h>

//set up ultrasonic sensor
const int trigPin = 2; // trigPin
const int echoPin = 3; // echoPin

const int horn = 12; // horn

//set up lightsteer
const int lsPin = A1;
const int ambient = 400; //natural light level
const int threshold = 460; //steering light level
int lightLeft = 0;
int lightRight = 0;

//set up manual steer
char incomingByte; // steering mode commands
const int btPin = A0;
int leftDrivePin = 4; // left motor
int rightDrivePin = 6; // right motor
int leftDirectionPin = 5; // direction - left motor
int rightDirectionPin = 7; // direction - right motor
int enable1 = 9; // left motor
int enable2 = 10; // right motor

const int minSafeDist = 30;
int centerDist, leftDist, rightDist, backDist; // Define variables center, left, right and back distance


Servo myservo; //declare servo

void setup()
{
Serial.begin(9600);
// Set all the pins and the servo
pinMode(btPin, INPUT);
pinMode(leftDrivePin, OUTPUT);
pinMode(rightDrivePin, OUTPUT);
pinMode(leftDirectionPin, OUTPUT);
pinMode(rightDirectionPin, OUTPUT);
pinMode(horn, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
digitalWrite(enable1, HIGH);
digitalWrite(enable2, HIGH);
myservo.attach(11);
myservo.write(95);
// Initial message
Serial.println("connection successful. enter '?' for list of commands.");
}

void loop()
{
//check if we are using the bluetooth module, if so listen for commands only
if( digitalRead(btPin) == HIGH ) {
manual();
return;
}
//check if the photosensors are on, if so follow light only
if( digitalRead(lsPin) == HIGH && digitalRead(btPin) == LOW ) {
lightsteer();
return;
}

centerDist = getDistance();

if(centerDist >= minSafeDist) /* If the inches in front of an object is greater than or equal to the minimum safe distance react*/
{
forward(); // All wheels forward for seconds
}
else // If not:
{
brake(); // Stop all motors
beep();
backward();
lookAround(); // Check your surroundings for best route
if(rightDist > leftDist) // If the right distance is greater than the left distance , turn right
{
right();
}
else if (leftDist > rightDist) // If the left distance is greater than the right distance , turn left
{
left();
}
else if ( leftDist&&rightDist < minSafeDist ) // If the left and right distance is smaller than the min safe distance go back
{
backward();
delay(1000);
}
}
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*manual methods*/
void manual()
{
if (Serial.available() > 0) {
incomingByte = Serial.read();

if (incomingByte == '?'){ // Help command responce
Serial.println("welcome to the help menue. here is a list of commands for steering: f - forwards, b - backwards, r - rotate right, l - rotate left, s - stop, h - buzzer.. visit project page for more info: code.google.com/p/pacerr - by usman zahoor");
}
if (incomingByte == 'f'|| incomingByte == 'F' ) { // Forwards command
digitalWrite(leftDirectionPin,HIGH);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,HIGH);
digitalWrite(rightDrivePin, LOW);
Serial.println("Forwards");
}
if (incomingByte == 'b'|| incomingByte == 'B' ) { //Backwards command
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, HIGH);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, HIGH);
Serial.println("Reverse");
}
if (incomingByte == 's'|| incomingByte == 'S' ) { // Brake command
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, LOW);
Serial.println("Brake");
}
if (incomingByte == 'l'|| incomingByte == 'l' ) { //Left command
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, HIGH);
digitalWrite(rightDirectionPin,HIGH);
digitalWrite(rightDrivePin, LOW);
delay(1000);
Serial.println("Turning Left");
}
if (incomingByte == 'r'|| incomingByte == 'R' ) { // Rightcommand
digitalWrite(leftDirectionPin,HIGH);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, HIGH);
delay(1000);
Serial.println("Turning Right");
}
if (incomingByte == 'h'|| incomingByte == 'H' ) { // horn command
beep();
}
}
}

/*light steering methods*/
void lightsteer()
{
// Read light sensors connected to
// analog pins A0 and A1
lightLeft = analogRead(A2);
lightRight = analogRead(A3);
// Stop robot if below ambient
if (lightRight < ambient || lightLeft < ambient) {
brake();
} else {
forward();
// Steer to right if right CdS below threshold
if (lightRight < threshold) {
left();
delay (250);
}
// Steer to left if left CdS below threshold
forward();
if (lightLeft < threshold) {
right();
delay (250);
}
}
}
/* End of light steering methods */

/* Motor methods */
void brake()
{
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, LOW);
Serial.println("Brake");
}

void forward()
{
digitalWrite(leftDirectionPin,HIGH);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,HIGH);
digitalWrite(rightDrivePin, LOW);
Serial.println("Forwards");
//delay();

}

void backward()
{
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, HIGH);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, HIGH);
Serial.println("Reverse");
delay(200);

}

void left()
{
digitalWrite(leftDirectionPin,LOW);
digitalWrite(leftDrivePin, HIGH);
digitalWrite(rightDirectionPin,HIGH);
digitalWrite(rightDrivePin, LOW);
delay(800);
Serial.println("Turning Left");
}

void right()
{
digitalWrite(leftDirectionPin,HIGH);
digitalWrite(leftDrivePin, LOW);
digitalWrite(rightDirectionPin,LOW);
digitalWrite(rightDrivePin, HIGH);
delay(800);
Serial.println("Turning Right");
}
/* End of Motor methods */

/* Servo methods */
void lookRight()
{
myservo.write(180);
delay(320);
}

void lookLeft()
{
myservo.write(0);
delay(320);
}

void lookAhead()
{
myservo.write(95);
delay(320);
}

void lookAround()
{
lookRight();
rightDist = getDistance();

lookLeft();
leftDist = getDistance();

lookAhead();
centerDist = getDistance();
}
/* End of servo methods */

/* Sensor methods */
int getDistance()
{
long duration;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
return duration / 2 / (29+(1/10));
}
/* End of sensor methods */

void beep (){
  digitalWrite(horn,HIGH);
  delay(200);
  digitalWrite(horn,LOW); 
}