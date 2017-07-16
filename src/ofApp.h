#pragma once

#include "ofMain.h"
#include "ofxEasyFft.h"
#include "ofEvents.h"

class ofApp : public ofBaseApp{

 public:
  void setup();
  void update();
  void draw();
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  ofxEasyFft fft; // ofxEasyFftインスタンス
  ofArduino	ard;
  bool		bSetupArduino;

 private:
  void setupArduino(const int & version);
  void updateArduino();
};
