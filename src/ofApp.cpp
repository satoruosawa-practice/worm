#include "ofApp.h"

void ofApp::setup(){
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofBackground(0);
  // FFTのサンプル数(2の累乗)を指定して初期化
  ff_factor_ = 12.0;
  fft.setup(pow(2.0, ff_factor_));
  
  // arduino
  ard.connect("/dev/cu.usbmodem1411", 57600);
  ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
  bSetupArduino_	= false;
}

void ofApp::update(){
  fft.update(); // FFT更新
  updateArduino();
}

void ofApp::draw(){
  // float型の配列にFFT結果を格納
//  vector<float> buffer;
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
  float ff = 22050.5 / pow(2.0, ff_factor_ - 1.0);  // 変換係数
  std::cout<< maxi << std::endl;
  std::cout<< buffer.size() << std::endl;
  std::cout<< maxi * ff << " Hz" << std::endl;
  
  ofEndShape();
}



//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
  ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
  bSetupArduino_ = true;

  ofLogNotice() << ard.getFirmwareName();
  ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
  
  ard.sendDigitalPinMode(13, ARD_OUTPUT);
  ard.sendDigitalPinMode(11, ARD_PWM);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
  ard.update();
  if (bSetupArduino_) {
    if (buffer[91] > 0.5){
      ard.sendPwm(11, (int)((buffer[91] - 0.3) * 100));
    } else {
      ard.sendPwm(11, 10);
    }
//    ard.sendPwm(11, (int)(20 + 20 * sin(ofGetElapsedTimef())));
  }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  ard.sendDigital(13, ARD_HIGH);
  ard.sendPwm(11, 255);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  ard.sendDigital(13, ARD_LOW);
  ard.sendPwm(11, 0);
}
