//
//  Line.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#ifndef evodraw1_Line_h
#define evodraw1_Line_h

#include "Shape.h"
#include "Geom2D.h"
#include <cmath>

class Line: public Shape{
public:
    Line(double _x, double _y){
        closed=false;
        dselected = false;
        selected = false;
        selectedP = -1;
        x1 = _x;
        y1 = _y;
        x2 = _x;
        y2 = _y;
        type = "line";
        cout << "created line" << endl;
    }
    
    Line(const Line &rhs){
        *this = rhs;
    }
    
    Line& operator = (const Line &rhs){
        if(this!= &rhs){
            
            this->x1 = rhs.x1;
            this->y1 = rhs.y1;
            this->x2=rhs.x2;
            this->y2=rhs.y2;
            
            copyBaseVariables( (Line*)&rhs );
        }
        return *this;
    }
    
    
    virtual ~Line(){
        
    }
    
    
    virtual vector<double>centroid(){
        return Geom2D::getMidpoint(x1,y1,x2,y2);
    }

    
    //returns bounding box as a vector (x,y,width,height)
    virtual vector<double>boundingbox(){
        vector<double>bb;
        if(Geom2D::isLeft(x1,x2))bb.push_back(x1);
        else bb.push_back(x2);
        if(Geom2D::isTop(y1,y2))bb.push_back(y1);
        else bb.push_back(y2);
        bb.push_back(abs(x1-x2));
        bb.push_back(abs(y1-y2));
        return bb;
    }
    
    virtual vector<double> getParams(){
        vector<double> params;
        params.push_back(x1);
        params.push_back(y1);
        params.push_back(x2);
        params.push_back(y2);
        return params;
        
    }
    
   virtual void size(double _x, double _y){
        x2 = _x;
        y2 = _y;
        
        // cout << "width and height " << x-_x << " ," <<y-_y << " ," << width << " ," <<height << endl;
        
    }
    
    virtual void draw(ofxVectorGraphics &output, bool dselect, int color) {
        output.setColor(color);
        output.noFill();
        output.line(x1, y1, x2,y2);
        output.setColor(0x00FF00);
        output.fill();
        output.rect(x1,y1,3,3);
        output.setColor(0xFF0000);
        output.rect(x2,y2,3,3);
        // cout << "draw ellipse at " << x << " ," <<y << " ," << width << " ," <<height << endl;
    }
    
    double x1;
    double y1;
    double x2;
    double y2;
    
    
private:
    
};

#endif
