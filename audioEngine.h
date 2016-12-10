//
//  audioEngine.hpp
//  Hzpiral
//
//  Created by Mark Hertensteiner on 11/27/16.
//
//

#ifndef audioEngine_h
#define audioEngine_h

//#include <stdio.h>
#include "faust-poly-engine.h"
#include "polarPoint.h"
#include "Touch.h"
#include "ofUtils.h"
//#ifndef pi
//#define pi    3.141592653589
//#endif


struct Note {
public:
    PolarPoint polarLoc;
    ofxKCTouchGui::Touch* noteTouch;
    int touchID;
    int noteIndex;
    float freq1;
    float freq2;
    float vol1;
    float vol2;
    float bornTime;
    Note() {
        bornTime = ofGetElapsedTimeMillis();
    }
    ~Note() {}
    float getAge() {
        return (float) (ofGetElapsedTimeMillis() - bornTime) / 1000.0f;
    }
    
};

struct Chord {
public:
  //  PolarPoint noteZeroLoc;
    vector<PolarPoint> intervals;
};

//struct PolarPoint : public ofPoint {
//    double radius;
//    double theta;
//    
//    PolarPoint () {}
//    ~PolarPoint () {}
//    
//    void polarFromCartesian(double xo, double yo) {
//        //        xo = xo - ofApp::getAppWidth()/2;
//        //        yo = yo - ofApp::getAppHeight()/2;
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

class AudioEngine {

public:
    
    AudioEngine();
    ~AudioEngine();
    Note* newNote(PolarPoint touchPoint);
    void noteMoved(Note *, PolarPoint touchPoint);
    void noteEnded(int noteIndex);
    void audioCallback(int count, float** inputs, float** outputs);
    
    void makePitchForNote(Note * note);
    void sendNoteParams(Note * note);
    void updateMasterVolume(int noteIndex);
    void updateAttack(int noteIndex);
    void updateDecay(int noteIndex);
    void updateSustain(int noteIndex);
    void updateRelease(int noteIndex);
    void updateSinMix(int noteIndex);
    void updateSawMix(int noteIndex);
    void updateSquareMix(int noteIndex);
    void updateTriMix(int noteIndex);
    void updateCutoff(int noteIndex);
    void updateQ(int noteIndex);
    void updateTremStr(int noteIndex);
    void updateTremRate(int noteIndex);
    void updateTremOn(int noteIndex);
    float quantize(float theta);
    float evenQuantize(float theta);
  //  int getAppHeight(void);
   // int getAppWidth(void);

  //  int appHeight, appWidth;

    //faust
    FaustPolyEngine faustEngine;
    MapUI** noteVoices;
    int numVoices;
    int sampleRate;
    int voiceCounter;
    int gridMode;
    int quantNumber;
    float masterVolume, attack, decay, sustain, release, sinMix, sawMix, squareMix, triMix, cutoff, Q, tremStr, tremRate;
    float pitchRef, pointerRef;
    double zoom;
    bool quantizeIsOn, tremOn;
 //   FAUSTFLOAT** audioBuffer;
    
};


#endif /* audioEngine_h */
