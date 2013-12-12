//
//  Vec2D.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/4/13.
//
//

#ifndef __evodraw1__Vec2D__
#define __evodraw1__Vec2D__

#include <iostream>
#include <math.h>

class Vec2D{
    
public:
   
     Vec2D(double _x, double _y);
    ~Vec2D();
    
    Vec2D add(Vec2D val);
    Vec2D sub(Vec2D val);
    Vec2D div(double val);
    Vec2D mul(double val);
    
    double distanceSqrd(Vec2D vec1, Vec2D vec2);
    double distance(Vec2D vec1, Vec2D vec2);
    static double lengthSqrd(Vec2D vec);
    double length();
    static Vec2D normalize(Vec2D vec);
    double dot(Vec2D b);
    static Vec2D projectOnto(Vec2D v, Vec2D w);
    
    
    double x;
    double y;
    
private:
    
};

#endif /* defined(__evodraw1__Vec2D__) */
