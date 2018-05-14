#include <RCSwitch.h> //--> Rx + Tx
#include <LiquidCrystal.h> //Display
#include "RTClib.h"

/*<-- VARIABLES -->*/
// Real Time Clock Module
RTC_DS1307 rtc;

// RF 433 MHz
// - Reciever
RCSwitch mySwitchRx = RCSwitch();

// - Transmitter
RCSwitch mySwitchTx = RCSwitch();

//Display
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button
const int buttonPin = 7;

// LEDS
int const led_sent = 13;
int const led_recieved = 10;

// Auxiliar variables
DateTime change_time;
unsigned long const code_on[] = {12165804, 11696236, 12518172, 11567196};
unsigned long const code_off[] = {11807932, 12470652, 12319532, 11982220};
int const protocol[] = {3, 5};
int const pulseLength[] = {101, 102, 518};

//
