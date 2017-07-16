#include "ofApp.h"

void ofApp::setup(){
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(0);
  // FFTのサンプル数(2の累乗)を指定して初期化
  fft.setup(pow(2.0, 15.0));
}

void ofApp::update(){
  fft.update(); // FFT更新
}

void ofApp::draw(){
  // float型の配列にFFT結果を格納
  vector<float> buffer;
  buffer = fft.getBins();
  // グラフに描画
  ofNoFill();
  ofSetLineWidth(2.0);
  ofBeginShape();
  for (int i = 0; i < buffer.size(); i++) {
    float x = ofMap(i, 0, buffer.size(), 0, ofGetWidth());
    float y = ofMap(buffer[i], 0, 1, ofGetHeight() - 100, 0);
    ofVertex(x, y);
  }
  ofEndShape();
}
