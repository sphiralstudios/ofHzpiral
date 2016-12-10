//#pragma once
//
//#include "ofxiOS.h"
//#include "audio.h"
//
//#include "ofConstants.h"
//#include "ofBaseTypes.h"
//#include "ofBaseApp.h"
//#include "ofTypes.h"
//#include "ofBaseSoundStream.h"
////#include "ofSoundStream.h"
//#include <climits>
//
//#ifdef OF_SOUNDSTREAM_RTAUDIO
//#include "ofRtAudioSoundStream.h"
//#define OF_SOUND_STREAM_TYPE ofRtAudioSoundStream
//#elif defined(OF_SOUNDSTREAM_ANDROID)
//#include "ofxAndroidSoundStream.h"
//#define OF_SOUND_STREAM_TYPE ofxAndroidSoundStream
//#elif defined(OF_SOUNDSTREAM_IOS)
//#include "ofxiOSSoundStream.h"
//#define OF_SOUND_STREAM_TYPE ofxiOSSoundStream
//#elif defined(OF_SOUNDSTREAM_EMSCRIPTEN)
//#include "ofxEmscriptenSoundStream.h"
//#define OF_SOUND_STREAM_TYPE ofxEmscriptenSoundStream
//#endif
//
//
//class ofAudio : public audio {
//    public:
//        void init();
//        void compute();
//    
//    
//};
//
//
#pragma once

#include "ofxiOS.h"
#include "ofxKCTouchGui.h"
#include "audioEngine.h"
#include "ofxFft.h"
#include "FaustReverb.h"
//#include "faust-poly-engine.h"
#ifndef pi
#define pi    3.141592653589
#endif



//struct PolarPoint : public ofPoint {
//    double radius;
//    double theta;
//    
//    PolarPoint () {}
//    ~PolarPoint () {}
//    
//    void polarFromCartesian(double xo, double yo) {
////        xo = xo - ofApp::getAppWidth()/2;
////        yo = yo - ofApp::getAppHeight()/2;
//        radius = pow((pow(xo,2)+pow(yo,2)),0.5);
//        //    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
//        //    double cutoff = r/rmax * 5000;
//        
//        if (xo<0 && yo<0) {
//            theta=pi+atan(yo/xo);
//        } else if (xo>0 && yo<0)
//            theta=(2*pi)+atan(yo/xo);
//        else if (xo<0 && yo>0)
//            theta = pi + atan(yo/xo);
//        
//        else {
//            theta=atan(yo/xo);
//            
//        }
//
//    }
//    
//    
//    void polarFromTheta (float thetaMake, float initialRadius) {
//        radius = initialRadius * pow(2,thetaMake/(2*pi));
//        theta = thetaMake;
//        while (theta > (2*pi)) theta -= (2*pi);
//        while (theta < 0) theta += (2*pi);
//        x = radius * cos(fmod(theta, (2 * pi)));
//        y = radius * sin(fmod(theta, (2 * pi)));
//        //    point.y = point.y - 768;
//        //   float tempTheta = -theta - 90;
//        
//        
//        if ((theta < (pi/2) &&  theta > (-pi/2)) || (theta > (3 * pi / 2) && theta < (5 * pi / 2)))
//            
//            //        (fmod(theta, (2 * pi)) < 0.25 || fmod(theta, (2 * pi)) > 0.75)
//            x = fabs(x);
//        else
//            x =  - fabs(x);
//        
//        //    NSLog(@"Theta = %e", theta);
//        if ((theta > 0.0 && theta <= pi) || (theta <= -pi && theta > (-2 * pi)) || (theta > (2*pi) && theta <= (3*pi)))
//            //(fmod(theta, (2 * pi)) < 0.5)
//            
//            y = fabs(y);
//        else
//            y = - fabs(y);
//        //       y = -y;
//        z = 0;
//    }
//    
//};



class ofApp : public ofxiOSApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void audioOut(float * output, int bufferSize, int nChannels);
    
//    int newNote(PolarPoint* touchPoint);
//    void noteMoved(int noteIndex, PolarPoint* touchPoint);
//    void noteEnded(int noteIndex);
    
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
    
//    int voiceCounter;
    
    //const float pi = 3.14159;
    
    float * lAudio;
    float * rAudio;
    
    ofxFft * fft;
    int nBins;
    float binWidth, fftHeight;
    float* binAmps;
    
    //------------------- for the simple sine wave synthesis
    float targetFrequency, targetFrequency2;
    float phase, phase2;
    float noteGain1, noteGain2;
    float phaseAdder, phaseAdder2;
    float phaseAdderTarget, phaseAdderTarget2;
    int initialBufferSize;
    int appWidth, appHeight;
    float initialRadius;
    bool flats;
    
    AudioEngine* audioEngine;
    FaustReverb faustReverb;
    
//    //faust
//    FaustPolyEngine faustEngine;
//    MapUI** noteVoices;
//    int numVoices;
    float** audioBuffer;
    
    //KCTouchGui
    ofxKCTouchGui::Controller controller;
    
    //images
    ofImage background;
    ofImage pitchSpace;
    ofImage pitchRing;
    ofImage pitchPointer;
    ofImage* noteNames;
    //ofImage A, Ab, B, Bb, C, D, Db, E, Eb, F, G, Gb;
//    ofImage spiralOverlay;
//    ofImage spiralIn;
//    ofImage spiralOut;
    ofImage blackKeys;
    
    
};

