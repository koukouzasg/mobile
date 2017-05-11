#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

const char s[2] = ",";          // Character to split in the strtok function
char *token;                    // Strtok tockens

int LeftJoy = 0;                // Left joystick value
int RightJoy = 0;               // Right Joystick value

void setup() {
  Serial.begin(9600);
  
  // Wait for the serial port to connect. Needed for native USB
  while (!Serial) { ; }
  delay(2000);
  Serial.println("Arduino is ready to receive...");
}

void loop() {
  int charsRead;
  while (Serial.available() > 0) {
    charsRead = Serial.readBytesUntil('&', receivedChars, sizeof(receivedChars) - 1); // Read until '>' or 31 chars
    receivedChars[charsRead] = '\0';    // Overwrite '>' to make it a string
   
    token = strtok(receivedChars, s);
    if (token != NULL) {
      RightJoy = atoi(token + 1);
    }
    token = strtok(NULL, s);
    if (token != NULL) {
      LeftJoy = atoi(token);
    }

    Serial.print("Left Stick: ");
    Serial.print(LeftJoy);
    Serial.print("\t\tRight Stick: ");
    Serial.println(RightJoy);
    Serial.println();
    
    // Clear receive buffer so we're ready to receive the next line
    receivedChars[0] = NULL;
  }
}
