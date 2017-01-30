#GSM Enabled Smart Mail Box

##The Project
The aim of this project was to develop an effective solution to getting a notification when receiving physical Mail. The project can be deployed in a Home or Office environment. It helps keep mail secure with the integrated locking mechanism on the Mailbox. It can be particularly useful when your are not at Home or in the Office and you need someone to get your mail incase it contains important information or is of considerable value.

One use of this project in an office environment would be to use it in the pigeon hole system so the owner would get an notification whent hey have mail so they can go and get it. With the current processes Mail can arrive at anytime up to a 2-10 day period.

##Hardware
The components I used in this project were:
<ul>
<li>Arduino Uno</li>
<li>Arduino GSM Shield</li>
<li>Seeed Studio NFC Shield V2.0</li>
<li>Servo</li>
<li>FSR (Force Sense Resistors</li>
<li>1 Green & 1 Red LED</li>
<li>4 220R Resistors</li>
<li>Strip Board</li>
</ul>

When putting together the Arduino Baord and the GSM Shield, please ensure you do not use Pins that are used for communication. Avoid using:

<ul>
<li>Pin 7 - Modem Reset Pin</li>
<li>Pin 3 - GSM TX</li>
<li>Pin 2 - GSM RX</li>
<li>Pin 0 & 1 - Not connected</li>
</ul>

In relation to using the NFC Shield. I used a Seeed Studio NFC Shield V2.0. Again, when connecting to the Arduino Board, do not use:
<ul>
<li>Pin 10 & 9 - used for SPI chip select (CS/SS)</li>
</ul>

When connecting both the NFC Shield GSM Shield to the Arduino, place the NFC Shield first then add the GSM Shield. If you connect the GSM Shield first then the NFC Shield will not be able to use D2 for the interrupt request (IRQ) as the GSM Shield uses D2 for GSM RX.

##Help
If you need help please refer to the relevant forums and documentation for the components, all the information you will need is on there. Most questions you ask are answered and explained well. I have put toegther a list for for all of the the compnents I used:
<ul>
<li>https://forum.arduino.cc/ - Arduino Forum</li>
<li>https://www.arduino.cc/en/Main/ArduinoBoardUno - Arduino Uno Documentation</li>
<li>https://www.seeed.cc/ - Seeed Studio Forum</li>
<li>http://wiki.seeed.cc/NFC_Shield_V2.0/ - Seeed Studio NFC Shield Wiki</li>
<li>https://www.arduino.cc/en/Main/ArduinoGSMShield - Arduino GSM Shield Documentation</li>
</ul>
