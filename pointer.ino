#include "pointer.h"

byte b; 
uint32_t num32 = 0x12345678;
uint8_t ptinputt;
 
void setup() {
    Serial.begin (9600); //inisialiasasi komunikasi serial

}
 
void loop() {
    ptinputt = getPointerr(num32);
 
}
