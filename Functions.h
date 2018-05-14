#include "Variables.h"

/*<-- FUNCTIONS -->*/

// Auxiliar functions
int sizeOf(unsigned long *input) {
  return sizeof(input) / sizeof(unsigned long);
}

int sizeOf(int *input) {
  return sizeof(input) / sizeof(int);
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
unsigned long sendCode (RCSwitch switchTX, unsigned long lastCode) {
  //Get next code
  unsigned long* codeType = ( getTypeOfCode(lastCode) ? code_on : code_off);
  int currentCodeIndex = getCodeIndex (lastCode);
  if ( currentCodeIndex >= sizeOf(codeType)) {
    currentCodeIndex = -1;
  }

  //Send the code
  for (int i = 0; i < sizeOf(protocol); i++) {
    for (int j = 0; j < sizeOf(pulseLength); j++) {
      switchTX.setProtocol(protocol[i]);
      switchTX.setPulseLength(pulseLength[j]);

      switchTX.send(codeType[currentCodeIndex ++], 24);
    }
  }
  return codeType[currentCodeIndex];
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
