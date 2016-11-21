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
    int sampleRate;
    bool bNoise;
    float volume;
    
    const float pi = 3.14159;
    
    float * lAudio;
    float * rAudio;
    
    //------------------- for the simple sine wave synthesis
    float targetFrequency;
    float phase;
    float phaseAdder;
    float phaseAdderTarget;
    int initialBufferSize;
    
};

