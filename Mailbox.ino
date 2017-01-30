#include <GSM.h>
#include <SPI.h>
#include <Servo.h>
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"

GSM gsmAccess;
GSM_SMS sms;
char remoteNumber[20] = "***********"; //number where the text is sent

int servoPin = 5; //digital pin which the Servo is connected
Servo Servo1; //declaring the servo object

String const myUID = "E0 04 79 DE"; // NFC tags UID
int const greenLedPin = 7; // green led used for correct key notification
int const redLedPin = 6; // red led used for incorrect key notification

PN532_SPI interface(SPI, 10); // create a SPI interface for the shield with the SPI CS terminal at digital pin 10
NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object

int y;
const int input[5] = {A0,A1,A2, A3, A4}; //array to hold the analog pins
int result[5];
int fsrReading; //int to hold the FSR readings
int endTotal; //average reading of the FSRs
boolean messageSent = false; //boolean to inform whether a message has been sent
boolean notConnected = false; //boolean to inform whether the SIM has been connected

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
      notConnected == false;
    }
    else
    {
      Serial.println("Failed");
    }
    delay(1000);
  }
  Serial.println("OK");
  Serial.println("SMS Setup Complete");
  
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
  //if statement to decide whether or not to initialise setupSMS()
  if (notConnected == false) {
    setupSMS();
  }
  
  Servo1.write(0); //set the servo to 0
  //if statement to decide whether or not to initialise startNFC()
  if (nfc.tagPresent()) { // check if an NFC tag is present on the antenna area
    startNFC(); //initialise startNFC
  }
}

//method to decide whether to send an SMS depending on FSR readings
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

//method to send a SMS
void sendSMS() {
  sms.beginSMS(remoteNumber);
  sms.println("You have mail to collect");
  delay(500);
  sms.endSMS();
  Serial.println("\nSent\n");
  sms.flush();
  messageSent = true;
}

//method to determine correct key has been detected and to power servo
void startNFC() {
    NfcTag tag = nfc.read(); // read the NFC tag
    String scannedUID = tag.getUidString(); // get the NFC tag's UID

    if (myUID.compareTo(scannedUID) == 0) { // compare the NFC tag's UID with the correct tag's UID (a match exists when compareTo returns 0)
      // The correct NFC tag was used
      Serial.println("Correct Key");
      // turn on green LED and make sure the RED led is off
      digitalWrite(greenLedPin,HIGH);
      digitalWrite(redLedPin,LOW);

      digitalWrite(greenLedPin,HIGH);
      delay(500);
      
      Servo1.write(45); //turn servo 45 degrees
      delay (10000); //wait 10 sendonds
      Servo1.write(0); //reset servo position
      digitalWrite(greenLedPin,LOW); //turn green LED off
      
    } else {
      // an incorrect NFC tag was used
      Serial.println("Incorrect key");
      // turn on red LED and make sure the green LED is off
      digitalWrite(greenLedPin,LOW);
      digitalWrite(redLedPin,HIGH);

      delay(2000); //wait 2 seconds
      digitalWrite(redLedPin,HIGH); //turn red LED on
      delay(500); //wait 0.5 seconds
      digitalWrite(redLedPin,LOW); //turn red LED off
            }
      delay(2000);
}

