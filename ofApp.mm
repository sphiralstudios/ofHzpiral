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
    bufferSize = 32768;
    
    
    
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    //fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING, OF_FFT_FFTW);
    nBins = fft->getBinSize();
    
    //    cout <<); nBins;
    binWidth = (float) sampleRate / 2 / nBins;
    binAmps = new float[nBins];
//    phase = 0;
//    phase2 = 0;
//    phaseAdder = 0.0f;
//    phaseAdder2 = 0.0f;
//    phaseAdderTarget = 0.0;
//    phaseAdderTarget2 = 0.0;
//    volume = 0.15f;
//    pan = 0.5;
//    bNoise = false;
    initialRadius = 1;
    
  //  voiceCounter = -1;
//    numVoices = 24;
//    noteVoices = new MapUI*[numVoices];
    audioBuffer = new float*[2];
    audioBuffer[0] = new float[1];
    audioBuffer[1] = new float[1];
    fftHeight = 10;
    
    //for some reason on the iphone simulator 256 doesn't work - it comes in as 512!
    //so we do 512 - otherwise we crash
    initialBufferSize = 512;
    
    lAudio = new float[initialBufferSize];
    rAudio = new float[initialBufferSize];
    
    memset(lAudio, 0, initialBufferSize * sizeof(float));
    memset(rAudio, 0, initialBufferSize * sizeof(float));
    
    //we do this because we don't have a mouse move function to work with:
    //targetFrequency = 444.0;
    //phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
    //targetFrequency2 = 444.0;
    //phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
    
    // This call will allow your app's sound to mix with any others that are creating sound
    // in the background (e.g. the Music app). It should be done before the call to
    // ofSoundStreamSetup. It sets a category of "play and record" with the "mix with others"
    // option turned on. There are many other combinations of categories & options that might
    // suit your app's needs better. See Apple's guide on "Configuring Your Audio Session".
    
    // ofxiOSSoundStream::setMixWithOtherApps(true);
    
    
    ofSetFrameRate(60);
    
    appWidth = ofGetWidth();
    appHeight = ofGetHeight();
    audioEngine = controller.theEngine;
    controller.init();
    faustReverb.init(controller.theEngine->sampleRate);
    
    //image init
    //float imgScale = appWidth/1024;
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
//    spiralIn.load("spiralOverlayIn.png");
//    spiralIn.setAnchorPercent(0.5, 0.5);
//    spiralOut.load("spiralOverlayOut.png");
//    spiralOut.setAnchorPercent(0.5, 0.5);
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
    
    
    
  //  controller.sustainOnImage.load("sustainOn.png.");
    ofSoundStreamSetup(2, 0, this, sampleRate, initialBufferSize, 4);
//    faustEngine.init(sampleRate);
    
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
    
//    float boxW = 200.0;
//    float boxH = boxW * 0.75;
//    
//    float topY = 30;
//    float leftX = 30;
//    float rightX = leftX + boxW + 20;
    
    ofPushMatrix();
    ofTranslate(appWidth/2, appHeight/2);
    background.draw(0,0);

    ofRotateZ(controller.theEngine->pitchRef*360);
    pitchSpace.draw(0, 0);
    
    //spiralIn.draw(0,0);
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
           // else if (appWidth == 2732) spiralScale = 585;
            else spiralScale = 565;
            for (int i=1; i < spiralScale; i++) {
                ofSetColor((int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), (int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), (int)((zoomColor-0.75 + (0.75 * i/spiralScale)) * 255), controller.spiralAlpha);
                newPoint.polarFromTheta((float)i/10, initialRadius);
                ofDrawLine(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y);
                oldPoint = newPoint;
            }
    
    /*
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
    
    //drawGrid - to go into separate function
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
    delete[] audioBuffer[0];
    delete[] audioBuffer[1];
    delete[] audioBuffer;
    delete[] lAudio;
    delete[] rAudio;
    delete[] binAmps;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
//    for(int i = 0; i<2; i++){
//        audioBuffer[i] = new FAUSTFLOAT[bufferSize];
//    }
    
    
    
    
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
    
    fft->setSignal(&lAudio[0]);
   // float* curFft = fft->getAmplitude();
    //for (int i =0; i < nBins; i++) {
    //    binAmps[i] = fft->getAmplitudeAtBin((float)i)*((float)i+32)/(fft->getBinSize()/32);
       // cout << binAmps[i];
   // }

    
//    float leftScale = 1 - pan;
//    float rightScale = pan;
//    
//    // sin (n) seems to have trouble when n is very large, so we
//    // keep phase in the range of 0-TWO_PI like this:
//    while(phase > TWO_PI){
//        phase -= TWO_PI;
//    }
//    // keep phase in the range of 0-TWO_PI like this:
//    while(phase2 > TWO_PI){
//        phase2 -= TWO_PI;
//    }
//    
//    if(bNoise == false){
//        // ---------------------- noise --------------
//        for(int i = 0; i < bufferSize; i++){
//            lAudio[i] = output[i * nChannels] = 0;
//            rAudio[i] = output[i * nChannels + 1] = 0;
//        }
//    } else {
//        phaseAdder = 0.05f * phaseAdder + 0.95f * phaseAdderTarget;
//        phaseAdder2 = 0.05f * phaseAdder2 + 0.95f * phaseAdderTarget2;
//        for(int i = 0; i < bufferSize; i++){
//            phase += phaseAdder;
//            phase2 += phaseAdder2;
//            float sample = sin(phase);
//            float sample2 = sin(phase2);
//            lAudio[i] = output[i * nChannels] = (sample * noteGain1 + sample2 * noteGain2) * volume * leftScale;
//            rAudio[i] = output[i * nChannels + 1] = (sample * noteGain1 + sample2 * noteGain2) * volume * rightScale;
//        }
//    }
    
    
}

////newNote returns index of voice in MapUI array noteVoices
//int ofApp::newNote(PolarPoint* touchPoint) {
////    PolarPoint touchPoint;
//    //    if(touch.id ==  0){
//    //        int width = ofGetWidth();
//    //        pan = (float)touch.x / (float)width;
//    //
//    //        int height = ofGetHeight();
// 
////    double xo = touch.x - appWidth/2;
////    double yo = touch.y - appHeight/2;
////    touchPoint.polarFromCartesian(xo, yo)
//    
////    double r = pow((pow(xo,2)+pow(yo,2)),0.5);
////    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
////    double cutoff = r/rmax * 5000;
// //   double theta;
//    double spiral, ratio;
//    
////    if (xo<0 && yo<0) {
////        theta=pi+atan(yo/xo);
////    } else if (xo>0 && yo<0)
////        theta=(2*pi)+atan(yo/xo);
////    else if (xo<0 && yo>0)
////        theta = pi + atan(yo/xo);
////    
////    else {
////        theta=atan(yo/xo);
////        
////    }
//    //
//    //            DBG("X = " << xo);
//    //            DBG("Y = " << yo);
//    //            DBG("Theta = " << theta);
//    double freq1, freq2, gain1, gain2;
//    spiral = (log(touchPoint->radius)/log(2.0));
//    ratio = ((2 * pi * spiral)-touchPoint->theta)/(2* pi);
//    if((ratio-floor(ratio))>=0.5) {
//        freq1 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq2 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//        gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//    } else {
//        freq2 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq1 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//        gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//    }
//    //voiceCounter = controller.getTouches().size()-1;
//    voiceCounter ++;
//    voiceCounter %= 24;
//    noteVoices[voiceCounter] = faustEngine.keyOn(voiceCounter, 100);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq", freq1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq2", freq2);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol1", gain1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol2", gain2);
//    return voiceCounter;
//}
//
//void ofApp::noteMoved(int noteIndex, PolarPoint* touchPoint) {
////    PolarPoint touchPoint;
////    double xo = touch.x - appWidth/2;
////    double yo = touch.y - appHeight/2;
////    touchPoint.polarFromCartesian(xo, yo);
//    
// //   double r = pow((pow(xo,2)+pow(yo,2)),0.5);
////    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
////    double cutoff = r/rmax * 5000;
// //   double theta;
//    double spiral, ratio;
//    
////    if (xo<0 && yo<0) {
////        theta=pi+atan(yo/xo);
////    } else if (xo>0 && yo<0)
////        theta=(2*pi)+atan(yo/xo);
////    else if (xo<0 && yo>0)
////        theta = pi + atan(yo/xo);
////    
////    else {
////        theta=atan(yo/xo);
//    
////    }
//    //
//    //            DBG("X = " << xo);
//    //            DBG("Y = " << yo);
//    //            DBG("Theta = " << theta);
//    double freq1, freq2, gain1, gain2;
//    spiral = (log(touchPoint->radius)/log(2.0));
//    ratio = ((2 * pi * spiral)-touchPoint->theta)/(2* pi);
//    if((ratio-floor(ratio))>=0.5) {
//        freq1 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq2 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//        gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//    } else {
//        freq2 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq1 = pow(2.0, (touchPoint->theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//        gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//    }
//    
//    noteVoices[noteIndex]->setParamValue("/hzpVoice/freq", freq1);
//    noteVoices[noteIndex]->setParamValue("/hzpVoice/freq2", freq2);
//    noteVoices[noteIndex]->setParamValue("/hzpVoice/vol1", gain1);
//    noteVoices[noteIndex]->setParamValue("/hzpVoice/vol2", gain2);
//
//}
//
//
//void ofApp::noteEnded(int noteIndex) {
//    faustEngine.keyOff(noteIndex);
//
//}


//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
 //   controller.touchDown(touch);
//    PolarPoint touchPoint;
////    if(touch.id ==  0){
////        int width = ofGetWidth();
////        pan = (float)touch.x / (float)width;
////        
////        int height = ofGetHeight();
//        double xo = touch.x - appWidth/2;
//        double yo = touch.y - appHeight/2;
//        double r = pow((pow(xo,2)+pow(yo,2)),0.5);
//        double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
//        double cutoff = r/rmax * 5000;
//        double theta;
//        double spiral, ratio;
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
//        //
//        //            DBG("X = " << xo);
//        //            DBG("Y = " << yo);
//        //            DBG("Theta = " << theta);
//        double freq1, freq2, gain1, gain2;
//        spiral = (log(r)/log(2.0));
//        ratio = ((2 * pi * spiral)-theta)/(2* pi);
//        if((ratio-floor(ratio))>=0.5) {
//            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//            gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//            gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//        } else {
//            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//            gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//            gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//        }
//    //voiceCounter = controller.getTouches().size()-1;
//    voiceCounter ++;
//    noteVoices[voiceCounter] = faustEngine.keyOn(voiceCounter, 100);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq", freq1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq2", freq2);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol1", gain1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol2", gain2);
    
//    faustEngine.setVoiceParamValue("Freq1", voiceCounter, freq1);
//    faustEngine.setVoiceParamValue("Freq2", voiceCounter, freq2);
//    faustEngine.setVoiceParamValue("Gain1", voiceCounter, gain1);
//    faustEngine.setVoiceParamValue("Gain2", voiceCounter, gain2);
    
//        targetFrequency = freq1;
//        targetFrequency2 = freq2;
//        phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
//        phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
//        noteGain1 = gain1;
//        noteGain2 = gain2;
    //}

    
 //   bNoise = true;
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
  //  controller.touchMoved(touch);
//    cout << "App Touch Moved";
    if(touch.id ==  0){
//        int width = ofGetWidth();
//        pan = (float)touch.x / (float)width;
//        
//        int height = ofGetHeight();
//        double xo = touch.x - appWidth/2;
//        double yo = touch.y - appHeight/2;
//        double r = pow((pow(xo,2)+pow(yo,2)),0.5);
//        double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
//        double cutoff = r/rmax * 5000;
//        double theta;
//        double spiral, ratio;
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
//        //
//        //            DBG("X = " << xo);
//        //            DBG("Y = " << yo);
//        //            DBG("Theta = " << theta);
//        double freq1, freq2, gain1, gain2;
//        spiral = (log(r)/log(2.0));
//        ratio = ((2 * pi * spiral)-theta)/(2* pi);
//        if((ratio-floor(ratio))>=0.5) {
//            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//                        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//                      gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//        } else {
//            freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
//            freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
//                        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//                      gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//        }
//        
//        noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq", freq1);
//        noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq2", freq2);
//        noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol1", gain1);
//        noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol2", gain2);
        
        
//        targetFrequency = freq1;
//        targetFrequency2 = freq2;
//        phaseAdderTarget = (targetFrequency / (float)sampleRate) * TWO_PI;
//        phaseAdderTarget2 = (targetFrequency2 / (float)sampleRate) * TWO_PI;
//        noteGain1 = gain1;
//        noteGain2 = gain2;
    }
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
//    bNoise = false;
//    faustEngine.keyOff(voiceCounter);
//    voiceCounter --;
//    controller.touchUp(touch);
 //   voiceCounter = controller.getTouches().size();
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
