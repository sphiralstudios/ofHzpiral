#pragma once

#include "Element.h"
#include "Touch.h"

#include "ofEvents.h"
#include "ofImage.h"
#include "ofGraphics.h"
#include "audioEngine.h"
#include <map>

class Bokeh {
public:
    Bokeh() {}
    ~Bokeh() {}
    
    void setup(){
        bokeh_image.load(ofToDataPath("Bokeh.png")); // Load the image
        bokeh_image.setAnchorPercent(0.5, 0.5);
        bokeh_color = ofColor::fromHsb(0, 255, 255);
        width = 300;
    }
    
    void update(float alphaValue) {
        bokeh_color.a = alphaValue * 255;
        // comment following line to improve performance on older ipad models
        bokeh_image.resize(width, width);

    }
    
    void draw() {
        ofPushStyle();
        ofSetColor(bokeh_color);
        bokeh_image.draw(x, y);
        ofPopStyle();
    }
    
    void setHue(int hue) {
        bokeh_color.setHue(hue);
    }
    
    void setLocation(int xl, int yl) {
        x = xl;
        y = yl;
    }
    
    void setWidth(int newWidth) {
        width = newWidth;
    }
    
    void setState(int state) {
        bokeh_state = state;
    }
    
    int getState() {
        return bokeh_state;
    }
    
private:
    ofImage bokeh_image;
    ofColor bokeh_color;
    int x, y, width, height;
    int bokeh_state;
    
};




namespace ofxKCTouchGui {
	class Controller {
	public:
		static Controller & X();
		Controller();
        ~Controller();
		void init();
		void add(shared_ptr<Element>);
		void drop(shared_ptr<Element>);

		void update();
		void draw();
		
		void touchDown(ofTouchEventArgs &);
		void touchMoved(ofTouchEventArgs &);
		void touchUp(ofTouchEventArgs &);
        void touchDoubleTap(ofTouchEventArgs &){}
		void touchCancelled(ofTouchEventArgs &) { }
        void updatePitches();
        void endOldNotes();
        void controls(PolarPoint touchPoint);
        void setControlStrings();
        
        void buildChordWithLocation(int chord, PolarPoint polarLoc);
        void startChordWithLocation(int chordNum, PolarPoint touchPoint, shared_ptr<Touch> touch);
        void moveChordNoteWithLocation(int chordNum, PolarPoint touchPoint, Note* note, int j);
		
		const vector<shared_ptr<Element> > & getElements() const;
		const map<int, shared_ptr<Touch> > & getTouches() const;
		
		void setZoom(float zoom = 1.0f);
		float getZoom() const;
		
		float getWidth() const;
		float getHeight() const;
		
		void setBrokenRotation(bool);
        float blackKeysAlpha, namesAlpha, spiralAlpha, gridAlpha;
        bool showFlats;
        
        float wheelTheta;
        float padScale;
        float slider1Val, slider2Val, slider3Val, slider4Val;
        
        AudioEngine* theEngine;
        ofImage sustainOnImage, sustainLockImage, sostOnImage, sostLockImage, setChordImage, chordOn;
        
	protected:
		vector<shared_ptr<Element> > elements;
		map<int, shared_ptr<Touch> > touches;
        vector<PolarPoint>* chords;
		float zoom;
        
		bool brokenRotation;
        bool sustainIsOn, sustainLock, sostenutoOn, sostenutoLock, holdOld, showNames;
        bool chord1, chord2, chord3, chord4, setChord;
        int controlScreen;
		static Controller * singleton;
        string shift1, shift2, button1, button2, slider1, slider2, slider3, slider4;
        Bokeh* bokehs;
        vector<Note> notes;
        vector<Note> oldNotes;
        
	};
}
