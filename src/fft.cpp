//
//  fft.cpp
//  worm
//
//  Created by OSAWASatoru on 2017/07/30.
//
//

#include "./fft.h"

void Fft::setup(ofSerial &serial) {
  serial_ = &serial;
  
  // FFTのサンプル数(2の累乗)を指定して初期化
  ff_factor_ = 10.0;
  fft_.setup(pow(2.0, ff_factor_));
  f_div_ = 22050.5 / pow(2.0, ff_factor_ - 1.0);
}

void Fft::update() {
  fft_.update(); // FFT更新
}

void Fft::draw() {
  buffer_ = fft_.getBins();
  ofNoFill();
  ofSetLineWidth(1.0);
  float max_volume_i = 0;
  for (int i = 0; i < buffer_.size(); i++) {
    if (buffer_[max_volume_i] < buffer_[i]) {
      max_volume_i = i;
    }
    float x = getWindowPosX(i * f_div_);
    float y = ofMap(buffer_[i], 0, 1, ofGetHeight() - 100, 0);
    ofBeginShape(); {
      ofVertex(x, y);
      ofVertex(x, ofGetHeight() - 100);
    } ofEndShape();
  }
  
  if(max_volume_i * f_div_ > 700 && max_volume_i * f_div_ < 750) {
    serial_->writeByte('9');
  } else {
    serial_->writeByte('0');
  }
  
  std::cout<< buffer_.size() << std::endl;
  std::cout<< max_volume_i * f_div_ << " Hz" << std::endl;
  drawGuide();
}

int Fft::getWindowPosX(float freq) {
  return ofMap(freq, 100, 5000, 0, ofGetWidth());
}

void Fft::drawGuide() {
  for(int i = 0; i < 10; i++) {
    float freq = i * 500;
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawBitmapString(ofToString(freq),
                       getWindowPosX(freq), ofGetHeight() - 80);
    ofBeginShape(); {
      ofVertex(getWindowPosX(freq), ofGetHeight() - 95);
      ofVertex(getWindowPosX(freq), ofGetHeight() - 100);
    } ofEndShape();
  }
}
