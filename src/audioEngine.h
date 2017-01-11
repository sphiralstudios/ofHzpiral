//
//  audioEngine.hpp
//  Hzpiral
//
//  Created by Mark Hertensteiner on 11/27/16.
//
//

#ifndef audioEngine_h
#define audioEngine_h

#include "faust-poly-engine.h"
#include "polarPoint.h"
#include "Touch.h"
#include "ofUtils.h"


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
    vector<PolarPoint> intervals;
};

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
    
};


#endif /* audioEngine_h */
