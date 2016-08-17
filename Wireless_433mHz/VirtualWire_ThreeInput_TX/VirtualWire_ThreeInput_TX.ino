/* 
Collect and then transmit 3 Analog Variables (hard-coded for 3 digit values) 
via low-cost 433mHz radios.  Can also be used with HIGH/LOW inputs.
*/

#include <VirtualWire.h>
char msg0[20];
char msg1[20];
char msg2[20];
int x = 0;
int y = 0;
int z = 0;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  vw_set_tx_pin(9);          // VirtualWire transmit pin
  vw_setup(4800);            // VirtualWire communication speed
//Serial.begin(9600);        // For Debugging
}

void loop() {
  digitalWrite(13, HIGH);    //Indicate the beginning of a transmission
  x = analogRead(A1);        // Variable holding AccelX
  y = analogRead(A2);        // Variable holding AccelY
  z = analogRead(A3);        // Variable holding AccelZ
  itoa(x, msg1, 10);         // Transfer x to msg1 as a decimal number                         
  itoa(y, msg0, 10);         // itoa arg #3: 10=decimal 2= binary, 16=hex
  itoa(z, msg2, 10);  
  strcat(msg0, msg1);                     // Add y to x
  strcat(msg0, msg2);                     // Add z to x&y
  vw_send((uint8_t *)msg0, strlen(msg0)); // Send all values
  vw_wait_tx();                           // Wait for tx to finish
  digitalWrite(13, LOW);                  //Indicate transmission end
  delay(40);                            // Wait 1 seconds, then do it again

//For Debugging
 //   Serial.write(msg0);
 //   Serial.println();  
}
