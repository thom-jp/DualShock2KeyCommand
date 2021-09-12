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
uint8_t mode;

void setup() {
  if (Usb.Init() == -1) {
    while (1); // Halt
  }
  Mouse.begin();
  redundant = 1;
  mode = 0;
  /* Serial1.begin(9600);
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  */
}

void loop() {
  Usb.Task();
  if (PS4.connected()) {
    if (PS4.getButtonPress(PS)){
      if (PS4.getButtonClick(TRIANGLE)) {
        PS4.setRumbleOn(RumbleHigh);
        PS4.setLed(0,255,100);
        mode = 1;
      }
      if (PS4.getButtonClick(CROSS)) {
        PS4.setRumbleOn(RumbleHigh);
        PS4.setLed(Blue);
        mode = 0;
      }
      if (PS4.getButtonClick(CIRCLE)) {
        PS4.setRumbleOn(RumbleHigh);
        PS4.setLed(Red);
        mode = 2;
      }
    }

    switch(mode){
      case 1:
        mode1();
        break;
      case 2:
        mode2();
        break;
    }
  }
}

void mode2(){
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

  if (PS4.getButtonClick(TRIANGLE)) {
    Keyboard.press('c');
    delay(40);
    Keyboard.releaseAll();
  }

  if (PS4.getButtonClick(OPTIONS)) {
    Keyboard.press(KEY_ESC);
    delay(40);
    Keyboard.releaseAll();
  }

}
void mode1(){
  if (PS4.getButtonPress(PS)&& ((abs(128 - PS4.getAnalogHat(RightHatX)) + abs(128 - PS4.getAnalogHat(RightHatX))) >= 127)) {
    //TopRight
    if (PS4.getAnalogHat(RightHatX) >= 128 && PS4.getAnalogHat(RightHatY) < 128 ) {
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, 1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, -1);
        Keyboard.releaseAll();
      }
    }
    
    //BottomRight
    if (PS4.getAnalogHat(RightHatX) >= 128 && PS4.getAnalogHat(RightHatY) >= 128 ) {
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, 1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, -1);
        Keyboard.releaseAll();
      }
    }
    
    //BottomLeft
    if (PS4.getAnalogHat(RightHatX) < 128 && PS4.getAnalogHat(RightHatY) >= 128 ) {
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, 1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, -1);
        Keyboard.releaseAll();
      }
    }
    
    //TopLeft
    if (PS4.getAnalogHat(RightHatX) < 128 && PS4.getAnalogHat(RightHatY) < 128 ) {
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, 1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        Mouse.move(0, 0, -1);
        Keyboard.releaseAll();
      }
    }
  }
  oldRightHatX = PS4.getAnalogHat(RightHatX);
  oldRightHatY = PS4.getAnalogHat(RightHatY);

  int r2 = PS4.getAnalogButton(R2);
  int l2 = PS4.getAnalogButton(L2);
  if (r2) {
    Keyboard.press(KEY_DOWN_ARROW);
    if (r2 < 100) {
      delay(80);
    } else if (r2 < 255) {
      delay(24);
    } else {
      delay(12);
    }
    Keyboard.releaseAll();
  }
  if (l2) {
    Keyboard.press(KEY_UP_ARROW);
    if (l2 < 100) {
      delay(80);
    } else if (l2 < 255) {
      delay(24);
    } else {
      delay(12);
    }
    Keyboard.releaseAll();
  }
  /*
  if (PS4.getAnalogButton(R2)) {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(256-PS4.getAnalogButton(R2));
    Keyboard.releaseAll();
  }
  
  if (PS4.getAnalogButton(L2)) {
    Keyboard.press(KEY_UP_ARROW);
    delay(256-PS4.getAnalogButton(L2));
    Keyboard.releaseAll();
  }
  */

  if (PS4.getButtonClick(PS)) {
    
  }
  
  if (PS4.getButtonClick(TRIANGLE)) {
    Keyboard.press('a');
    delay(100);
    Keyboard.releaseAll();
  }
  if (PS4.getButtonClick(CIRCLE)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('1');
    delay(100);
    Keyboard.releaseAll();
  }
  if (PS4.getButtonClick(CROSS)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('d');
    delay(100);
    Keyboard.releaseAll();
  }
  if (PS4.getButtonClick(SQUARE)) {
  }

  if (PS4.getButtonPress(UP)) {
    Keyboard.press(KEY_PAGE_UP);
    delay(40);
    Keyboard.releaseAll();
  } if (PS4.getButtonClick(RIGHT)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('.');
    delay(100);
    Keyboard.releaseAll();
  } if (PS4.getButtonPress(DOWN)) {
    Keyboard.press(KEY_PAGE_DOWN);
    delay(40);
    Keyboard.releaseAll();
  } if (PS4.getButtonClick(LEFT)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(',');
    delay(100);
    Keyboard.releaseAll();
  }

  if (PS4.getButtonClick(L1)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(',');
    delay(100);
    Keyboard.releaseAll();
    //myDFPlayer.play(1);
  }
  if (PS4.getButtonClick(L3)) {
    
  }
  if (PS4.getButtonClick(R1)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('.');
    delay(100);
    Keyboard.releaseAll();
    //myDFPlayer.play(2);
  }
  if (PS4.getButtonClick(R3)) {
  }

  if (PS4.getButtonClick(SHARE)) {
  }
  if (PS4.getButtonClick(OPTIONS)) {
  }
  if (PS4.getButtonClick(TOUCHPAD)) {
  }
}
