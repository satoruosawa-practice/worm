//#include "ofApp.h"
//
//void ofApp::setup(){
//  ofSetFrameRate(60);
//  ofSetVerticalSync(true);
//  ofBackground(0);
//  // FFTのサンプル数(2の累乗)を指定して初期化
//  fft.setup(pow(2.0, 12.0));
//}
//
//void testApp::setup(){
//  ofSetVerticalSync(true);
//  ofSetFrameRate(60);
//  ofBackground(255,0,130);
//  bgImage.loadImage("firmata.png");
//  font.loadFont("franklinGothic.otf", 20);
//  ard.connect("/dev/tty.usbmodem1411", 9600);
//  // listen for EInitialized notification. this indicates that
//  // the arduino is ready to receive commands and it is safe to
//  // call setupArduino()
//  ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
//  bSetupArduino = false;
//}
//
//void ofApp::update(){
//  fft.update(); // FFT更新
//}
//
//void ofApp::draw(){
//  // float型の配列にFFT結果を格納
//  vector<float> buffer;
//  buffer = fft.getBins();
//  // グラフに描画
//  ofNoFill();
//  ofSetLineWidth(2.0);
//  ofBeginShape();
//  float maxi = 0;
//  for (int i = 0; i < buffer.size(); i++) {
//    if (buffer[maxi] < buffer[i]) {
//      maxi = i;
//    }
//    float x = ofMap(i, 0, buffer.size(), 0, ofGetWidth() * 5);
//    float y = ofMap(buffer[i], 0, 1, ofGetHeight() - 100, 0);
//    
//    ofVertex(x, y);
//  }
//  float ff = 22050.5 / pow(2.0, 17.0);  // 変換係数
//  std::cout<< maxi << std::endl;
//  std::cout<< buffer.size() << std::endl;
//  std::cout<< maxi * ff << " Hz" << std::endl;
//  
//  ofEndShape();
//}



#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
  ofSetVerticalSync(true);
  ofSetFrameRate(60);
  ofBackground(0);

  ard.connect("/dev/cu.usbmodem1411", 57600);
  ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
  bSetupArduino	= false;
}

//--------------------------------------------------------------
void ofApp::update(){
  updateArduino();
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
  ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
  bSetupArduino = true;

  ofLogNotice() << ard.getFirmwareName();
  ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
  
  ard.sendDigitalPinMode(13, ARD_OUTPUT);
  ard.sendDigitalPinMode(11, ARD_PWM);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
  ard.update();
  if (bSetupArduino) {
    ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));
  }
}


//--------------------------------------------------------------
void ofApp::draw(){
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
