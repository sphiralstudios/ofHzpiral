//
//  audioEngine.cpp
//  Hzpiral
//
//  Created by Mark Hertensteiner on 11/27/16.
//
//

#include "audioEngine.h"


AudioEngine::AudioEngine(){
    sampleRate = 44100;
    numVoices = 24;
    noteVoices = new MapUI*[numVoices];
    faustEngine.init(sampleRate);
    voiceCounter = -1;
    pitchRef = 0;
    pointerRef = 0;
    zoom = 1;
    quantizeIsOn = false;
    quantNumber = 12;
    gridMode = 1;
    masterVolume = 1;
    tremOn = false;
    attack = 0.1;
    decay = 0.1;
    sustain = 75;
    release = 0.5;
    sinMix = 1;
    sawMix = 0;
    squareMix = 0;
    triMix = 0;
    cutoff = 10000;
    Q = 7;
    tremStr = 0.5;
    tremRate = 6;
}

AudioEngine::~AudioEngine(){
    delete[] noteVoices;
}

//newNote returns index of voice in MapUI array noteVoices
Note* AudioEngine::newNote(PolarPoint touchPoint) {
    //    PolarPoint touchPoint;
    //    if(touch.id ==  0){
    //        int width = ofGetWidth();
    //        pan = (float)touch.x / (float)width;
    //
    //        int height = ofGetHeight();
    
    //    double xo = touch.x - appWidth/2;
    //    double yo = touch.y - appHeight/2;
    //    touchPoint.polarFromCartesian(xo, yo)
    
    //    double r = pow((pow(xo,2)+pow(yo,2)),0.5);
    //    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
    //    double cutoff = r/rmax * 5000;
    //   double theta;
    
    
    //    if (xo<0 && yo<0) {
    //        theta=pi+atan(yo/xo);
    //    } else if (xo>0 && yo<0)
    //        theta=(2*pi)+atan(yo/xo);
    //    else if (xo<0 && yo>0)
    //        theta = pi + atan(yo/xo);
    //
    //    else {
    //        theta=atan(yo/xo);
    //
    //    }
    //
    //            DBG("X = " << xo);
    //            DBG("Y = " << yo);
    //            DBG("Theta = " << theta);
    Note* newNote = new Note;
    newNote->polarLoc = touchPoint;
    makePitchForNote(newNote);
//    double spiral, ratio, qTheta;
//    
//    double freq1, freq2, gain1, gain2;
//    spiral = (log(touchPoint.radius)/log(2.0));
//    ratio = ((2 * myPi * spiral)-touchPoint.theta)/(2* myPi);
//    if((ratio-floor(ratio))>=0.5) {
//        freq1 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq2 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)) + 1);
//        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//        gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//    } else {
//        freq2 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)+1) + 1);
//        freq1 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)) + 1);
//        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//        gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//    }
    //voiceCounter = controller.getTouches().size()-1;
    voiceCounter ++;
    voiceCounter %= numVoices;
    newNote->noteIndex=voiceCounter;
    noteVoices[voiceCounter] = faustEngine.keyOn(voiceCounter, 100);
    sendNoteParams(newNote);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq", newNote->freq1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/freq2", newNote->freq2);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol1", newNote->vol1);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/vol2", newNote->vol2);
    updateMasterVolume(voiceCounter);
//    noteVoices[voiceCounter]->setParamValue("/hzpVoice/gain", masterVolume/2);
    updateAttack(voiceCounter);
    updateDecay(voiceCounter);
    updateSustain(voiceCounter);
    updateRelease(voiceCounter);
    updateCutoff(voiceCounter);
    updateQ(voiceCounter);
    updateTremStr(voiceCounter);
    updateTremRate(voiceCounter);
    updateTremOn(voiceCounter);
    
    
    return newNote;
}

void AudioEngine::noteMoved(Note * note, PolarPoint touchPoint) {
    //    PolarPoint touchPoint;
    //    double xo = touch.x - appWidth/2;
    //    double yo = touch.y - appHeight/2;
    //    touchPoint.polarFromCartesian(xo, yo);
    
    //   double r = pow((pow(xo,2)+pow(yo,2)),0.5);
    //    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
    //    double cutoff = r/rmax * 5000;
    //   double theta;
    
    
    //    if (xo<0 && yo<0) {
    //        theta=pi+atan(yo/xo);
    //    } else if (xo>0 && yo<0)
    //        theta=(2*pi)+atan(yo/xo);
    //    else if (xo<0 && yo>0)
    //        theta = pi + atan(yo/xo);
    //
    //    else {
    //        theta=atan(yo/xo);
    
    //    }
    //
    //            DBG("X = " << xo);
    //            DBG("Y = " << yo);
    //            DBG("Theta = " << theta);
//    double spiral, ratio;
//    double freq1, freq2, gain1, gain2;
//    spiral = (log(touchPoint.radius)/log(2.0));
//    ratio = ((2 * myPi * spiral)-touchPoint.theta)/(2* myPi);
//    if((ratio-floor(ratio))>=0.5) {
//        freq1 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)+1)+1);
//        freq2 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio))+1);
//        gain1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
//        gain2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
//    } else {
//        freq2 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio)+1)+1);
//        freq1 = pow(2.0, ((touchPoint.theta - pitchRef)/(2*myPi)) + 0.55 + (floor(ratio))+1);
//        gain2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
//        gain1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
//    }
    note->polarLoc = touchPoint;
   // makePitchForNote(note);
  //  sendNoteParams(note);
//    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/freq", note->freq1);
//    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/freq2", note->freq2);
//    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/vol1", note->vol1);
//    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/vol2", note->vol2);
    
}

void AudioEngine::sendNoteParams(Note* note) {
    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/freq", note->freq1);
    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/freq2", note->freq2);
    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/vol1", note->vol1);
    noteVoices[note->noteIndex]->setParamValue("/hzpVoice/vol2", note->vol2);
}


void AudioEngine::noteEnded(int noteIndex) {
    
    faustEngine.keyOff(noteIndex);
    
}

void AudioEngine::makePitchForNote(Note* note){
    double spiral, ratio, qTheta;
    
 //   double freq1, freq2, gain1, gain2;
    spiral = (log(note->polarLoc.radius)/log(2.0));
    
    if (quantizeIsOn)
        qTheta=quantize(note->polarLoc.theta);
    else {
        qTheta = note->polarLoc.theta;
        //    if (!noteSettings.gridTurn || (!noteSettings.quantizeIsOn && noteSettings.gridTurn))
        qTheta -= (pitchRef * 2 * myPi);
    }

    
    ratio = ((2 * myPi * spiral)-qTheta)/(2* myPi) + zoom;
    if((ratio-floor(ratio))>=0.5) {
        note->freq1 = pow(2.0, (qTheta/(2*myPi)) + 0.55 + (floor(ratio)+1) + 1);
        note->freq2 = pow(2.0, (qTheta/(2*myPi)) + 0.55 + (floor(ratio)) + 1);
        note->vol1 = (ratio - floor(ratio)) /* * gainSlider.getValue()*/;
        note->vol2 = (1 - (ratio-floor(ratio))) /* * gainSlider.getValue()*/;
    } else {
        note->freq2 = pow(2.0, (qTheta/(2*myPi)) + 0.55 + (floor(ratio)+1) + 1);
        note->freq1 = pow(2.0, (qTheta/(2*myPi)) + 0.55 + (floor(ratio)) + 1);
        note->vol2 = (ratio - floor(ratio))/* * gainSlider.getValue()*/;
        note->vol1 = (1 - (ratio-floor(ratio)))/* * gainSlider.getValue()*/;
    }
    
}


float AudioEngine::quantize (float theta) {
    //	if(quantizeType == quantizeTypeEven)
    //    NSArray * tempTune = [NSArray arrayWithArray:[wheelGrid getTuning]];
    //theta += myPi/2;
    
    if (gridMode == 1) {
        theta = evenQuantize(theta);
        return theta;
    }
    
    int i = 0;
    double qtheta;
    //    if (theta > 1.0)
    //        theta -=1.0;
    //    for (int i=0; i < [wheelGrid.tuning count]; i++) {
    
    //    float tref;
    // //   if (noteSettings.gridTurn)
    //        tref = noteSettings.pitchRef*360-180;
    //   tref = 180;
 
    //   theta -= (noteSettings.pointerRef * 2 * myPi);
    
    while (theta < 0) theta += (2 * myPi);
    while (theta > (2*myPi)) theta -= (2*myPi);
            
//        while (i < [wheelGrid.tuning count]) {
//            
//            if (theta < (([[wheelGrid.tuning objectAtIndex:i] getRangeEndTheta]) * pi /180)) {
//                //            if (i == 0 || i == [wheelGrid.tuning count]-1 || theta > ([[wheelGrid.tuning objectAtIndex:i-1] getRangeEndTheta] * pi/180))
//                qtheta = [[wheelGrid.tuning objectAtIndex:i] getThetaSound] + ((noteSettings.pointerRef) * 360);
//                //            if (noteSettings.gridTurn)
//                //               qtheta += noteSettings.pitchRef * 360;
//                
//                qtheta += 90;
//                qtheta *= -pi/180;
//                qtheta += noteSettings.pitchRef * 2 * myPi;
//                while(qtheta > (2*myPi)) qtheta -= (2*myPi);
//                    while(qtheta < 0.0) qtheta += (2*myPi);
//                        return qtheta;
//                
//                
//                //            if (theta > ([[wheelGrid.tuning objectAtIndex:i+1] getRangeEndTheta] * pi/180))
//                //                return [[wheelGrid.tuning objectAtIndex:i] getThetaSound] * pi/180;
//            }
//            i ++;
//        }
 //   qtheta = [[wheelGrid.tuning objectAtIndex:0] getThetaSound] + ((noteSettings.pointerRef) * 360);
    //    if (noteSettings.gridTurn)
 //   qtheta += pitchRef * 360;
    qtheta += 90;
    qtheta *= -myPi/180;
    qtheta -= pitchRef * 2 * myPi;
    while(qtheta > (2*myPi)) qtheta -= (2*myPi);
    while(qtheta < 0) qtheta += (2*myPi);
        return qtheta;
    //    return
    
    
    
}

float AudioEngine::evenQuantize(float theta) {
    int q = quantNumber;
    double qTheta;
    //    int i;
    double tdisp;
    //    theta += noteSettings.pointerRef * 2*pi;
    //    if(noteSettings.gridTurn)
    //    tdisp = ((noteSettings.pointerRef * q));
    //    else tdisp = 0;
    //    theta += noteSettings.pitchRef * 2 * pi;
    //    double temp = noteSettings.pointerRef - noteSettings.pitchRef;
    //    while (temp < 0.0) temp += 1.0;
    //    while (temp > 1.0) temp -= 0.0;
    //    temp = temp * q - floor(temp *  q);
    //    tdisp = (noteSettings.pointerRef * q - floor(noteSettings.pointerRef * q));
    //   theta += tdisp;
 
    //   theta -= noteSettings.pointerRef * 2 * pi;
 //   theta += myPi/2;
    //theta = -(theta + (myPi/2));
    while (theta < 0) theta += (2 * myPi);
    while (theta >= (2*myPi)) theta -= (2*myPi);
    
    qTheta = ((floor((((theta/(2*myPi) - pitchRef))* q)+ 0.5))) / q * (2*myPi);
    
    //    qTheta -= pi / q;
    //    qTheta -= (floor(noteSettings.pointerRef * q));
    //    qTheta -= tdisp * 2 * pi / q;
//    qTheta += pointerRef * 2 * myPi;
    //qTheta = -(qTheta + (myPi/2));
//    qTheta -= pitchRef * 2 * myPi;
    //qTheta = -(qTheta - (myPi/2));
//    theta -= myPi/2;
    while(qTheta >= (2*myPi)) qTheta -= (2*myPi);
    while(qTheta < 0.0) qTheta += (2*myPi);
            
        return qTheta;
    
}

void AudioEngine::updateMasterVolume(int noteIndex) {
  //  for(int i = 0; i < numVoices; i++)
    noteVoices[noteIndex]->setParamValue("/hzpVoice/gain", masterVolume/2);
}

void AudioEngine::updateAttack(int noteIndex){
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/att", attack);
}

void AudioEngine::updateDecay(int noteIndex){
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/dec", decay);
}

void AudioEngine::updateSustain(int noteIndex){
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/sus", sustain);
}

void AudioEngine::updateRelease(int noteIndex){
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/rel", release);
}

void AudioEngine::updateSinMix(int noteIndex){
  //  for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/sineMix", sinMix);
}

void AudioEngine::updateSawMix(int noteIndex) {
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/sawMix", sawMix);
}

void AudioEngine::updateSquareMix(int noteIndex) {
  //  for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/squareMix", squareMix);
}

void AudioEngine::updateTriMix(int noteIndex) {
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/triMix", triMix);
}

void AudioEngine::updateCutoff(int noteIndex) {
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/cutoff", cutoff);
}

void AudioEngine::updateQ(int noteIndex) {
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/Q", Q);
}

void AudioEngine::updateTremStr(int noteIndex) {
//    for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/tremstr", tremStr);
}

void AudioEngine::updateTremRate(int noteIndex) {
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/tremrate", tremRate);
}

void AudioEngine::updateTremOn(int noteIndex) {
    int tremInt;
    if(tremOn) tremInt = 1;
    else tremInt = 0;
 //   for(int i = 0; i < numVoices; i++)
        noteVoices[noteIndex]->setParamValue("/hzpVoice/tremOn", tremInt);

}


void AudioEngine::audioCallback(int count, float** inputs, float** outputs){
    faustEngine.computeAudio(count, inputs, outputs);
//    cout << outputs[0][0];
}

//int AudioEngine::getAppWidth(void) {
//    return appWidth;
//}
//
//int AudioEngine::getAppHeight(void) {
//    return appHeight;
//}
