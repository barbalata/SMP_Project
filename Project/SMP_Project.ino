/*<-- Libraries -->*/
#include "Functions.h"

bool isOk_1 = false;
bool isOk_2 = false;

void setup() {
  // Leds
  pinMode(led_sent, OUTPUT);
  pinMode(led_recieved, OUTPUT);

  // Reciever
  Serial.begin(9600);
  mySwitchRx.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

  // Transmitter
  mySwitchTx.enableTransmit(7);  // Using Pin #7 --> Transmitter
  mySwitchTx.setProtocol(protocol);
  mySwitchTx.setPulseLength(pulseLength);

  // Display
  lcd.begin(16, 2);
  lcd.clear();

  // Real Time Clockx
  if (! rtc.begin()) {
    Serial.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.print("RTC is NOT running!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // READY TO GO!
  change_time = rtc.now();
  change_time_2 = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print("1 - " + String(button1_action));

  lcd.setCursor(0, 1);
  lcd.print("2 - " + String(button1_action_2));
}

void loop() {
  DateTime now = rtc.now();
  isOk_1 = false;
  isOk_2 = false;
  //Reciever
  if (mySwitchRx.available()) {
    Serial.println("Value: " + String(mySwitchRx.getReceivedValue()));
    Serial.println("Delay: " + String(mySwitchRx.getReceivedDelay()));
    Serial.println("Protocol: " + String(mySwitchRx.getReceivedProtocol()));

    if (mySwitchRx.getReceivedProtocol() == 2) {
      if (mySwitchRx.getReceivedValue() == 12165000) {
        isOk_1 = true;
      }
      else if (mySwitchRx.getReceivedValue() == 12165001) {
        isOk_1 = false;
      }
      else if (mySwitchRx.getReceivedValue() == 22165001) {
        isOk_2 = true;
      }
      else if (mySwitchRx.getReceivedValue() == 22165001) {
        isOk_2 = false;
      }
      else{
        isOk_1 = false;
        isOk_2 = false;
      }
    }
    displayRecievedMessage(lcd,  mySwitchRx.getReceivedValue());

    change_time = rtc.now();

    mySwitchRx.resetAvailable();
  }

  // Transmitter
  /*
      The message will be send when the user will press the button (ON/OFF) or automatically after 5 seconds since last send.
  */

  button1_status = digitalRead(buttonPin);
  if (button1_status == HIGH  || now.unixtime() - change_time.unixtime() > 10 ) {
    button1_action = ! button1_action;

    if (button1_action) {
      last_code_on = sendCode(mySwitchTx, last_code_on, button1_action);
    }
    else {
      last_code_off = sendCode(mySwitchTx, last_code_off, button1_action);
    }

    digitalWrite(led_sent, (button1_action ? HIGH : LOW));
    change_time = rtc.now();
  }

  // Button 2
  button1_status_2 = digitalRead(buttonPin_2);
  if (button1_status_2 == HIGH  || now.unixtime() - change_time_2.unixtime() >  30) {
    button1_action_2 = ! button1_action_2;

    if (button1_action_2) {
      last_code_on_2 = sendCode2(mySwitchTx, last_code_on_2, button1_action_2);
    }
    else {
      last_code_off_2 = sendCode2(mySwitchTx, last_code_off_2, button1_action_2);
    }

    change_time_2 = rtc.now();
  }
  lcd.setCursor(0, 0);
  lcd.print("1 - " + String(isOk_1));

  lcd.setCursor(0, 1);
  lcd.print("2 - " + String(isOk_1));
}
