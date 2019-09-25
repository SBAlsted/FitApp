#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

#include "BluefruitConfig.h"


/*=========================================================================
       -----------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/


/* ...software SPI, using SCK/MOSI/MISO user-defined SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_SCK, BLUEFRUIT_SPI_MISO, BLUEFRUIT_SPI_MOSI, BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

int ledPin1 = 10;
int ledPin2 = 9;
int ledPin3 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  digitalWrite(ledPin1, LOW);  // turn LED OFF
  digitalWrite(ledPin2, LOW);  // turn LED OFF
  digitalWrite(ledPin3, LOW);  // turn LED OFF

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Command <-> Data Mode Example"));
  Serial.println(F("------------------------------------------------"));


    /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ) {
      error(F("Couldn't factory reset"));
    }
  }

  //Give module a new name
  ble.println("AT+GAPDEVNAME=FitApp"); // named FitApp

  // Set module to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop() {
  
  if(! ble.isConnected()){
    digitalWrite(ledPin1, LOW);  // turn LED OFF
    digitalWrite(ledPin2, LOW);  // turn LED OFF
    digitalWrite(ledPin3, LOW);  // turn LED OFF
  }else{
    digitalWrite(ledPin1, HIGH);  // turn LED ON
    delay(1000);
    digitalWrite(ledPin1, LOW);  // turn LED OFF
    digitalWrite(ledPin2, HIGH);  // turn LED ON
    delay(1000);
    digitalWrite(ledPin2, LOW);  // turn LED OFF
    digitalWrite(ledPin3, HIGH);  // turn LED ON
    delay(1000);
    digitalWrite(ledPin3, LOW);  // turn LED OFF
  } 
  
}
