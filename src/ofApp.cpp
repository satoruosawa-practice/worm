#include "ofApp.h"

void ofApp::setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(0);
  
  serial_.setup("/dev/cu.usbmodem1411",9600);

  fft_.setup(serial_);
}

void ofApp::update() {
  fft_.update();
}

void ofApp::draw() {
  fft_.draw();
}

void ofApp::keyPressed(int key) {
  switch (key) {
    case '0' :
    case '1' :
    case '2' :
    case '3' :
    case '4' :
    case '5' :
    case '6' :
    case '7' :
    case '8' :
    case '9' :
      serial_.writeByte(key);
      break;
  }
}

