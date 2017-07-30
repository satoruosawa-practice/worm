#pragma once

#include "ofMain.h"
#include "./fft.h"

class ofApp : public ofBaseApp{
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  ofSerial serial_;
  Fft fft_;
};
