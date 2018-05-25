#include "Variables.h"

/*<-- FUNCTIONS -->*/

// Auxiliar functions
int sizeOf(unsigned long *input) {
  return sizeof(*input) / sizeof(input[0]);
}

int sizeOf(int *input) {
  return sizeof(*input) / sizeof(input[0]);
}

// Get the type of code: on (true) or off (false)
bool getTypeOfCode(unsigned long code) {
  for (int i = 0; i < sizeOf(code_on); i++) {
    if (code == code_on[i]) {
      return true;
    }
  }
  return false;
}

// Get code index
int getCodeIndex (unsigned long code) {
  unsigned long* codeType = ( getTypeOfCode(code) ? code_on : code_off);
  for (int i = 0; i < sizeOf(codeType); i++) {
    if (code == codeType[i]) {
      return i;
    }
  }
  return -1;
}

// Send code
unsigned long sendCode (RCSwitch switchTX, unsigned long last_code, bool signalType) {
  int index = 0;
  if (signalType) {
    for (int k = 0; k < sizeof(code_on) / sizeof(code_on[0]); k++) {
      if (last_code = code_on[k]) {
        index = k;
      }
    }
    last_code = index != 3 ? code_on[++index] : code_on[0];
  }
  else {
    for (int k = 0; k < sizeof(code_off) / sizeof(code_off[0]); k++) {
      if (last_code = code_off[k]) {
        index = k;
      }
    }
    last_code = index != 3 ? code_off[++index] : code_off[0];
  }

  switchTX.send(last_code, 24);
  Serial.println("Protocol: " + String(protocol) + "; Delay: " + String(pulseLength) + "; Code: " + String(last_code));

  return last_code;
}

unsigned long sendCode2 (RCSwitch switchTX, unsigned long last_code, bool signalType) {
  int index = 0;
  if (signalType) {
    for (int k = 0; k < sizeof(code_on_2) / sizeof(code_on_2[0]); k++) {
      if (last_code = code_on_2[k]) {
        index = k;
      }
    }
    last_code = index != 3 ? code_on_2[++index] : code_on_2[0];
  }
  else {
    for (int k = 0; k < sizeof(code_off_2) / sizeof(code_off_2[0]); k++) {
      if (last_code = code_off_2[k]) {
        index = k;
      }
    }
    last_code = index != 3 ? code_off_2[++index] : code_off_2[0];
  }

  switchTX.send(last_code, 24);
  Serial.println("Protocol: " + String(protocol) + "; Delay: " + String(pulseLength) + "; Code: " + String(last_code));

  return last_code;
}

// Display Fuctions
void displayRecievedMessage(LiquidCrystal LCD, unsigned long sentCode) {
  LCD.setCursor(0, 1);
  LCD.print("R.: " + String(sentCode));
}

void displaySentMessage(LiquidCrystal LCD, unsigned long sentCode) {
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("S.: " + String(sentCode));
}

void displaySocketStatus(LiquidCrystal LCD, int buttonId, bool buttonState, int numberOfPresses) {
  LCD.setCursor(0, 0);
  LCD.print(String(buttonId) + "." + (buttonState == true ? "ON " : "OFF") + " " + String(numberOfPresses));
}

void displayTime(LiquidCrystal LCD, DateTime now) {
  //  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  lcd.print("   ");

  //  lcd.setCursor(0, 0);
  //  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  //  lcd.print(" ,");
  //  lcd.print(now.day());
  //  lcd.print('/');
  //  lcd.print(now.month());
  //  lcd.print('/');
  //  lcd.print(now.year());
}

