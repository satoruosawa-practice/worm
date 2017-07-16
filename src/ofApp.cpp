#include "ofApp.h"

void ofApp::setup(){
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(0);
  // FFTのサンプル数(2の累乗)を指定して初期化
  fft.setup(pow(2.0, 12.0));
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
  float maxi = 0;
  for (int i = 0; i < buffer.size(); i++) {
    if (buffer[maxi] < buffer[i]) {
      maxi = i;
    }
    float x = ofMap(i, 0, buffer.size(), 0, ofGetWidth() * 5);
    float y = ofMap(buffer[i], 0, 1, ofGetHeight() - 100, 0);
    
    ofVertex(x, y);
  }
  float ff = 22050.5 / pow(2.0, 17.0);  // 変換係数
  std::cout<< maxi << std::endl;
  std::cout<< buffer.size() << std::endl;
  std::cout<< maxi * ff << " Hz" << std::endl;
  
  ofEndShape();
}
