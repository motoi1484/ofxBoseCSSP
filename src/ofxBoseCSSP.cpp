//
//  ofxBoseCSSP.cpp
//  bose_test
//
//  Created by Motoi Ishibashi on 2018/02/27.
//
//

#include "ofxBoseCSSP.h"

ofxBoseCSSP::ofxBoseCSSP()
{
    
}

ofxBoseCSSP::~ofxBoseCSSP()
{
    tcpClient.close();
}

bool ofxBoseCSSP::setup(string host, int port)
{
    if(host == "") return false;
    
    _host = host;
    _port = port;
    
    tcpClient.setup(_host, _port);
    tcpClient.setMessageDelimiter("\r");
    
    if(tcpClient.isConnected()){
        ofLogVerbose() << "ofxBoseCSSP : Success to connect to " << _host;
        return true;
    }
    else{
        ofLogVerbose() << "ofxBoseCSSP : Failed to connect to " << _host;
        return false;
    }
    
    return true;
}




void ofxBoseCSSP::setGain(string moduleName, int dir, float step)
{
    float currentGain = 0.0;
    float newGain = 0.0;
    string _modName;
    vector<string> ss;
    
    if(moduleName == "") return;
    
    //query current gain level
    _modName = "\"" + moduleName + "\"";
    msgTx = "GA" + _modName + ">1\r";
    
    this->sendAndGetResponse(msgTx, msgRx);
    
    
    //get current gain level
    if(msgRx != ""){
        ss = ofSplitString(msgRx, ">");
        if(ss.size() >= 2){
            sscanf(ss[1].c_str(), "1=%f", &currentGain);
        
            if(dir == GainControl_up) newGain = currentGain + step;
            else newGain = currentGain - step;
        
            //set new gain
            msgTx = "SA" + _modName + ">1=" + ofToString(newGain) + "\r";
            this->sendCommand(msgTx);
        }
    }
    else{
        ofLogError() << "ofxBoseCSSP : Failed to get current gain of " << moduleName;
    }

    
}

void ofxBoseCSSP::recall(unsigned char presetIndex)
{
    unsigned char index = presetIndex;
    
    msgTx = "SS " + ofToHex(presetIndex) + "\r";
    this->sendCommand(msgTx);
    
    msgTx = "GS\r";
    this->sendAndGetResponse(msgTx, msgRx);
    
    //query call preset
    int queryIndex = -1;
    sscanf(msgRx.c_str(), "S %X\r", &queryIndex);
    
    if(queryIndex != presetIndex){
        ofLogError() << "ofxBoseCSSP : Failed to call preset";
    }
    else{
        ofLogVerbose() << "ofxBoseCSSP : Success to change preset to " << queryIndex;
    }
    
}

void ofxBoseCSSP::sendAndGetResponse(string tx, string& rx)
{
    sendCommand(tx);
    
    unsigned long s = ofGetElapsedTimeMillis();
    rx = "";
    while(ofGetElapsedTimeMillis() - s < 1000){
        if(tcpClient.isConnected()){
            rx = tcpClient.receive();
            if(rx != "") break;
        }
        else{
            rx = "";
            break;
        }
    }
    if(rx != ""){
        auto pos = rx.find("\x06");
        if(pos != string::npos){
            rx.replace(pos, 1, "");
        }
        ofLogVerbose() << "ofxBoseCSSP : <-- " << rx;
    }
}


void ofxBoseCSSP::sendCommand(string cmd)
{
    if(tcpClient.isConnected()){
        ofLogVerbose() << "ofxBoseCSSP : --> " << cmd;
        tcpClient.sendRaw(cmd);
    }
    else{
        ofLogVerbose() << "ofxBoseCSSP : reconnect to host " << _host;
        tcpClient.setup(_host, _port);
        if(tcpClient.isConnected()){
            ofLogVerbose() << "ofxBoseCSSP : Success to reconnect";
            ofLogVerbose() << "--> " << cmd;
            tcpClient.sendRaw(cmd);
        }
        else{
            ofLogError() << "ofxBoseCSSP : Failed to reconnect";
        }
    }
}
