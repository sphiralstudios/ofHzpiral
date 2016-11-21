#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // IMPORTANT!!! if your sound doesn't work in the simulator - read this post - which requires you set the output stream to 24bit
    //	http://www.cocos2d-iphone.org/forum/topic/4159
    
    ofSetOrientation(OF_ORIENTATION_90_RIGHT);//Set iOS to Orientation Landscape Right
    
    ofBackground(255, 255, 255);
    
    // 2 output channels,
    // 0 input channels
    // 44100 samples per second
    // 512 samples per buffer
    // 4 num buffers (latency)
    
    sampleRate = 44100;
    phase = 0;
    phase2 = 0;
    phaseAdder = 0.0f;
    phaseAdder2 = 0.0f;
    phaseAdderTarget = 0.0;
    phaseAdderTarget2 = 0.0;
    volume = 0.15f;
    pan = 0.5;
    bNoise = false;
    initialRadius = 1;
    
    //for some reason on the iphone simulator 256 doesn't work - it comes in as 512!
    //so we do 512 - otherwise we crash
    initialBufferSize = 512;
    
    lAudio = new float[initialBufferSize];
    rAudio = new float[initialBufferSize];
    
    memset(lAudio, 0, initialBufferSize * sizeof(float));
    memset(rAudio, 0, initialBufferSize * sizeof(float));
    
    //we do this because we don't have a mouse move function to work with:
    targetFrequency = 444.0;
    phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
    targetFrequency2 = 444.0;
    phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
    
    // This call will allow your app's sound to mix with any others that are creating sound
    // in the background (e.g. the Music app). It should be done before the call to
    // ofSoundStreamSetup. It sets a category of "play and record" with the "mix with others"
    // option turned on. There are many other combinations of categories & options that might
    // suit your app's needs better. See Apple's guide on "Configuring Your Audio Session".
    
    // ofxiOSSoundStream::setMixWithOtherApps(true);
    
    ofSoundStreamSetup(2, 0, this, sampleRate, initialBufferSize, 4);
    ofSetFrameRate(60);
    
    appWidth = ofGetWidth();
    appHeight = ofGetHeight();
    
    //image init
    background.load("HzpiralBackground7.png");
    pitchSpace.load("spiralbackground2flip.png");
    pitchSpace.setAnchorPercent(0.5, 0.5);
    pitchPointer.load("Big Ring In over.png");
    pitchPointer.setAnchorPercent(0.5, 0.5);
    pitchRing.load("Big Ring.png");
    pitchRing.setAnchorPercent(0.5, 0.5);
    spiralIn.load("spiralOverlayIn.png");
    spiralIn.setAnchorPercent(0.5, 0.5);
    spiralOut.load("spiralOverlayOut.png");
    spiralOut.setAnchorPercent(0.5, 0.5);
    blackKeys.load("blackKeys.png");
    blackKeys.setAnchorPercent(0.5, 0.5);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float boxW = 200.0;
    float boxH = boxW * 0.75;
    
    float topY = 30;
    float leftX = 30;
    float rightX = leftX + boxW + 20;
    
    background.draw(0,0);
    ofPushMatrix();
    ofTranslate(appWidth/2, appHeight/2);
    pitchSpace.draw(0, 0);
    
    //spiralIn.draw(0,0);
    blackKeys.draw(0,0);
    
    
        ofPushStyle();
            PolarPoint oldPoint;
            oldPoint.polarFromTheta(0, initialRadius);
            ofSetLineWidth(2.0);
            ofSetColor(0, 0, 0);
            for (int i=1; i < 535; i++) {
                PolarPoint newPoint;
                newPoint.polarFromTheta((float)i/10, initialRadius);
                ofDrawLine(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y);
                oldPoint = newPoint;
            }
    
    
    //drawGrid - to go into separate function
            ofPushMatrix();
            ofRotateZ(15);
            for (int i = 0; i < 12; i++) {
                ofDrawLine(0,0,0,appHeight/2-20);
                ofRotateZ(30);
            }
            ofPopMatrix();
    
    
        ofPopStyle();
    pitchRing.draw(0,0);
    pitchPointer.draw(0,0);
    ofPopMatrix();
    
    
    // draw the left:
//    ofSetHexColor(0x333333);
//    ofDrawRectangle(leftX, topY, boxW, boxH);
//    ofSetHexColor(0xFFFFFF);
//    for(int i = 0; i < initialBufferSize; i++){
//        float x = ofMap(i, 0, initialBufferSize, 0, boxW, true);
//        ofDrawLine(leftX + x,topY + boxH / 2,leftX + x, topY + boxH / 2 + lAudio[i] * boxH * 0.5);
//    }
//    
//    // draw the right:
//    ofSetHexColor(0x333333);
//    ofDrawRectangle(rightX, topY, boxW, boxH);
//    ofSetHexColor(0xFFFFFF);
//    for(int i = 0; i < initialBufferSize; i++){
//        float x = ofMap(i, 0, initialBufferSize, 0, boxW, true);
//        ofDrawLine(rightX + x, topY + boxH / 2, rightX + x, topY + boxH / 2 + rAudio[i] * boxH * 0.5);
//    }
//    
//    ofSetHexColor(0x333333);
//    stringstream reportString;
//    reportString << "volume: (" << volume << ") \npan: (" << pan << ")\nsynthesis: " << ( bNoise ? "noise" : "sine wave" );
//    reportString << " (" << targetFrequency << "hz)\n";
//    ofDrawBitmapString(reportString.str(), leftX, topY + boxH + 20);
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    if( initialBufferSize < bufferSize ){
        ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
        return;
    }
    
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    // sin (n) seems to have trouble when n is very large, so we
    // keep phase in the range of 0-TWO_PI like this:
    while(phase > TWO_PI){
        phase -= TWO_PI;
    }
    // keep phase in the range of 0-TWO_PI like this:
    while(phase2 > TWO_PI){
        phase2 -= TWO_PI;
    }
    
    if(bNoise == false){
        // ---------------------- noise --------------
        for(int i = 0; i < bufferSize; i++){
            lAudio[i] = output[i * nChannels] = 0;
            rAudio[i] = output[i * nChannels + 1] = 0;
        }
    } else {
        phaseAdder = 0.05f * phaseAdder + 0.95f * phaseAdderTarget;
        phaseAdder2 = 0.05f * phaseAdder2 + 0.95f * phaseAdderTarget2;
        for(int i = 0; i < bufferSize; i++){
            phase += phaseAdder;
            phase2 += phaseAdder2;
            float sample = sin(phase);
            float sample2 = sin(phase2);
            lAudio[i] = output[i * nChannels] = (sample * noteGain1 + sample2 * noteGain2) * volume * leftScale;
            rAudio[i] = output[i * nChannels + 1] = (sample * noteGain1 + sample2 * noteGain2) * volume * rightScale;
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    controller.touchDown(touch);
    PolarPoint touchPoint;
    if(touch.id ==  0){
        int width = ofGetWidth();
        pan = (float)touch.x / (float)width;
        
        int height = ofGetHeight();
        double xo = touch.x - width/2;
        double yo = touch.y - height/2;
        double r = pow((pow(xo,2)+pow(yo,2)),0.5);
        double rmax = pow((pow(width/2,2) + pow(height/2,2)),0.5);
        double cutoff = r/rmax * 5000;
        double theta;
        double spiral, ratio;
        
        if (xo<0 && yo<0) {
            theta=pi+atan(yo/xo);
        } else if (xo>0 && yo<0)
            theta=(2*pi)+atan(yo/xo);
        else if (xo<0 && yo>0)
            theta = pi + atan(yo/xo);
        
        else {
            theta=atan(yo/xo);
            
        }
        //
        //            DBG("X = " << xo);
        //            DBG("Y = " << yo);
        //            DBG("Theta = " << theta);
        double freq1, freq2, gain1, gain2;
        spiral = (log(r)/log(2.0));
        ratio = ((2 * pi * spiral)-theta)/(2* pi);
        if((ratio-floor(ratio))>=0.5) {
            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
            gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
            gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
        } else {
            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
            gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
            gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
        }
        
        
        targetFrequency = freq1;
        targetFrequency2 = freq2;
        phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
        phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
        noteGain1 = gain1;
        noteGain2 = gain2;
    }

    
    bNoise = true;
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    if(touch.id ==  0){
        int width = ofGetWidth();
        pan = (float)touch.x / (float)width;
        
        int height = ofGetHeight();
        double xo = touch.x - width/2;
        double yo = touch.y - height/2;
        double r = pow((pow(xo,2)+pow(yo,2)),0.5);
        double rmax = pow((pow(width/2,2) + pow(height/2,2)),0.5);
        double cutoff = r/rmax * 5000;
        double theta;
        double spiral, ratio;
        
        if (xo<0 && yo<0) {
            theta=pi+atan(yo/xo);
        } else if (xo>0 && yo<0)
            theta=(2*pi)+atan(yo/xo);
        else if (xo<0 && yo>0)
            theta = pi + atan(yo/xo);
        
        else {
            theta=atan(yo/xo);
            
        }
        //
        //            DBG("X = " << xo);
        //            DBG("Y = " << yo);
        //            DBG("Theta = " << theta);
        double freq1, freq2, gain1, gain2;
        spiral = (log(r)/log(2.0));
        ratio = ((2 * pi * spiral)-theta)/(2* pi);
        if((ratio-floor(ratio))>=0.5) {
            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
                        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
                      gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
        } else {
            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
                        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
                      gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
        }
        
        
        targetFrequency = freq1;
        targetFrequency2 = freq2;
        phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
        phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
        noteGain1 = gain1;
        noteGain2 = gain2;
    }
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    bNoise = false;
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    bNoise = false;
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
    
}
