# ofxBoseCSSP

## Bose Control Space Serial protocol addon

## Usage

### setup

~~~
ofxBoseCSSP boseCSSP;
boseCSSP.setup("192.168.7.56");
~~~
### control

#### recall parameters
~~~
ofxBoseCSSP boseCSSP;
boseCSSP.setup("192.168.7.56");

//recall parameter set 1
boseCSSP.recall(1);
~~~

#### gain control
~~~
ofxBoseCSSP boseCSSP;
boseCSSP.setup("192.168.7.56");

//gain module named "main_gain", set -0.5dB
boseCSSP.setGain("main_gain", GainControl_down);

//gain module named "main_gain", set +2.0dB
boseCSSP.setGain("main_gain", GainControl_up, 2.0);