#include "pointer.h"

uint32_t num32;
uint8_t ptinputt;
 
void setup() {
Serial.begin (9600);
}
 
void loop() {
 while (!Serial.available()); // Wait for characters
 //get input from serial monitor
 String data = Serial.readString();
 Serial.println(data); 
 
 //convert string to char* so it can be processed by funcstrtok
 char* buf = strdup(data.c_str());
 char* tok = strtok(buf, " ");
 
 //convert char* to unsigned long int
 num32 = strtoul(tok, NULL, 16);
 ptinputt = getPointerr(num32);
 
 
}

 
