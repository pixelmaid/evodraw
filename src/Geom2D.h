//
//  Geom2D.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/12/13.
//
//

#ifndef __evodraw1__Geom2D__
#define __evodraw1__Geom2D__

#include <iostream>
#include <math.h>  
#include "ofMain.h"
#include "Vec2D.h"

#define BIG 1e+15
#define SMALL 1e-15

class Geom2D{
    
public:
    
static double euclidDist(double x1, double y1, double x2, double y2);
        
static int pointOnLine(double pX, double pY, double x1, double y1, double x2, double y2, double m);
  
static double getSlope(double sx, double sy, double ex, double ey);
    
static double getYIntercept(double sx, double sy, double m);
    
static vector<double> getMidpoint(double sx, double sy, double ex, double ey);

static bool isLeft(double x1, double x2);
    
static bool isTop(double y1, double y2);
    
static vector<double> meanSd(vector<double> values, bool forcesd);
static vector<double> normalize(vector<double> values);
    
static double angle(double x1, double y1, double x2, double y2);
    
    static double distanceToLine(double px, double py, double x1, double y1, double x2, double y2);
    
static double inEllipse(double x, double y, double ex, double ey, double ew, double eh);
    
static double inRect(double pX, double pY, double aX, double aY, double bX, double bY, double cX, double cY, double dX, double dY, double m);

static double triangleArea(double aX, double aY, double bX, double bY, double cX, double cY);
private:
  Geom2D();
    
};


#endif /* defined(__evodraw1__Geom__) */
