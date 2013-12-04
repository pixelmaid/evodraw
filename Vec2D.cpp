//
//  Vec2D.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/4/13.
//
//

#include "Vec2D.h"

Vec2D::Vec2D(double _x, double _y) {
    
    x = _x;
    y = _y;
    
}



Vec2D::~Vec2D(){
    
}




 Vec2D Vec2D::add(Vec2D val) {
    return Vec2D(x + val.x, y + val.y);
}

Vec2D Vec2D::sub(Vec2D val) {
    return Vec2D(x - val.x, y - val.y);
}

Vec2D Vec2D::div(double val) {
    return Vec2D(x / val, y / val);
}

Vec2D Vec2D::mul(double val) {
    return Vec2D(x * val, y * val);
}


double Vec2D::distanceSqrd(Vec2D vec1, Vec2D vec2) {
    return (pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}

double Vec2D::distance(Vec2D vec1, Vec2D vec2) {
    //Returns the distance between two points
    return sqrt(distanceSqrd(vec1, vec2));
}

double Vec2D::lengthSqrd(Vec2D vec) {
    //Returns the length of a vector sqaured. Faster than Length(), but only marginally
    return pow(vec.x, 2) + pow(vec.y, 2);
}


double Vec2D::length() {
    //Returns the length of a vector'
    return sqrt(lengthSqrd(*this));
}

 static Vec2D normalize(Vec2D vec) {
    //Returns a new vector that has the same direction as vec, but has a length of one.
    if (vec.x == 0 && vec.y == 0) {
        return Vec2D(0, 0);
    }
    
    return vec.div(vec.length());
}


 double Vec2D::dot(Vec2D b) {
    //Computes the dot product of a and b'
    return (x * b.x) + (y * b.y);
}


 Vec2D Vec2D::projectOnto(Vec2D v, Vec2D w) {
    //'Projects w onto v.'
    return v.mul(w.dot(v) / lengthSqrd(v));
}