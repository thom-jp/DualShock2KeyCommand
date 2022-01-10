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

enum eMode {
  e_none,
  e_outlook,
  e_touhou,
  e_mouse
};

USB Usb;
PS4USB PS4(&Usb);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
uint8_t oldRightHatX, oldRightHatY;
uint8_t redundant;
eMode mode;
float accm_w = 0;
float r = 0;
float x = 0;
float y = 0;
bool disconnected;

class MouseHandler {
  private:
    float accm_x = 0;
    float accm_y = 0;
    float accm_w = 0;
  public:
    int divider = 8;
    void move(float xVal, float yVal);
    void wheel(float wVal);
};

MouseHandler mh;

void MouseHandler::move(float xVal, float yVal) {
  accm_x += xVal / divider;
  accm_y += yVal / divider;
  Mouse.move((int)accm_x, (int)accm_y, 0);
  accm_x -= (int)accm_x;
  accm_y -= (int)accm_y;
}

void MouseHandler::wheel(float wVal) {
  accm_w += (float)wVal/4096;
  Mouse.move(0, 0, (int)accm_w);
  accm_w -= (int)accm_w;
}

void setup() {
  if (Usb.Init() == -1) {
    while (1); // Halt
  }
  Mouse.begin();
  redundant = 1;
  mode = e_none;
  disconnected = false;
}

void loop() {
  Usb.Task();
  if (PS4.connected()) {
    if (PS4.getButtonPress(PS)){
      if (PS4.getButtonClick(TRIANGLE)) {
        PS4.setRumbleOn(RumbleHigh);
        disconnected = true;
        mode = e_outlook;
      }
      if (PS4.getButtonClick(CROSS)) {
        PS4.setRumbleOn(RumbleHigh);
        PS4.setLed(Blue);
        mode = e_none;
      }
      if (PS4.getButtonClick(CIRCLE)) {
        PS4.setRumbleOn(RumbleHigh);
        disconnected = true;
        mode = e_touhou;
      }
      if (PS4.getButtonClick(SQUARE)) {
        PS4.setRumbleOn(RumbleHigh);
        disconnected = true;
        mode = e_none;
      }
      if (PS4.getButtonClick(R1)) {
        PS4.setRumbleOn(RumbleHigh);
        disconnected = true;
        mode = e_mouse;
      }
    }

    switch(mode){
      case e_outlook:
        if(disconnected) {
          PS4.setLed(0,255,100);
          disconnected = false;
        }
        mode_outlook();
        break;
      case e_touhou:
        if(disconnected) {
          PS4.setLed(Red);
          disconnected = false;
        }
        mode_touhou();
        break;
      case e_mouse:
        if(disconnected) {
          PS4.setLed(Yellow);
          disconnected = false;
        }
        if(disconnected) PS4.setLed(Yellow);
        mode_mouse();
        break;
    }
  } else {
    disconnected = true;
  }
}

void press_sync(ButtonEnum pad, char key) {
    if (PS4.getButtonPress(pad)) {
      Keyboard.press(key);
    } else {
      Keyboard.release(key);
    }
}

void click_sync(ButtonEnum pad, char key) {
  if (PS4.getButtonClick(pad)) {
    Keyboard.press(key);
    delay(40);
    Keyboard.release(key);
  }
}

void mode_touhou(){
  press_sync(CROSS, 'z');
  press_sync(UP, KEY_UP_ARROW);
  press_sync(RIGHT, KEY_RIGHT_ARROW);
  press_sync(DOWN, KEY_DOWN_ARROW);
  press_sync(LEFT, KEY_LEFT_ARROW);
  press_sync(R1, KEY_LEFT_SHIFT);
  click_sync(L1,'x');
  click_sync(SQUARE,'c');
  click_sync(OPTIONS,KEY_ESC);
}

void mode_outlook(){
  if (PS4.getButtonPress(PS)&& ((abs(128 - PS4.getAnalogHat(RightHatX)) + abs(128 - PS4.getAnalogHat(RightHatX))) >= 127)) {
    //TopRight
    if (PS4.getAnalogHat(RightHatX) >= 128 && PS4.getAnalogHat(RightHatY) < 128 ) {
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, 1);
        mh.wheel(1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, -1);
        mh.wheel(-1);
        Keyboard.releaseAll();
      }
    }
    
    //BottomRight
    if (PS4.getAnalogHat(RightHatX) >= 128 && PS4.getAnalogHat(RightHatY) >= 128 ) {
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, 1);
        mh.wheel(1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, -1);
        mh.wheel(-1);
        Keyboard.releaseAll();
      }
    }
    
    //BottomLeft
    if (PS4.getAnalogHat(RightHatX) < 128 && PS4.getAnalogHat(RightHatY) >= 128 ) {
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, 1);
        mh.wheel(1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, -1);
        mh.wheel(-1);
        Keyboard.releaseAll();
      }
    }
    
    //TopLeft
    if (PS4.getAnalogHat(RightHatX) < 128 && PS4.getAnalogHat(RightHatY) < 128 ) {
      if (oldRightHatX + redundant < PS4.getAnalogHat(RightHatX) && oldRightHatY - redundant > PS4.getAnalogHat(RightHatY)) {
        //RightRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, 1);
        mh.wheel(1);
        Keyboard.releaseAll();
      }
      if (oldRightHatX - redundant > PS4.getAnalogHat(RightHatX) && oldRightHatY + redundant < PS4.getAnalogHat(RightHatY)) {
        //LeftRotate
        Keyboard.press(KEY_LEFT_CTRL);
        //Mouse.move(0, 0, -1);
        mh.wheel(-1);
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
  }
  if (PS4.getButtonClick(R1)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('.');
    delay(100);
    Keyboard.releaseAll();
  }
}

void mode_mouse() {
    y = PS4.getAnalogHat(LeftHatY)-128;
    x = PS4.getAnalogHat(LeftHatX)-128;
    r = sqrt(pow(x,2) + pow(y,2));
    if (PS4.getButtonPress(R1)) {
      mh.divider = 64;
    } else {
      mh.divider = 8;
    }
    if (r > 5) {
     mh.move(x, y);
    }
    if (PS4.getButtonPress(CROSS)) {
      Mouse.press();
    } else {
      Mouse.release();
    }
    if (PS4.getButtonPress(TRIANGLE)) {
      Mouse.press(MOUSE_RIGHT);
    } else {
      Mouse.release(MOUSE_RIGHT);
    }
    press_sync(L1, KEY_LEFT_CTRL);
    
    int r2 = PS4.getAnalogButton(R2);
    int l2 = PS4.getAnalogButton(L2);
    if (l2) {
      mh.wheel(l2);
    }
    if (r2) {
      mh.wheel(-r2);
    }

    press_sync(OPTIONS, 'f');

    if (PS4.getButtonPress(PS)){
      if (PS4.getButtonClick(UP)) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(';');
        Keyboard.releaseAll();
      }
      if (PS4.getButtonClick(DOWN)) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press('-');
        Keyboard.releaseAll();
      }
    }
    else {
      press_sync(UP, KEY_PAGE_UP);
      press_sync(DOWN, KEY_PAGE_DOWN);
      press_sync(RIGHT, KEY_RIGHT_ARROW);
      press_sync(LEFT, KEY_LEFT_ARROW);
    }
}
