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
  //pinMode(PWM_SPEAKER_PIN, OUTPUT);

  Serial.begin(9600);

  // initialize User Parameters object
  //UserParameters UsrPrm;

  // initialize SPI bus and MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
}

// the loop function runs infinitely while the board is powered
void loop()
{
   // TODO: implement RFIDoggy Door control
}
