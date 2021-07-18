#include <Keyboard.h>
#include <Mouse.h>
#include <PS4USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// #include "Arduino.h"
// #include "DFRobotDFPlayerMini.h"
// DFRobotDFPlayerMini myDFPlayer;

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
uint8_t oldRightHatX, oldRightHatY;
uint8_t redundant;

void setup() {
  if (Usb.Init() == -1) {
    while (1); // Halt
  }
  Mouse.begin();
  redundant = 1;
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    if (PS4.getButtonClick(PS)) {
    }
    if (PS4.getButtonPress(TRIANGLE)) {
    }
    if (PS4.getButtonClick(CIRCLE)) {
    }
    if (PS4.getButtonPress(CROSS)) {
      Keyboard.press('z');
    } else {
      Keyboard.release('z');
    }
    
    if (PS4.getButtonClick(SQUARE)) {
    }

    if (PS4.getButtonPress(UP)) {
      Keyboard.press(KEY_UP_ARROW);
    } else {
      Keyboard.release(KEY_UP_ARROW);
    }
    if (PS4.getButtonPress(RIGHT)) {
      Keyboard.press(KEY_RIGHT_ARROW);
    } else {
      Keyboard.release(KEY_RIGHT_ARROW);
    }
    if (PS4.getButtonPress(DOWN)) {
      Keyboard.press(KEY_DOWN_ARROW);
    } else {
      Keyboard.release(KEY_DOWN_ARROW);
    }
    if (PS4.getButtonPress(LEFT)) {
      Keyboard.press(KEY_LEFT_ARROW);
    } else {
      Keyboard.release(KEY_LEFT_ARROW);
    }

    if (PS4.getButtonPress(R1)) {
      Keyboard.press(KEY_LEFT_SHIFT);
    } else {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    
    if (PS4.getButtonClick(L1)) {
      Keyboard.press('x');
      delay(40);
      Keyboard.releaseAll();
    }
 
    if (PS4.getButtonClick(OPTIONS)) {
      Keyboard.press(KEY_ESC);
      delay(40);
      Keyboard.releaseAll();
    }
  }
}
