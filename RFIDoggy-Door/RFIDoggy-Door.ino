/*  
    RFIDoggy-Door.ino

    run RFIDoggy Door control   
*/

#include "include/UserParameters.h"

#include <SPI.h>
#include <MFRC522.h>

/*****************************************************************************/
/*                                 PINOUT                                    */

// TMP36 Temperature Sensor
#define AI_TEMP_SENSOR_PIN    A0

// Soil Moisture Sensor
#define AI_MOIST_SENSOR_PIN   A1

// Speaker
#define PWM_SPEAKER_PIN       3

//Test LED
#define EXTLED                7

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

MFRC522 mfrc522[NR_OF_READERS]; // Create MFRC522 instance.

// the setup function runs once when you press reset or power the board
void setup()
{
  // outputs
  //pinMode(DO_SOLENOID_PIN, OUTPUT);
  //pinMode(PWM_SPEAKER_PIN, OUTPUT);
  pinMode(EXTLED, OUTPUT);

  Serial.begin(9600);

  // initialize User Parameters object
  //UserParameters UsrPrm;

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

      // Looking for new cards
      if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
        Serial.print(F("Reader "));
        Serial.print(reader);

        // Show some details of the PICC (that is: the tag/card)
        Serial.print(F(": Card UID:"));
        tag = printTagUID(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
        Serial.println(tag);
        if(tag == "8be5c8c")
        {
          Serial.println("SUCCESS");
          digitalWrite(EXTLED, HIGH);
          delay(2000);
          digitalWrite(EXTLED, LOW);
        }
        else
        {
          Serial.println("FAIL");
        }
      }
      //delay(50);
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
