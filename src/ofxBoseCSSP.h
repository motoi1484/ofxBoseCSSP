//
//  ofxBoseCSSP.h
//  bose_test
//
//  Created by Motoi Ishibashi on 2018/02/27.
//
//

#ifndef ofxBoseCSSP_h
#define ofxBoseCSSP_h

#include "ofMain.h"
#include "ofxNetwork.h"

enum boseCSSP_gainDir
{
    GainControl_up = 1,
    GainControl_down
};

class ofxBoseCSSP
{
public:
    ofxBoseCSSP();
    ~ofxBoseCSSP();
    
    bool setup(string host, int port=10055);
    
    void recall(unsigned char presetIndex = 0);
    
    void setGain(string moduleName, int dir, float step=0.5);
    
private:
    ofxTCPClient tcpClient;
    string msgTx, msgRx;
    string _host;
    int _port;
    
    void sendAndGetResponse(string tx, string &rx);
    void sendCommand(string cmd);
    
};

#endif /* ofxBoseCSSP_h */
