/*<-- Libraries -->*/
#include "Functions.h"

void setup() {
  // Leds
  pinMode(led_sent, OUTPUT);
  pinMode(led_recieved, OUTPUT);

  // Reciever
  Serial.begin(9600);
  mySwitchRx.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  // Transmitter
  mySwitchTx.enableTransmit(8);  // Using Pin #8 --> Transmitter

  // Display
  lcd.begin(16, 2);
  lcd.clear();

  // Real Time Clockx
  if (! rtc.begin()) {
    lcd.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    lcd.print("RTC is NOT running!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // READY TO GO!
  change_time = rtc.now();
}

void loop() {
  DateTime now = rtc.now();

  // Reciever
  if (mySwitchRx.available()) {
    Serial.println("Value: " + String(mySwitchRx.getReceivedValue()));
    Serial.println("Delay: " + String(mySwitchRx.getReceivedDelay()));
    Serial.println("Protocol: " + String(mySwitchRx.getReceivedProtocol()));

    displayRecievedMessage(lcd,  mySwitchRx.getReceivedValue());

    change_time = rtc.now();

    mySwitchRx.resetAvailable();
  }

  // Transmitter
  /*
      The message will be send when the user will press the button (ON/OFF) or automatically after 5 seconds since last send.
  */

  button1_status = digitalRead(buttonPin);
  if (button1_status == HIGH  || now.unixtime() - change_time.unixtime() > 5 ) {
    button1_action = ! button1_action;

    last_sent_code = sendCode(mySwitchTx, last_sent_code);
    digitalWrite(led_sent, (button1_action ? HIGH : LOW));
    change_time = rtc.now();
    displaySentMessage(lcd, last_sent_code);
  }
}
