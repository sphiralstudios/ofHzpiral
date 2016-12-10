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
        //        xo = xo - ofApp::getAppWidth()/2;
        //        yo = yo - ofApp::getAppHeight()/2;
    x = xo;
    y = yo;
    z = 0;
    radius = pow((pow(xo,2)+pow(yo,2)),0.5);
        //    double rmax = pow((pow(appWidth/2,2) + pow(appHeight/2,2)),0.5);
        //    double cutoff = r/rmax * 5000;
    theta = atan2(yo,xo);
    if(theta < 0) theta += (2*myPi);
    if(theta >= (2*myPi)) theta -= (2*myPi);
    
//        if (xo<0 && yo<0) {
//            theta=myPi+atan(yo/xo);
//        } else if (xo>0 && yo<0)
//            theta=(2*myPi)+atan(yo/xo);
//        else if (xo<0 && yo>0)
//            theta = myPi + atan(yo/xo);
//        
//        else {
//            theta=atan(yo/xo);
//        }
    
    }
void PolarPoint::newCartesians() {
    x = radius * cos(fmod(theta, (2 * myPi)));
    y = radius * sin(fmod(theta, (2 * myPi)));
    //    point.y = point.y - 768;
    //   float tempTheta = -theta - 90;
    
    
    if ((theta < (myPi/2) &&  theta > (-myPi/2)) || (theta > (3 * myPi / 2) && theta < (5 * myPi / 2)))
        
        //        (fmod(theta, (2 * pi)) < 0.25 || fmod(theta, (2 * pi)) > 0.75)
        x = fabs(x);
    else
        x =  - fabs(x);
    
    //    NSLog(@"Theta = %e", theta);
    if ((theta > 0.0 && theta <= myPi) || (theta <= -myPi && theta > (-2 * myPi)) || (theta > (2*myPi) && theta <= (3*myPi)))
        //(fmod(theta, (2 * pi)) < 0.5)
        
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
//        x = radius * cos(fmod(theta, (2 * myPi)));
//        y = radius * sin(fmod(theta, (2 * myPi)));
//        //    point.y = point.y - 768;
//        //   float tempTheta = -theta - 90;
//        
//        
//        if ((theta < (myPi/2) &&  theta > (-myPi/2)) || (theta > (3 * myPi / 2) && theta < (5 * myPi / 2)))
//            
//            //        (fmod(theta, (2 * pi)) < 0.25 || fmod(theta, (2 * pi)) > 0.75)
//            x = fabs(x);
//        else
//            x =  - fabs(x);
//        
//        //    NSLog(@"Theta = %e", theta);
//        if ((theta > 0.0 && theta <= myPi) || (theta <= -myPi && theta > (-2 * myPi)) || (theta > (2*myPi) && theta <= (3*myPi)))
//            //(fmod(theta, (2 * pi)) < 0.5)
//            
//            y = fabs(y);
//        else
//            y = - fabs(y);
        //       y = -y;
        z = 0;
    }
    
