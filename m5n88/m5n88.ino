#include "StdHeader.h"
#include <M5stack.h>
#include <M5StackUpdater.h>     // https://github.com/tobozo/M5Stack-SD-Updater/
#include "X88000.h"

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  delay(1000);
  Wire.begin();

  if(digitalRead(BUTTON_A_PIN) == 0) {
     Serial.println("Will Load menu binary");
     updateFromFS(SD);
     ESP.restart();
  }

  Serial.println("Start!");
  
  CX88000 *cx88000 = new CX88000();
  cx88000->Execute();

}

void loop() {
  // put your main code here, to run repeatedly:
}