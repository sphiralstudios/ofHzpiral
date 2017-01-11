//
//  polarPoint.cpp
//  Hzpiral
//
//  Created by Mark Hertensteiner on 11/28/16.
//
//

#include "polarPoint.h"




PolarPoint::PolarPoint () {}
PolarPoint::~PolarPoint () {}
    
void PolarPoint::polarFromCartesian(double xo, double yo) {
    x = xo;
    y = yo;
    z = 0;
    radius = pow((pow(xo,2)+pow(yo,2)),0.5);
    theta = atan2(yo,xo);
    if(theta < 0) theta += (2*myPi);
    if(theta >= (2*myPi)) theta -= (2*myPi);
}

void PolarPoint::newCartesians() {
    x = radius * cos(fmod(theta, (2 * myPi)));
    y = radius * sin(fmod(theta, (2 * myPi)));
    
    if ((theta < (myPi/2) &&  theta > (-myPi/2)) || (theta > (3 * myPi / 2) && theta < (5 * myPi / 2)))
        x = fabs(x);
    else
        x =  - fabs(x);
    if ((theta > 0.0 && theta <= myPi) || (theta <= -myPi && theta > (-2 * myPi)) || (theta > (2*myPi) && theta <= (3*myPi)))
        y = fabs(y);
    else
        y = - fabs(y);
}

void PolarPoint::polarFromTheta (float thetaMake, float initialRadius) {
    radius = initialRadius * pow(2,thetaMake/(2*myPi));
    theta = thetaMake;
    while (theta > (2*myPi)) theta -= (2*myPi);
    while (theta < 0) theta += (2*myPi);
    newCartesians();
    z = 0;
    }
    
