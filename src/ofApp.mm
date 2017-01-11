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
    
    
    // to do: implement real-time fft display along spiral, current add-on doesn't work with iOS
    //bufferSize = 32768;
    
    
    
    //fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    //fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);
    //nBins = fft->getBinSize();
    
    //binWidth = (float) sampleRate / 2 / nBins;
    //binAmps = new float[nBins];

    initialRadius = 1;
    
    audioBuffer = new float*[2];
    audioBuffer[0] = new float[1];
    audioBuffer[1] = new float[1];
    fftHeight = 10;
    
    initialBufferSize = 512;
    
    lAudio = new float[initialBufferSize];
    rAudio = new float[initialBufferSize];
    
    memset(lAudio, 0, initialBufferSize * sizeof(float));
    memset(rAudio, 0, initialBufferSize * sizeof(float));
    
    ofSetFrameRate(60);
    
    appWidth = ofGetWidth();
    appHeight = ofGetHeight();
    audioEngine = controller.theEngine;
    controller.init();
    faustReverb.init(controller.theEngine->sampleRate);
    
    background.load("Background8.png");
    background.setAnchorPercent(0.5, 0.5);
    background.resize(appWidth, appHeight);
    pitchSpace.load("spiralbackground2flip.png");
    pitchSpace.setAnchorPercent(0.5, 0.5);
    pitchSpace.resize((749*controller.padScale), (752*controller.padScale));
    pitchPointer.load("Big Ring In over.png");
    pitchPointer.setAnchorPercent(0.5, 0.5);
    pitchPointer.resize((814*controller.padScale), (814*controller.padScale));
    pitchRing.load("Big Ring.png");
    pitchRing.setAnchorPercent(0.5, 0.5);
    pitchRing.resize((int)(814*controller.padScale),(814*controller.padScale));
    blackKeys.load("blackKeys.png");
    blackKeys.setAnchorPercent(0.5, 0.5);
    blackKeys.resize((749*controller.padScale),(752*controller.padScale));
    noteNames = new ofImage[12];
    noteNames[9].load("Anat.png");
    noteNames[8].load("AflatW.png");
    noteNames[11].load("Bnat.png");
    noteNames[10].load("BflatW.png");
    noteNames[0].load("Cnat.png");
    noteNames[2].load("Dnat.png");
    noteNames[1].load("DflatW.png");
    noteNames[4].load("Enat.png");
    noteNames[3].load("EflatW.png");
    noteNames[5].load("Fnat.png");
    noteNames[7].load("Gnat.png");
    noteNames[6].load("GflatW.png");
    for(int i = 0; i< 12; i++)
        noteNames[i].setAnchorPercent(0.5, 0.5);
    
    ofSoundStreamSetup(2, 0, this, sampleRate, initialBufferSize, 4);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    controller.update();
    if(controller.showFlats != flats) {
        flats = controller.showFlats;
        noteNames[1].clear();
        noteNames[3].clear();
        noteNames[6].clear();
        noteNames[8].clear();
        noteNames[10].clear();
        if(flats) {
            noteNames[1].load("DflatW.png");
            noteNames[3].load("EflatW.png");
            noteNames[6].load("GflatW.png");
            noteNames[8].load("AflatW.png");
            noteNames[10].load("BflatW.png");
        } else {
            noteNames[1].load("CsharpW.png");
            noteNames[3].load("DsharpW.png");
            noteNames[6].load("FsharpW.png");
            noteNames[8].load("GsharpW.png");
            noteNames[10].load("AsharpW.png");
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(appWidth/2, appHeight/2);
    background.draw(0,0);

    ofRotateZ(controller.theEngine->pitchRef*360);
    pitchSpace.draw(0, 0);
    ofPushStyle();
    ofSetColor(0, 0, 0, controller.blackKeysAlpha);
    blackKeys.draw(0,0);
    ofPopStyle();
    
    
        ofPushStyle();
            PolarPoint oldPoint;
            oldPoint.polarFromTheta(0, initialRadius);
            ofSetLineWidth(2.0);
            float zoomColor = (controller.theEngine->zoom + 6)/8;
            ofSetColor((zoomColor-0.75) * 255, (zoomColor-0.75) * 255, (zoomColor-0.75) * 255, controller.spiralAlpha);
            ofPushMatrix();
            ofRotateZ((controller.theEngine->zoom - 1) * 360);
            PolarPoint newPoint;
            int spiralScale;
            if(appWidth == 1024) spiralScale = 535;
            else spiralScale = 565;
            for (int i=1; i < spiralScale; i++) {
                ofSetColor((int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), (int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), (int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), controller.spiralAlpha);
                newPoint.polarFromTheta((float)i/10, initialRadius);
                ofDrawLine(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y);
                oldPoint = newPoint;
            }
    
    /*  fft curve - to add with iOS compatable fft addon
    PolarPoint oldBinPoint;
    oldBinPoint.polarFromTheta(4*myPi, 1);
    ofColor c = ofColor::fromHsb(0, 255, 255);
    ofSetLineWidth(4.);
    int k = 16;
    float thetaMake, newHue;
    for(int j = 1;j<k-1; j++) {
        for (int i=1+(j-1)*(nBins/k); i < (j*nBins/k)+1; i+=pow(2,(j-1))) {
            //      for (int j=0; j < fft->getBinSize();i++) {
            PolarPoint newBinPoint;
            thetaMake = 2*myPi*log2((float)i/10*binWidth) + 4*myPi;
            
            newBinPoint.polarFromTheta(thetaMake, initialRadius);
            newHue = fmodf(449.0+oldBinPoint.theta/(2*myPi)*255, 256.0);
            c.setHue(newHue);
            ofSetColor(c);
            ofDrawLine(oldBinPoint.x+cos(oldBinPoint.theta)*fftHeight*binAmps[i-(int)pow(2,(j-1))], oldBinPoint.y+sin(oldBinPoint.theta)*fftHeight*binAmps[i-(int)pow(2,(j-1))], 5 ,newBinPoint.x+cos(newBinPoint.theta)*fftHeight*binAmps[i], newBinPoint.y+sin(newBinPoint.theta)*fftHeight*binAmps[i], 5);
            oldBinPoint = newBinPoint;
        }
        
    }
     */
    
            ofPopMatrix();
            ofPopStyle();
            ofPushMatrix();
            ofPushStyle();
            if(controller.theEngine->quantizeIsOn)
                ofSetColor(0, 0, 0, controller.gridAlpha);
            else
                ofSetColor(255, 255, 255, controller.gridAlpha);
            ofRotateZ(360.0/(float)controller.theEngine->quantNumber/2);
            for (int i = 0; i < controller.theEngine->quantNumber; i++) {
                ofDrawLine(0,0,0,appHeight/2-20);
                ofRotateZ(360.0/ (float)controller.theEngine->quantNumber);
            }
            ofPopStyle();
            ofPopMatrix();
    
    
        
    pitchRing.draw(0,0);
    pitchPointer.draw(0,0);
    //drawNames
    ofPushStyle();
    ofSetColor(0, 0, 0, controller.namesAlpha);
    for (int i = 0; i < 12; i++) {
        ofPushMatrix();
        ofRotate(30*i);
        ofTranslate(0, appHeight*3/8);
        ofRotate(-30*i-controller.theEngine->pitchRef * 360);
        if (i == 1 || i == 3 || i == 6 || i == 8 || i == 10) {
            ofPushStyle();
            ofSetColor(controller.blackKeysAlpha, controller.blackKeysAlpha, controller.blackKeysAlpha, controller.namesAlpha);
            noteNames[i].draw(0,0);
            ofPopStyle();
        } else
            noteNames[i].draw(0,0);
        ofPopMatrix();
    }
    ofPopStyle();
    ofPopMatrix();
    ofPushMatrix();
    controller.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(appWidth/2, appHeight/2);
    ofRotateZ(controller.theEngine->pitchRef*360);
    pitchRing.draw(0,0);
    pitchPointer.draw(0,0);
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    delete[] audioBuffer[0];
    delete[] audioBuffer[1];
    delete[] audioBuffer;
    delete[] lAudio;
    delete[] rAudio;
    delete[] binAmps;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){

    for(int i = 0; i < bufferSize; i++){
        audioEngine->audioCallback(1, NULL, audioBuffer);
        faustReverb.compute(1,audioBuffer,audioBuffer);
        lAudio[i] = output[i * 2] = audioBuffer[0][0];
        rAudio[i] = output[i * 2 + 1] = audioBuffer[0][0];
    }
    
    if( initialBufferSize < bufferSize ){
        ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
        return;
    }
    
    //  to-do fft audio handling
    //fft->setSignal(&lAudio[0]);
   // float* curFft = fft->getAmplitude();
    //for (int i =0; i < nBins; i++) {
    //    binAmps[i] = fft->getAmplitudeAtBin((float)i)*((float)i+32)/(fft->getBinSize()/32);
       // cout << binAmps[i];
   // }
    
}


//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
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
