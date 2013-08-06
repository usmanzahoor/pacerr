char incomingByte;
int leftDrivePin = 6;      // left motor
int rightDrivePin = 5;      // right motor
int leftDirectionPin = 7;   // direction - left motor
int rightDirectionPin = 4;  // direction - right motor

void setup() 
{
  Serial.begin(9600);
  pinMode(leftDrivePin, OUTPUT);
  pinMode(rightDrivePin, OUTPUT);
  pinMode(leftDirectionPin, OUTPUT);
  pinMode(rightDirectionPin, OUTPUT);
  Serial.println("connection successful. enter command, R, B, S, L, or F");
}

void loop() 
{
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'F') {
        digitalWrite(leftDirectionPin,HIGH);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,HIGH);
        digitalWrite(rightDrivePin, LOW);
        Serial.println("Forwards");
    }
    if (incomingByte == 'B') {
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, HIGH);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, HIGH);
        Serial.println("Reverse");
    }
    if (incomingByte == 'S') {
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, LOW);
        Serial.println("Brake");
    }  
    if (incomingByte == 'L') {
        digitalWrite(leftDirectionPin,LOW);
        digitalWrite(leftDrivePin, HIGH);
        digitalWrite(rightDirectionPin,HIGH);
        digitalWrite(rightDrivePin, LOW);
        Serial.println("Turning Left");
    } 
    if (incomingByte == 'R') {
        digitalWrite(leftDirectionPin,HIGH);
        digitalWrite(leftDrivePin, LOW);
        digitalWrite(rightDirectionPin,LOW);
        digitalWrite(rightDrivePin, HIGH);
        Serial.println("Turning Right");
    }    
  }
}