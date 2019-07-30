/*  
    RFIDoggy-Door.ino

    run RFIDoggy Door control   
*/

#include "UserParameters.h"

#include <SPI.h>
#include <MFRC522.h>

/*****************************************************************************/
/*                                 PINOUT                                    */

// TMP36 Temperature Sensor
#define AI_TEMP_SENSOR_PIN    A0

// Soil Moisture Sensor
#define AI_MOIST_SENSOR_PIN   A1

// Solenoid
#define DO_SOLENOID_PIN       8

// Speaker
#define PWM_SPEAKER_PIN       3

// MFRC522 RFID Reader
#define PWM_SS_PIN            10
#define PWM_RST_PIN           9

// HC-05 Bluetooth Module
#define SERIAL_RX_PIN         0
#define SERIAL_TX_PIN         1

// DS3231 RTC
#define AI_SDA_PIN            A4
#define AI_SCL_PIN            A5

/*****************************************************************************/

MFRC522 mfrc522(PWM_SS_PIN, PWM_RST_PIN); // Create MFRC522 instance.

// the setup function runs once when you press reset or power the board
void setup()
{

  // outputs
  pinMode(DO_SOLENOID_PIN, OUTPUT);
  pinMode(PWM_SPEAKER_PIN, OUTPUT);

  Serial.begin(9600);

  // initialize User Parameters object
  UserParameters UsrPrm;

  // initialize SPI bus and MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
}

// the loop function runs infinitely while the board is powered
void loop()
{
   // TODO: implement RFIDoggy Door control
}

// example code to read MFRC522 RFID tag and print data to serial monitor ( File > Examples > MFRC522 > DumpInfo )
// https://randomnerdtutorials.com/security-access-using-mfrc522-rfid-reader-with-arduino/
void mfrc522Example()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}
