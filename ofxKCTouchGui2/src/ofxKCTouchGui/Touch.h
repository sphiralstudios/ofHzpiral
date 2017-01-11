#pragma once

#include "ofVec2f.h"
#include "ofEvents.h"
#include "ofTypes.h"
#include "polarPoint.h"

using namespace std;

namespace ofxKCTouchGui {
	class Element;
	
	class Touch : public ofVec2f {
	public:
		Touch(const ofTouchEventArgs &, float zoom);
		Touch(int index, const ofVec2f & position);
				
		void attach(Element *);
		void detach();
		void moveTo(const ofVec2f & position);
		void clearFrameMovement();

		int getIndex() const;
		const ofVec2f & getPosition() const;
		
		bool isAttached() const;
		bool isAttachedTo(Element *) const;
		
		bool hasMoved() const;
		ofVec2f getMovement() const;
		ofVec2f getPreviousPosition() const;
		
		float getAge() const;
		
		void drawDebug() const;
        
        void setVoiceIndex(int vIndex);
        int getVoiceIndex();
        
        void setPolarLocation(PolarPoint polarPoint);
        PolarPoint getPolarLocation();
        
        bool movePitchRing;
        
        
	protected:
		int index;
        int voiceIndex;
		bool moved;
		ofVec2f movement;
		long bornTime;
		Element * attachedTo;
        PolarPoint polarLocation;
	};
	
	ostream & operator<<(ostream & os, const Touch &);
}