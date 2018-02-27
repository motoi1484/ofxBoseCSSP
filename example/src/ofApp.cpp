#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60.0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    boseCSSP.setup("192.168.7.56");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        //recall paramset 1
        boseCSSP.recall(1);
    }
    if(key == '2'){
        //recall paramset 1
        boseCSSP.recall(2);
    }
    if(key == '3'){
        //recall paramset 1
        boseCSSP.recall(3);
    }
    if(key == '4'){
        //recall paramset 1
        boseCSSP.recall(4);
    }
    
    if(key == OF_KEY_UP){
        //gain up (default 0.5db) of "Cneter PC" gain module
        boseCSSP.setGain("Center PC", GainControl_up);
    }
    if(key == OF_KEY_DOWN){
        //gain down (default 0.5db) of "Cneter PC" gain module
        boseCSSP.setGain("Center PC", GainControl_down);
    }
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
