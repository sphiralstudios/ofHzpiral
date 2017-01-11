#include "Controller.h"
#include "ofxAssets.h"
#include "ofAppRunner.h"


namespace ofxKCTouchGui {
	//----------
	Controller * Controller::singleton = 0;
	
	//----------
	Controller & Controller::X() {
		return * Controller::singleton;
	}
	
	//----------
	Controller::Controller() {
		this->zoom = 1.0f;
		this->brokenRotation = false;
		Controller::singleton = this;
        theEngine = new AudioEngine;
        this->wheelTheta = 0;
        bokehs = new Bokeh[24];
        chords = new vector<PolarPoint>[4];
        
	}
    
    Controller::~Controller() {
        delete[] bokehs;
        delete[] chords;
        delete theEngine;
    }
	
	//----------
	void Controller::init() {
        padScale = (float) getWidth()/1024;
        for (int i = 0; i<24; i++)
            bokehs[i].setup();
        sustainOnImage.load("sustainOn.png");
        sustainOnImage.setAnchorPercent(0.5, 0.5);
        sustainOnImage.resize(getWidth(), getHeight());
        sustainLockImage.load("sustainLock.png");
        sustainLockImage.setAnchorPercent(0.5, 0.5);
        sustainLockImage.resize(getWidth(), getHeight());
        sostOnImage.load("sostenutoOn.png");
        sostOnImage.setAnchorPercent(0.5, 0.5);
        sostOnImage.resize(getWidth(), getHeight());
        sostLockImage.load("sostLock.png");
        sostLockImage.setAnchorPercent(0.5, 0.5);
        sostLockImage.resize(getWidth(), getHeight());
        setChordImage.load("SetChordOn.png");
        setChordImage.setAnchorPercent(0.5, 0.5);
        setChordImage.resize(getWidth(),getHeight());
        chordOn.load("chord1Shade.png");
        chordOn.setAnchorPercent(0.5, 0.5);
        chordOn.resize(getWidth(), getHeight());
        sustainIsOn = false;
        sustainLock = false;
        sostenutoOn = false;
        sostenutoLock = false;
        chord1 = false;
        chord2 = false;
        chord3 = false;
        chord4 = false;
        setChord = false;
        showFlats = true;
        showNames = true;
        blackKeysAlpha = 255;
        gridAlpha = 255;
        spiralAlpha = 255;
        namesAlpha = 255;
        controlScreen = 0;
        setControlStrings();
		ofxAssets::AssetRegister().addAddon("ofxKCTouchGui2");
		ofRegisterTouchEvents(this);
	}
	
	//----------
	void Controller::add(shared_ptr<ofxKCTouchGui::Element> element) {
		this->elements.push_back(element);
	}
	
	//----------
	void Controller::drop(shared_ptr<ofxKCTouchGui::Element> element) {
		bool found = false;
		while (!found) {
			for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
				if (*it == element) {
					this->elements.erase(it);
					found = true;
				}
			}
		}
	}
	
	//----------
	void Controller::update() {
		for(auto element : this->elements) {
			element->update();
		}
        int bCount;
		for(auto &note : notes) {
            bCount = note.noteIndex;
            if(bCount>=0) {
                float newHueTheta = note.polarLoc.theta/(2*myPi) - 0.25 - theEngine->pitchRef;
                while (newHueTheta < 0.)
                    newHueTheta ++;
                while (newHueTheta >=1.)
                    newHueTheta --;
                bokehs[bCount].setHue((int) (newHueTheta*256));
                bokehs[bCount].setWidth((int) (abs((int)((fmodf(note.getAge()*1000, 1000)*0.8-400)/2)) + 250) * padScale);
                bokehs[bCount].setLocation(note.polarLoc.x, note.polarLoc.y);
                bokehs[bCount].update(bokehs[bCount].getState());
            }
		}
        for(auto &note : oldNotes) {
            bCount = note.noteIndex;
            if(bCount>=0) {
                float newHueTheta = note.polarLoc.theta/(2*myPi) - 0.25 - theEngine->pitchRef;
                while (newHueTheta < 0.)
                    newHueTheta ++;
                while (newHueTheta >=1.)
                    newHueTheta --;
                bokehs[bCount].setHue((int) (newHueTheta*256));
                bokehs[bCount].setWidth((int) (abs((int)((fmodf(note.getAge()*1000, 1000)*0.8-400)/2)) + 250) * padScale);
                bokehs[bCount].update(bokehs[bCount].getState());
            }
        }
        
                
        
	}
	//----------
	void Controller::draw() {
		ofPushMatrix();
		ofScale(this->zoom, this->zoom);
		for(auto element : this->elements) {
			ofPushMatrix();
			ofTranslate(element->getBounds().getTopLeft());
			element->draw();
			ofPopMatrix();
		}
        ofPushMatrix();
    
       
        ofTranslate(getWidth()/2, getHeight()/2);
        for(auto &note : notes) {
            bokehs[note.noteIndex].draw();
        }
        for(auto &note : oldNotes)
            bokehs[note.noteIndex].draw();
         //draw buttons from center
        if(sustainIsOn)
            sustainOnImage.draw(0,0);
        if(sustainLock)
            sustainLockImage.draw(0,0);
        if(sostenutoOn)
            sostOnImage.draw(0,0);
        if(sostenutoLock)
            sostLockImage.draw(0,0);
        if(setChord)
            setChordImage.draw(0,0);
        if(chord1 || chord2 || chord3 || chord4) {
            if(setChord) {
                ofPushStyle();
                ofSetColor(200, 40, 40);
                chordOn.draw(0,0);
                ofPopStyle();
            } else
                chordOn.draw(0,0);
        }
        ofPushStyle();
        
        
        ofSetColor(255, 255, 255);
        ofSetLineWidth(5);
        ofPushMatrix();
        ofRotateZ((0.6936 + 0.69 * slider1Val)*180/myPi);
        ofDrawLine(0, 465 * padScale, 0, 506 * padScale);
        ofPopMatrix();
        ofPushMatrix();
        ofRotateZ(-(0.6936 + 0.69 * slider4Val)*180/myPi);
        ofDrawLine(0, 465 * padScale, 0, 506 * padScale);
        ofPopMatrix();
        ofPushMatrix();
        ofRotateZ((0.5236 + 0.86 * slider2Val)*180/myPi);
        ofDrawLine(0, 410 * padScale, 0, 452 * padScale);
        ofPopMatrix();
        ofPushMatrix();
        ofRotateZ(-(0.5236 + 0.86 * slider3Val)*180/myPi);
        ofDrawLine(0, 410 * padScale, 0, 452 * padScale);
        ofPopMatrix();
        
        ofSetColor(0, 0, 0);
        ofRotateZ(50);
        ofDrawBitmapString(slider1, -50, 487 * padScale);
        ofDrawBitmapString(slider2, -40, 432 * padScale);
        ofRotateZ(-100);
        ofDrawBitmapString(slider3, -40, 432 * padScale);
        ofDrawBitmapString(slider4, -50, 487 * padScale);
        
        ofPopMatrix();
        
        ofDrawBitmapString(button1, 20 * padScale, getHeight() - 75 * padScale);
        ofDrawBitmapString(button2, getWidth()-67 * padScale, getHeight() - 75 * padScale);
        ofDrawBitmapString(shift1, 80 * padScale, getHeight() - 15 * padScale);
        ofDrawBitmapString(shift2, getWidth() - 122 * padScale, getHeight()-15 * padScale);
        
        ofPopStyle();
        
        ofPopMatrix();
        
	}
	//----------
	void Controller::touchDown(ofTouchEventArgs & rawTouch) {
		shared_ptr<Touch> touch;
		
		//check if we've already got this touch in the register (we basically never should at this point)
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			touch = shared_ptr<Touch>(new Touch(rawTouch, zoom));
            
            PolarPoint touchPoint;
            touchPoint.polarFromCartesian(touch->x-getWidth()/2, touch->y-getHeight()/2);
            touch->setPolarLocation(touchPoint);
            if (touchPoint.radius > 520 * padScale) {
                if (touchPoint.theta < (myPi * 1.85) && touchPoint.theta > 1.15 * myPi) {
                    if (touchPoint.theta < 3*myPi/2) {
                        sostenutoOn = true;
                        for (int i = notes.size()-1; i>=0; i--) {
                            oldNotes.push_back(notes[i]);
                            notes.pop_back();
                        }
                        sustainIsOn = false;
                        sustainLock = false;
                        

                    }
                    else {
                        sustainIsOn = true;
                        sostenutoLock = false;
                        sostenutoOn = false;
                    }
                } else if (touchPoint.theta > 0.6632 && touchPoint.theta < myPi - 0.6632) {
                    // switch Controls
                    if(touchPoint.theta > myPi/2) controlScreen -=1;
                    else controlScreen +=1;
                    if(controlScreen > 4) controlScreen = 0;
                    if(controlScreen < 0) controlScreen = 4;
                    setControlStrings();
                    
                } else if (touchPoint.theta > 0.5062 && touchPoint.theta < 0.6632) {
                    //Button 2
                    switch (controlScreen) {
                        case 0:
                            showNames = !showNames;
                            break;
                        case 1:
                            theEngine->quantizeIsOn = !theEngine->quantizeIsOn;
                            break;
                        //case 2:
                          // Env preset 2
                            //break;
                        //case 3:
                            //wave preset 2
                            //break;
                        case 4:
                            theEngine->tremOn = !theEngine->tremOn;
                            for(auto &note:notes)
                                theEngine->updateTremOn(note.noteIndex);
                            for(auto &note:oldNotes)
                                theEngine->updateTremOn(note.noteIndex);
                            //break;
                    }
                } else if (touchPoint.theta > myPi - 0.6632 && touchPoint.theta < myPi - 0.5062) {
                    //Button 1
                    switch (controlScreen) {

                        case 0:
                            showFlats = !showFlats;
                            break;
                        //case 1:
                            // Grid Turn
                            //break;
                            //case 2:
                            // Env preset 1
                            //break;
                            //case 3:
                            //wave preset 1
                            //break;
                            //case 4:
                            //filter on/off
                            //break;
                    }
                
                
                } else if ((touchPoint.theta > 0.17 && touchPoint.theta < myPi/6) || (touchPoint.theta > myPi*5/6 &&touchPoint.theta < myPi - 0.17))
                    //set Chords
                    setChord = true;
                
                
            } else  if (touchPoint.radius > 410 * padScale && touchPoint.radius < 520 * padScale) {
                if (touchPoint.theta < myPi + 0.17 && touchPoint.theta > myPi) {
                    if(setChord && !chord1)
                        chords[0].clear();
                    chord1 = !chord1;
                    if(chord1) {
                        chordOn.clear();
                        chordOn.load("chord1Shade.png");
                        chordOn.resize(getWidth(),getHeight());
                        chord2 = false;
                        chord3 = false;
                        chord4 = false;
                    }
                }
                else if (touchPoint.theta < myPi && touchPoint.theta > myPi - 0.17) {
                    if(setChord && !chord3)
                        chords[2].clear();
                    chord3 = !chord3;
                    if(chord3) {
                        chordOn.clear();
                        chordOn.load("chord3Shade.png");
                        chordOn.resize(getWidth(),getHeight());
                        chord2 = false;
                        chord1 = false;
                        chord4 = false;
                    }
                }
                else if (touchPoint.theta > 2*myPi - 0.17 && touchPoint.theta < 2*myPi) {
                    if(setChord && !chord2)
                        chords[1].clear();
                    chord2 = !chord2;
                    if(chord2) {
                        chordOn.clear();
                        chordOn.load("chord2Shade.png");
                        chordOn.resize(getWidth(),getHeight());
                        chord1 = false;
                        chord3 = false;
                        chord4 = false;
                    }
                }
                else if (touchPoint.theta > 0 && touchPoint.theta < 0.17){
                    if(setChord && !chord4)
                        chords[3].clear();
                    chord4 = !chord4;
                    if(chord4) {
                        chordOn.clear();
                        chordOn.load("chord4Shade.png");
                        chordOn.resize(getWidth(),getHeight());
                        chord2 = false;
                        chord3 = false;
                        chord1 = false;
                    }
                }
                else if (touchPoint.theta > 0.17 && touchPoint.theta < myPi - 0.17) {
                    controls(touchPoint);
                }
                    
            }
                
                
            else if(touchPoint.radius <= 345 * padScale) {
                if (chord1 && !setChord && !chords[0].empty()) {
                    startChordWithLocation(0, touchPoint, touch);
                } else if (chord2 && !setChord && !chords[1].empty()) {
                    startChordWithLocation(1, touchPoint, touch);
                } else if (chord3 && !setChord && !chords[2].empty()) {
                    startChordWithLocation(2, touchPoint, touch);
                } else if (chord4 && !setChord && !chords[3].empty()) {
                    startChordWithLocation(3, touchPoint, touch);
                } else {
                    Note* thisNote = theEngine->newNote(touchPoint);
                    touch->setVoiceIndex(thisNote->noteIndex);
                    thisNote->noteTouch = touch.get();
                    bokehs[thisNote->noteIndex].setState(1);
                    notes.push_back(*thisNote);
                }
                
                
                
            } else if (touchPoint.radius > 345 * padScale && touchPoint.radius <= 405 * padScale) {
                touch->movePitchRing = true;
            }
			this->touches.insert(pair<int, shared_ptr<Touch> >(rawTouch.id, touch));
		} else {
			touch = findTouch->second;
		}
		for(auto it = this->elements.rbegin(); it != this->elements.rend(); it++) {
			if (!touch->isAttached()) {
				auto element = *it;
                element->touchDown(touch);
			}
		}
	}
    
    void Controller::buildChordWithLocation(int chord, PolarPoint polarLoc) {
        PolarPoint chordPolarLoc = polarLoc;
        chords[chord].push_back(chordPolarLoc);
    }
    
    void Controller::startChordWithLocation(int chordNum, PolarPoint touchPoint, shared_ptr<Touch> touch) {
        PolarPoint tempPolar;
        for(int i = 0; i < chords[chordNum].size(); i++) {
            tempPolar.radius = touchPoint.radius * chords[chordNum][i].radius/chords[chordNum][0].radius;
            tempPolar.theta = touchPoint.theta + chords[chordNum][i].theta - chords[chordNum][0].theta;
            if (tempPolar.theta >= 2*myPi) tempPolar -= 2*myPi;
            if (tempPolar.theta < 0) tempPolar += 2*myPi;
            tempPolar.newCartesians();
            Note* thisNote = theEngine->newNote(tempPolar);
            if(i == 0) touch->setVoiceIndex(thisNote->noteIndex);
            thisNote->noteTouch = touch.get();
            bokehs[thisNote->noteIndex].setState(1);
            notes.push_back(*thisNote);
        }

    }
    
    void Controller::moveChordNoteWithLocation(int chordNum, PolarPoint touchPoint, Note* note, int j) {
        PolarPoint tempPolar = touchPoint;
        j %= chords[chordNum].size();
        tempPolar.radius *= chords[chordNum][j].radius/chords[chordNum][0].radius;
        tempPolar.theta += chords[chordNum][j].theta - chords[chordNum][0].theta;
        if (tempPolar.theta >= 2*myPi) tempPolar.theta -= 2*myPi;
        if (tempPolar.theta < 0) tempPolar.theta += 2*myPi;
        tempPolar.newCartesians();
        theEngine->noteMoved(note,tempPolar);
    }

	
	//----------
	void Controller::touchMoved(ofTouchEventArgs & rawTouch) {
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			ofLogError("ofxKCTouch") << "We're receiving a touchMoved event before a touchDown. The world has gone to hell";
			return;
		}
		
		auto & touch = findTouch->second;
		touch->moveTo((ofVec2f &) rawTouch / zoom);
        PolarPoint touchPoint;
        touchPoint.polarFromCartesian(touch->x-getWidth()/2, touch->y-getHeight()/2);
        float deltaTheta = touchPoint.theta - touch->getPolarLocation().theta;
        //move playing note
        if (touchPoint.radius > 520 * padScale) {
            if (touchPoint.theta < (2 * myPi - 0.17) && touchPoint.theta > myPi+ 0.17 ) {
                if (touchPoint.theta < myPi + myPi/6) {
                    if (sostenutoLock == false && sostenutoOn) {
                        sostenutoLock = true;
                    }
                    
                }
                else if (touchPoint.theta > 2* myPi - myPi / 6) {
                    if (sustainLock == false && sustainIsOn) {
                        sustainLock = true;
                    }
                }
            }

            
        } else if (touchPoint.radius > 410 * padScale && touchPoint.radius < 520 * padScale) {
            if (touchPoint.theta < (2 * myPi - 0.17) && touchPoint.theta > myPi+ 0.17 ) {
                if (touchPoint.theta > 3 * myPi / 2) {
                    //change volume
                    theEngine->masterVolume-=deltaTheta;
                    if(theEngine->masterVolume > 1) theEngine->masterVolume = 1;
                    if(theEngine->masterVolume < 0) theEngine->masterVolume = 0;
                    for(auto & note :notes)
                        theEngine->updateMasterVolume(note.noteIndex);
                    for(auto & note :oldNotes)
                        theEngine->updateMasterVolume(note.noteIndex);
                } else {
                    theEngine->zoom+=deltaTheta*2;
                    updatePitches();
                }
            }
            else if (touchPoint.theta > 0.17 && touchPoint.theta < myPi - 0.17) {
                controls(touchPoint);
            }
        }

        
        if(touchPoint.radius <= 345 * padScale && touch->getVoiceIndex()>=0) {
            int j = 0;
            for(int i = 0; i < notes.size(); i++) {
                
                if(notes[i].noteTouch == touch.get()) {
                    
                    if(chord1 && !setChord && !chords[0].empty()) {
                        moveChordNoteWithLocation(0, touchPoint, &notes[i], j);
                        j++;
                    } else if(chord2 && !setChord && !chords[1].empty()) {
                        moveChordNoteWithLocation(1, touchPoint, &notes[i], j);
                        j++;
                    } else if(chord3 && !setChord && !chords[2].empty()) {
                        moveChordNoteWithLocation(2, touchPoint, &notes[i], j);
                        j++;
                    } else if(chord4 && !setChord && !chords[3].empty()) {
                        moveChordNoteWithLocation(3, touchPoint, &notes[i], j);
                        j++;
                    } else {
                        theEngine->noteMoved(&notes[i], touchPoint);
                    }
                }
            }
        } else
            //end note if leaves playing surface
        if(touchPoint.radius > 345 * padScale && touch->getPolarLocation().radius * padScale <= 345 && touch->getVoiceIndex()>=0) {
            for(int i = notes.size()-1; i>=0; i--) {
                if (notes[i].noteTouch == touch.get()) {
                    theEngine->noteEnded(notes[i].noteIndex);
                    notes[i] = notes[notes.size()-1];
                    notes.pop_back();
                }
            }
                
        } else
            //rotate pitchring
        if (/*touchPoint.radius > 345 && touchPoint.radius <= 405 && */ touch->movePitchRing){
            theEngine->pitchRef += deltaTheta/(2*myPi);
            while(theEngine->pitchRef < 0)
                theEngine->pitchRef += 1;
            while(theEngine->pitchRef >= 1)
                theEngine->pitchRef -= 1;
            //if gridturn (to-do)
            theEngine->pointerRef += deltaTheta/(2*myPi);
            while(theEngine->pointerRef < 0) theEngine->pointerRef += 1;
            while(theEngine->pointerRef >=1) theEngine->pointerRef -= 1;
        }
        updatePitches();
        //update touch polarLocation
        touch->setPolarLocation(touchPoint);
		for(auto element : this->elements) {
			if (touch->isAttachedTo(element.get())) {
				element->touchMoved(touch);
			}
		}
	}
	
	//----------
	void Controller::touchUp(ofTouchEventArgs & rawTouch) {
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			ofLogError("ofxKCTouch") << "We're receiving a touchUp event before a touchDown. The world has gone to hell";
			return;
		}
		
		auto & touch = findTouch->second;
        PolarPoint touchPoint;
        touchPoint.polarFromCartesian(touch->x-getWidth()/2, touch->y-getHeight()/2);
        
        if (touchPoint.radius > 520 * padScale) {
            
            if (touchPoint.theta < (myPi * 1.85) && touchPoint.theta > 1.15 * myPi) {
                if (touchPoint.theta < 3*myPi/2) {
                    sostenutoOn = false;
                    sostenutoLock = false;
                    
                    if(!sustainIsOn) {
                        endOldNotes();
                    }
                }
                else {
                    sustainIsOn = false;
                    sustainLock = false;
                    // end all notes without touches
                    if(!sostenutoOn)
                        endOldNotes();
                    
                }
            } else if ((touchPoint.theta > 0.17 && touchPoint.theta < myPi/6) || (touchPoint.theta > myPi*5/6 &&touchPoint.theta < myPi - 0.17))
                    setChord = false;
            
        } else if (touchPoint.theta <=345) {
            for(int i = notes.size()-1; i >= 0; i--) {
                if(notes[i].noteTouch == touch.get()) {
                    if(sustainIsOn) {
                        oldNotes.push_back(notes[i]);
                    } else {
                        theEngine->noteEnded(notes[i].noteIndex);
                        bokehs[notes[i].noteIndex].setState(0);
                        bokehs[notes[i].noteIndex].update(bokehs[notes[i].noteIndex].getState());
                        
                    }
                    
                    if(setChord) {
                        int chordNum;
                        if(chord1) chordNum = 0;
                        else if(chord2) chordNum = 1;
                        else if(chord3) chordNum = 2;
                        else if(chord4) chordNum = 3;
                        buildChordWithLocation(chordNum, touchPoint);
                    }

                    
                    notes[i] = notes[notes.size()-1];
                    notes.pop_back();
                }
            }
        }
        
		for(auto element : this->elements) {
			element->touchUp(touch);
		}
		
		this->touches.erase(findTouch);
	}
    
    void Controller::updatePitches() {
        for (auto & note :notes) {
            theEngine->makePitchForNote(&note);
            theEngine->sendNoteParams(&note);
        }
        for(auto & note : oldNotes) {
            theEngine->makePitchForNote(&note);
            theEngine->sendNoteParams(&note);
        }
    }
    
    void Controller::endOldNotes() {
        for(int i = oldNotes.size()-1; i >= 0; i--) {
            theEngine->noteEnded(oldNotes[i].noteIndex);
            bokehs[oldNotes[i].noteIndex].setState(0);
            bokehs[oldNotes[i].noteIndex].update(bokehs[oldNotes[i].noteIndex].getState());
            oldNotes.pop_back();
        }
    }
    
    void Controller::controls(PolarPoint touchPoint) {
        if (touchPoint.radius > 465 * padScale) {
            if (touchPoint.theta > myPi / 2){
                //S1
                float S1 = (touchPoint.theta-2.2644)/(0.69);
                if (S1 < 0) S1 = 0;
                if (S1 > 1) S1 = 1;
                slider1Val = S1;
                switch (controlScreen) {
                        //Display
                    case 0:
                        blackKeysAlpha = S1 * 255;
                        break;
                        //Grid
                    case 1:
                        gridAlpha = S1 * 255;
                        break;
                        //Env
                    case 2:
                        theEngine->attack = (S1 * 2);
                        for(auto &note:notes)
                            theEngine->updateAttack(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateAttack(note.noteIndex);
                        break;
                        //Wave
                    case 3:
                        theEngine->sinMix = (S1);
                        for(auto &note:notes)
                            theEngine->updateSinMix(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateSinMix(note.noteIndex);
                        break;
                        //Effects
                    case 4:
                        theEngine->cutoff = (20*pow(2,(S1*10)));
                        for(auto &note:notes)
                            theEngine->updateCutoff(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateCutoff(note.noteIndex);
                        break;
                }
            } else {
                //S4
                float S4 = 1-((touchPoint.theta-0.1872)/0.69);
                if (S4 < 0) S4 = 0;
                if (S4 > 1) S4 = 1;
                slider4Val = S4;
                switch (controlScreen) {
                        //Display
                    case 0:
                        // color wheel sat
                        break;
                        //Grid
                    case 1:
                        theEngine->quantNumber = (int) (S4 * 22) + 2;
                        // handle non-even quantize cases
                        break;
                        //Env
                    case 2:
                        theEngine->release = (S4 * 4);
                        for(auto &note:notes)
                            theEngine->updateRelease(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateRelease(note.noteIndex);
                        break;
                        //Wave
                    case 3:
                        theEngine->triMix = (S4);
                        for(auto &note:notes)
                            theEngine->updateTriMix(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateTriMix(note.noteIndex);
                        break;
                        //Effects
                    case 4:
                        theEngine->tremRate = ((S4*8)+2);
                        for(auto &note:notes)
                            theEngine->updateTremRate(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateTremRate(note.noteIndex);
                        break;
                }
            }
        } else {
            if (touchPoint.theta > myPi / 2){
                //S2
                float S2 =(touchPoint.theta-2.0944)/(0.86);
                if (S2 < 0) S2 = 0;
                if (S2 > 1) S2 = 1;
                slider2Val = S2;
                switch (controlScreen) {
                        //Display
                    case 0:
                        namesAlpha = (S2 * 255);
                        break;
                        //Grid
                    case 1:
                        // theEngine->quantNumber = (int) (S4 * 22) + 2;
                        break;
                        //Env
                    case 2:
                        theEngine->decay = (S2 * 2);
                        for(auto &note:notes)
                            theEngine->updateDecay(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateDecay(note.noteIndex);
                        break;
                        //Wave
                    case 3:
                        theEngine->sawMix = (S2);
                        for(auto &note:notes)
                            theEngine->updateSawMix(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateSawMix(note.noteIndex);
                        break;
                        //Effects
                    case 4:
                        theEngine->Q = ((S2*19)+1);
                        for(auto &note:notes)
                            theEngine->updateQ(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateQ(note.noteIndex);
                        break;
                }
            } else {
                //S3
                float S3 = 1 - ((touchPoint.theta-0.1872)/0.86);
                if (S3 < 0) S3 = 0;
                if (S3 > 1) S3 = 1;
                slider3Val = S3;
                switch (controlScreen) {
                        //Display
                    case 0:
                        spiralAlpha = (S3 * 255);
                        break;
                        //Grid
                    case 1:
                        // quantize type
                        // handle non-even quantize cases (to-do)
                        break;
                        //Env
                    case 2:
                        theEngine->sustain = (S3 * 100);
                        for(auto &note:notes)
                            theEngine->updateSustain(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateSustain(note.noteIndex);
                        break;
                        //Wave
                    case 3:
                        theEngine->squareMix = (S3);
                        for(auto &note:notes)
                            theEngine->updateSquareMix(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateSquareMix(note.noteIndex);
                        break;
                        //Effects
                    case 4:
                        theEngine->tremStr = (S3);
                        for(auto &note:notes)
                            theEngine->updateTremStr(note.noteIndex);
                        for(auto &note:oldNotes)
                            theEngine->updateTremStr(note.noteIndex);
                        break;
                }
                
            }
        }

    }
    
    void Controller::setControlStrings() {
        switch(controlScreen) {
            case 0:
                shift1 = "FX";
                shift2 = "Grid";
                button1 = "Sharps/\nFlats";
                button2 = "Show\nNotes";
                slider1 = "Black Key Fade";
                slider2 = "Note Name Fade";
                slider3 = "Spiral Fade";
                slider4 = "Color Brightness";
                slider1Val = blackKeysAlpha/255;
                slider2Val = namesAlpha/255;
                slider3Val = spiralAlpha/255;
                //slider4Val =
                break;
            case 1:
                shift1 = "Display";
                shift2 = "Env";
                button1 = " Grid\nRotate";
                button2 = "Grid\n On";
                slider1 = "Grid Fade";
                slider2 = " ";
                slider3 = "Grid Type";
                slider4 = "Grid Number";
                slider1Val = gridAlpha/255;
                //slider2Val =
                //slider3Val =
                slider4Val = (theEngine->quantNumber-2)/22;
                break;
            case 2:
                shift1 = "Grid";
                shift2 = "Wave";
                button1 = "Preset\n  1";
                button2 = "Preset\n  2";
                slider1 = "Attack";
                slider2 = "Decay";
                slider3 = "Sustain";
                slider4 = "Release";
                slider1Val = theEngine->attack;
                slider2Val = theEngine->decay;
                slider3Val = theEngine->sustain/100;
                slider4Val = theEngine->release/2;
                break;
            case 3:
                shift1 = "Env";
                shift2 = "FX";
                button1 = "Preset\n  1";
                button2 = "Preset\n  2";
                slider1 = "Sine Level";
                slider2 = "Saw Level";
                slider3 = "Square Level";
                slider4 = "Tri Level";
                slider1Val = theEngine->sinMix;
                slider2Val = theEngine->sawMix;
                slider3Val = theEngine->squareMix;
                slider4Val = theEngine->triMix;
                break;
            case 4:
                shift1 = "Wave";
                shift2 = "Display";
                button1 = "LPF";
                button2 = "Tremolo";
                slider1 = "Cutoff Frequency";
                slider2 = "Filter Q";
                slider3 = "Tremolo Depth";
                slider4 = "Tremolo Rate";
                slider1Val = (log2(theEngine->cutoff/20))/10;
                slider2Val = (theEngine->Q-1)/19;
                slider3Val = theEngine->tremStr;
                slider4Val = (theEngine->tremRate-2)/8;
                break;
        }

    }
    
	//----------
	const vector<shared_ptr<Element> > & Controller::getElements() const {
		return this->elements;
	}
	
	//----------
	const map<int, shared_ptr<Touch> > & Controller::getTouches() const {
		return this->touches;
	}
	
	//----------
	void Controller::setZoom(float zoom) {
		this->zoom = zoom;
	}
	
	//----------
	float Controller::getZoom() const {
		return this->zoom;
	}
	
	//----------
	float Controller::getWidth() const {
		if (this->brokenRotation) {
			return ofGetHeight() / zoom;
		} else {
			return ofGetWidth() / zoom;
		}
	}
	
	//----------
	float Controller::getHeight() const {
		if (this->brokenRotation) {
			return ofGetWidth() / zoom;
		} else {
			return ofGetHeight() / zoom;
		}
	}
	
	//----------
	void Controller::setBrokenRotation(bool brokenRotation) {
		this->brokenRotation = brokenRotation;
	}
}
