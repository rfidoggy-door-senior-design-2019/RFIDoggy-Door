/*  
    RFIDoggy-Door.ino

    run RFIDoggy Door control   
*/

#include "include/UserParameters.h"
#include <SoftwareSerial.h>

#include <SPI.h>
#include <MFRC522.h>

/*****************************************************************************/
/*                                 PINOUT                                    */

// TMP36 Temperature Sensor
#define AI_TEMP_SENSOR_PIN    A0

// Soil Moisture Sensor
#define AI_MOIST_SENSOR_PIN   A1

// Speaker maybe??
#define PWM_SPEAKER_PIN       3

//Solenoid output pins
#define INSIDE_SOL             7
#define OUTSIDE_SOL             6

// MFRC522 RFID Reader
#define PWM_SDA_PIN1          10
#define PWM_SDA_PIN2          8
#define PWM_RST_PIN           9

// HC-05 Bluetooth Module
#define SERIAL_RX_PIN         0
#define SERIAL_TX_PIN         1

// DS3231 RTC
#define AI_SDA_PIN            A4
#define AI_SCL_PIN            A5

/*****************************************************************************/
#define NR_OF_READERS         2



byte SDAPins[] = {PWM_SDA_PIN1, PWM_SDA_PIN2};

MFRC522 mfrc522[NR_OF_READERS]; // Create MFRC522 instance. READER 0 will be outside reader
SoftwareSerial btm = SoftwareSerial(SERIAL_RX_PIN, SERIAL_TX_PIN); 
int index = 0; 
//used to store incoming data
char incomingData[10];
char incomingCharacter; 
boolean flag = false; 

// the setup function runs once when you press reset or power the board
void setup()
{
  //outputs
  pinMode(SERIAL_RX_PIN, INPUT);
  pinMode(SERIAL_TX_PIN, OUTPUT);
  pinMode(INSIDE_SOL, OUTPUT);
  pinMode(OUTSIDE_SOL, OUTPUT);

  Serial.begin(9600);
  btm.begin(9600); 


  // initialize SPI bus and MFRC522
  SPI.begin();

  for(uint8_t reader = 0; reader<NR_OF_READERS; reader++)
  {
     mfrc522[reader].PCD_Init(SDAPins[reader], PWM_RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

// the loop function runs infinitely while the board is powered
void loop()
{ 
    String tag;
   // TODO: implement RFIDoggy Door control
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {

      if(reader == 1){
        if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
          Serial.print(F("Reader "));
          Serial.print(reader);
  
          // Show some details of the PICC (that is: the tag/card)
          Serial.print(F(": Card UID:"));
          tag = printTagUID(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
          Serial.println(tag);
          
          if(tag == "8be5c8c" && incomingCharacter == 'U'){
            Serial.println("SUCCESS");
            "
            digitalWrite(OUTSIDE_SOL, HIGH);
            delay(2000);
            digitalWrite(OUTSIDE_SOL, LOW);
          }
          else{
            Serial.println("FAIL");
          }
        }
      }
      else{
        if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
          Serial.print(F("Reader "));
          Serial.print(reader);
  
          // Show some details of the PICC (that is: the tag/card)
          Serial.print(F(": Card UID:"));
          tag = printTagUID(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
          Serial.println(tag);
          
          if(tag == "8be5c8c"){
            Serial.println("SUCCESS");
            digitalWrite(INSIDE_SOL, HIGH);
            delay(2000);
            digitalWrite(INSIDE_SOL, LOW);
          }
          else{
            Serial.println("FAIL");
          }
        }
      }
    }
    
    if(btm.available() > 0) {
      while(btm.available() > 0) {
        incomingCharacter = btm.read();
        delay(10); 
        incomingData[index] = incomingCharacter; 
        index++;
      }
      incomingData[index] = '\0';
      flag = true;
    }
    if(flag) {
      flag = false;
      index = 0; 
      incomingData[0] = '\0';
    }
}

String printTagUID(byte * buffer, byte bufferSize) {
  String tag;
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], HEX);
     tag.concat(String(buffer[i], HEX));
  }
  return tag;
}
