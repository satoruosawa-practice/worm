//
//  fft.h
//  worm
//
//  Created by OSAWASatoru on 2017/07/30.
//
//
#pragma once

#include "ofMain.h"
#include "ofxEasyFft.h"

class Fft {
 public:
  void setup(ofSerial &serial);
  void update();
  void draw();

 private:
  ofSerial * serial_;
  
  int getWindowPosX(float frew);
  void drawGuide();
  ofxEasyFft fft_; // ofxEasyFftインスタンス
  vector<float> buffer_;
  float ff_factor_;
  float f_div_;
};
