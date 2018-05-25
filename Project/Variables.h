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
const int rs = 8, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button
const int buttonPin = 10;
bool button1_status = false;
bool button1_action = false;


const int buttonPin_2 = 11;
bool button1_status_2 = false;
bool button1_action_2 = false;

// LEDS
int const led_sent = 13;
int const led_recieved = 10;

// Auxiliar variables
DateTime change_time;
unsigned long last_code_on = 12165804;
unsigned long last_code_off = 11807932;

DateTime change_time_2;
unsigned long last_code_on_2 = 22165804;
unsigned long last_code_off_2 = 21807932;

unsigned long const code_on[] = {12165804, 11696236, 12518172, 11567196};
unsigned long const code_off[] = {11807932, 12470652, 12319532, 11982220};

unsigned long const code_on_2[] = {22165804, 21696236, 22518172, 21567196};
unsigned long const code_off_2[] = {21807932, 22470652, 22319532, 21982220};
int const protocol = 3;
int const pulseLength = 101;


char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


//
