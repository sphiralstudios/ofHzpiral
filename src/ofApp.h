
#pragma once

#include "ofxiOS.h"
#include "ofxKCTouchGui.h"
#include "audioEngine.h"
//#include "ofxFft.h"  // fft visualization not yet implemented
#include "FaustReverb.h"
#ifndef pi
#define pi    3.141592653589
#endif

class ofApp : public ofxiOSApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    float pan;
    int sampleRate, bufferSize;
    bool bNoise;
    float volume;
    
    float * lAudio;
    float * rAudio;
    
//    ofxFft * fft;
    int nBins;
    float binWidth, fftHeight;
    float* binAmps;
    
    int initialBufferSize;
    int appWidth, appHeight;
    float initialRadius;
    bool flats;
    
    AudioEngine* audioEngine;
    FaustReverb faustReverb;
    
    float** audioBuffer;
    
    //KCTouchGui
    ofxKCTouchGui::Controller controller;
    
    //images
    ofImage background;
    ofImage pitchSpace;
    ofImage pitchRing;
    ofImage pitchPointer;
    ofImage* noteNames;
    ofImage blackKeys;
    
    
};

