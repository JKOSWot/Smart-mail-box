#include <GSM.h>
#include <SPI.h>
#include <Servo.h>
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"

GSM gsmAccess;
GSM_SMS sms;
char remoteNumber[20] = "***********";

int servoPin = 5;
Servo Servo1;

String const myUID = "E0 04 79 DE"; // replace this UID with your NFC tag's UID
int const greenLedPin = 7; // green led used for correct key notification
int const redLedPin = 6; // red led used for incorrect key notification

PN532_SPI interface(SPI, 10); // create a SPI interface for the shield with the SPI CS terminal at digital pin 10
NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object

int y;
const int input[5] = {A0,A1,A2, A3, A4};
int result[5];
int fsrReading;
int endTotal;
boolean messageSent = false;
boolean notConnected = false;

void setup() {
  //set up connection to serial
  Serial.begin(115200);

  //set up the network connection
  while (!Serial) {
    ;
  }

  while (notConnected) {
    Serial.println("not Connected");
    int r = gsmAccess.begin();
    Serial.println("GSM status " + r);
    if (r == GSM_READY)
    {
      notConnected = false;
    }
    else
    {
      Serial.println("Failed");
    }
    delay(1000);
  }
  Serial.println("OK");
  Serial.println("SMS Setup Complete");
  
  Serial.begin(115200); // start serial comm
  nfc.begin(); // begin NFC comm
  
  // make LED pins outputs
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);

  // turn off the LEDs
  digitalWrite(greenLedPin,LOW);
  digitalWrite(redLedPin,LOW);

  //attach servo to the used pin number
  Servo1.attach(servoPin);

}

void loop() {
  if (notConnected = false) {
    setupSMS();
  }
  
  Servo1.write(0);
  if (nfc.tagPresent()) { // check if an NFC tag is present on the antenna area
    startNFC(); //initialise startNFC
  }
}

void setupSMS() {
  int total = 0;
  for (y = 0; y < 5; y++) {
    result[y] = analogRead(input[y]);
    total += result[y];
  }
  endTotal = (total / 5);
  Serial.println(endTotal);
  delay(1000);

  if (endTotal > 500) {
    if (!messageSent) {
      sendSMS();
    }
  } else {
    (endTotal < 0); {
      messageSent = false;
    }
  }
  delay(1000);
}

void sendSMS() {
  sms.beginSMS(remoteNumber);
  sms.println("You have mail to collect");
  delay(500);
  sms.endSMS();
  Serial.println("\nSent\n");
  sms.flush();
  messageSent = true;
}

void startNFC() {
    NfcTag tag = nfc.read(); // read the NFC tag
    String scannedUID = tag.getUidString(); // get the NFC tag's UID

    if( myUID.compareTo(scannedUID) == 0) { // compare the NFC tag's UID with the correct tag's UID (a match exists when compareTo returns 0)
      // The correct NFC tag was used
      Serial.println("Correct Key");
      // turn on green LED and make sure the RED led is off
      digitalWrite(greenLedPin,HIGH);
      digitalWrite(redLedPin,LOW);

      digitalWrite(greenLedPin,HIGH);
      delay(500);
      
      Servo1.write(0);
      //delay(1000);
      Servo1.write(45);
      delay (10000);
      Servo1.write(0);
      digitalWrite(greenLedPin,LOW);
      
    } else {
      // an incorrect NFC tag was used
      Serial.println("Incorrect key");
      // turn on red LED and make sure the green LED is off
      digitalWrite(greenLedPin,LOW);
      digitalWrite(redLedPin,HIGH);

      delay(2000);
      digitalWrite(redLedPin,HIGH);
      delay(500);
      digitalWrite(redLedPin,LOW);
            }
      delay(2000);
}

