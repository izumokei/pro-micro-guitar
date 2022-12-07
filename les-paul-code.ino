#include <Keyboard.h>

// Define buttons and corresponding pins
#define BUTTON_COUNT 9

#define PIN_1 5   // Green button,  keyboard 1
#define PIN_2 6   // Red button,    keyboard 2
#define PIN_3 7   // Yellow button, keyboard 3
#define PIN_4 8   // Blue button,   keyboard 4
#define PIN_5 9   // Orange button, keyboard 5

#define PIN_SU 10 // Strum up,      keyboard Enter
#define PIN_SD 16 // Strum down,    keyboard Backspace
#define PIN_ST 14 // Start button,  keyboard Right Shift
#define PIN_SP 15 // Star power,    keyboard Delete

#define DEBOUNCE_TIME 50

byte buttons[9] = {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_SU, PIN_SD, PIN_ST, PIN_SP};

// Button state arrays
byte buttonState[BUTTON_COUNT] = {0};
byte buttonStateLast[BUTTON_COUNT] = {1};

// Define an array of keyboard keys
char keyboardKeys[BUTTON_COUNT] = {
  '1', '2', '3', '4', '5', KEY_RETURN, KEY_BACKSPACE, KEY_RIGHT_SHIFT, KEY_DELETE
};

void setup() {
  // Serial for debug
  Serial.begin(9600);
  // Set all buttons pin mode to INPUT
  // and set them to HIGH
  for(int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  // Begin keyboard emulation
  Keyboard.begin();
}

void loop() {
  // Loop through pins to read inputs
  for(int i = 0; i < BUTTON_COUNT; i++) {
    buttonState[i] = digitalRead(buttons[i]);
    if(buttonState[i] == 0 && buttonStateLast[i] == 1) {
      Keyboard.press(keyboardKeys[i]);
      delay(DEBOUNCE_TIME);
    }
    if(buttonState[i] == 1 && buttonStateLast[i] == 0) {
      Keyboard.release(keyboardKeys[i]);
      delay(DEBOUNCE_TIME);      
    }
    buttonStateLast[i] = buttonState[i];
  }
}
