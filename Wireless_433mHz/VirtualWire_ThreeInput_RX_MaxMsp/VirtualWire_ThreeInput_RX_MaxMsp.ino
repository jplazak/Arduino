/* 
Receive Three Analog Variables (hard-coded for 3 digit values) via 433mHz radios
These variables can be recorded or used for digitalWrites.  
*/
#include <VirtualWire.h>

int i;
char Sensor1CharMsg[5]; 
char Sensor2CharMsg[5]; 
char Sensor3CharMsg[5]; 
int Sensor1Data;
int Sensor2Data;
int Sensor3Data;

void setup() {
  Serial.begin(9600);              
  vw_setup(4800);                  // VirtualWire communication speed
  vw_rx_start();                   // Getting redy to receive
  vw_set_rx_pin(11);               // Set VirtualWire receive pin
}

// Loop function - runs forever
void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];      // Variable to hold the received data
  uint8_t buflen = VW_MAX_MESSAGE_LEN;  // Variable to hold the length of the received data
 
 // If data is received
  if (vw_get_message(buf, &buflen)) {
         // Get the three first bytes
         for (i=0;i<3;i++) {
            Sensor1CharMsg[i] = char(buf[i]);
         }  
        
         // Get the next three bytes
         for (i=3;i<6;i++) {
            Sensor2CharMsg[i-3] = char(buf[i]);          
         }  
        
         // Get the last three bytes
         for (i=6;i<10;i++) {
            Sensor3CharMsg[i-6] = char(buf[i]);          
         }  
         
         //Transform String Data to Ints
           Sensor1Data = atoi(Sensor1CharMsg);
           Sensor2Data = atoi(Sensor2CharMsg);
           Sensor3Data = atoi(Sensor2CharMsg);
         
         //Clear Buffer Legnth to avoid size errors
           Sensor1CharMsg[buflen] = '\0';
           Sensor2CharMsg[buflen] = '\0';
           Sensor3CharMsg[buflen] = '\0';
         
         //Display Data in Serial Monitor  
           Serial.print(Sensor1Data);
           Serial.print(" ");
           Serial.print(Sensor2Data);
           Serial.print(" ");
           Serial.println(Sensor3Data);
    }

}

