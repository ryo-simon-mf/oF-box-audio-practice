#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    soundStream.printDeviceList();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter    = 0;
    drawCounter        = 0;
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    
    cam.setDistance(1250);
    
    ofBackground(0, 0, 0);
    
    random = ofRandom(50);
    
    pos = ofVec3f(ofRandom(-150,150),//Width
                  ofRandom(-150,150),//Height
                  ofRandom(-150,150));//Depth
    
    updown = 0;
    downup = 0;
    
    
    
    
    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;
    
    box_size = 50;
    
    ofSetFrameRate(120);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    soundplay.load("01.mp3");
    soundplay.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    updown = 15.0 * cos( 1.0 * ofGetFrameNum() );
    downup = 15.0 * sin( 1.0 * ofGetFrameNum() );
    Col_1 = ofColor(ofRandom(120,255),
                    ofRandom(0,255),
                    ofRandom(120,255));
    Col_2 = ofColor(ofRandom(0,255),
                    ofRandom(120,255),
                    ofRandom(0,255));
    
    Col_3 = ofColor(ofRandom(120,255),
                    ofRandom(0,255),
                    ofRandom(0,120));
    
    rotate_x += 0.3;
    rotate_y += 0.3;
    rotate_z += 0.3;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(225);
    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 0, 15);

    ofSetColor(245, 58, 135);
    ofFill();
//    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, scaledVol * 190.0f);
    
    
    
    
    cam.begin();
    ofPushMatrix();
    ofRotateX(-1.0 * rotate_x);
    ofRotateY(-1.0 * rotate_y);
    ofRotateZ(-1.0 * rotate_z);
    for(int i=0;i<scaledVol*100.0/2-1;i++){
        ofSetColor(Col_1);
        ofDrawBox(0+20*i,0+20*i,0+20*i,50,50,50);
        ofDrawBox(0-20*i,0+20*i,0+20*i,50,50,50);
        ofDrawBox(0+20*i,0-20*i,0+20*i,50,50,50);
        ofDrawBox(0+20*i,0+20*i,0-20*i,50,50,50);
        ofDrawBox(0-20*i,0-20*i,0+20*i,50,50,50);
        ofDrawBox(0+20*i,0-20*i,0-20*i,50,50,50);
        ofDrawBox(0-20*i,0+20*i,0-20*i,50,50,50);
        ofDrawBox(0-20*i,0-20*i,0-20*i,50,50,50);
        
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateX(rotate_x);
    ofRotateY(rotate_y);
    ofRotateZ(rotate_z);
    for(int i = 0;i<scaledVol*50-1;i++){
        ofSetColor(Col_3);
        ofDrawBox(0+10*i, 0, 0, box_size);
        ofDrawBox(0, 0+10*i, 0, box_size);
        ofDrawBox(0, 0, 0+10*i, box_size);
        ofDrawBox(0+10*i, 0+10*i, 0, box_size);
        ofDrawBox(0, 0+10*i, 0+10*i, box_size);
        ofDrawBox(0+10*i, 0, 0+10*i, box_size);
        ofDrawBox(0+10*i, 0+10*i, 0+10*i, box_size);
        
        ofDrawBox(0-10*i, 0, 0, box_size);
        ofDrawBox(0, 0-10*i, 0, box_size);
        ofDrawBox(0, 0, 0-10*i, box_size);
        ofDrawBox(0-10*i, 0-10*i, 0, box_size);
        ofDrawBox(0, 0-10*i, 0-10*i, box_size);
        ofDrawBox(0-10*i, 0, 0-10*i, box_size);
        ofDrawBox(0-10*i, 0-10*i, 0-10*i, box_size);
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateX(rotate_x);
    ofRotateY(rotate_y);
    ofRotateZ(rotate_z);
    for(int i = 0;i<scaledVol*50-1;i++){
        ofSetColor(Col_2);
        ofDrawBox(0+100*i,0+100*i,0+100*i,50,50,50);
        ofDrawBox(0-100*i,0+100*i,0+100*i,50,50,50);
        ofDrawBox(0+100*i,0-100*i,0+100*i,50,50,50);
        ofDrawBox(0+100*i,0+100*i,0-100*i,50,50,50);
        ofDrawBox(0-100*i,0-100*i,0+100*i,50,50,50);
        ofDrawBox(0+100*i,0-100*i,0-100*i,50,50,50);
        ofDrawBox(0-100*i,0+100*i,0-100*i,50,50,50);
        ofDrawBox(0-100*i,0-100*i,0-100*i,50,50,50);
    }
    ofPopMatrix();
    
    
    cam.end();
    
    
    
    
    
    //lets draw the volume history as a graph
    drawCounter++;
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]     = input[i*2]*0.5;
        right[i]    = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if( key == 's' ){
        soundStream.start();
    }
    
    if( key == 'e' ){
        soundStream.stop();
    }
//    if(key == 'p'){
//        soundplay.play();
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

