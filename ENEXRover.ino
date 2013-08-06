
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
*/

//  F  forward
//  B  backward
//  L  left
//  R  right
//  S  stop

char input;
int leftDrivePin = 6;      // left motor
int rightDrivePin = 5;      // right motor
int leftDirectionPin = 7;   // direction - left motor
int rightDirectionPin = 4;  // direction - right motor

// digitalWrite(leftDrivePin,HIGH); can be replaced with
// analogWrite(leftDrivePin,N); to control speed

void setup()
{
  Serial.begin(9600);
  pinMode(leftDrivePin, OUTPUT);
  pinMode(rightDrivePin, OUTPUT);
  pinMode(leftDirectionPin, OUTPUT);
  pinMode(rightDirectionPin, OUTPUT);
}

void loop() 
{
  if (Serial.available()) {
    input = Serial.read();
    switch(input)
    {
      case 'F': // forwards
        digitalWrite(leftDirectionPin,HIGH);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,HIGH);
        digitalWrite(rightDrivePin, LOW);
        break;
      case 'B':  // backwards
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, HIGH);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, HIGH);
        break;
      case 'S':  // stop
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, LOW);
        break;
      case 'L':  // left
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, HIGH);
        digitalWrite(rightDirectionPin,HIGH);
        digitalWrite(rightDrivePin, LOW);
        break;
      case 'R':  // right
        digitalWrite(leftDirectionPin,HIGH);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, HIGH);
        break;
      default:    // unrecognized character
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, LOW);
        break;
    }
  }
}