//
//  polarPoint.hpp
//  Hzpiral
//
//  Created by Mark Hertensteiner on 11/28/16.
//
//

#ifndef polarPoint_hpp
#define polarPoint_hpp

#ifndef myPi
#define myPi 3.141592653589
#endif

#include "ofPoint.h"

//#include <stdio.h>

struct PolarPoint : public ofPoint {
    double radius;
    double theta;
    
    PolarPoint ();
    ~PolarPoint ();
    
    void polarFromCartesian(double xo, double yo);
    void newCartesians();
    
    void polarFromTheta (float thetaMake, float initialRadius);     
};

#endif /* polarPoint_hpp */
