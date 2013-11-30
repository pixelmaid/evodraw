//
//  Ellipse.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/27/13.
//
//

#ifndef evodraw1_Ellipse_h
#define evodraw1_Ellipse_h
#include "Shape.h"
#include <cmath>  

class Ellipse: public Shape{
public:
    Ellipse(double _x, double _y){
        closed=false;
        dselected = false;
        selected = false;
        selectedP = -1;
        width=0;
        height=0;
        x = _x;
        y = _y;
        type = "ellipse";
        cout << "created ellipse" << endl;
    }
    
    Ellipse(const Ellipse &rhs){
        *this = rhs;
    }
    
    Ellipse& operator = (const Ellipse &rhs){
        if(this!= &rhs){
         
            this->width = rhs.width;
            this->height = rhs.height;
            this->x=rhs.x;
            this->y=rhs.y;
           
            copyBaseVariables( (Ellipse*)&rhs );
        }
        return *this;
    }
    
    
    virtual ~Ellipse(){
        
        
        
    }
    virtual virtual vector<double>centroid(){
        vector<double>c;
        c.push_back(x);
        c.push_back(y);
        return c;
    }
    
    //returns bounding box as a vector (x,y,width,height)
    virtual vector<double>boundingbox(){
        vector<double>bb;
        bb.push_back(x-width/2);
        bb.push_back(y-height/2);
        bb.push_back(width);
        bb.push_back(height);
        return bb;
    }
   
    void size(double _x, double _y){
        width = std::abs(x-_x)*2;
        height = std::abs(y-_y)*2;
        
       // cout << "width and height " << x-_x << " ," <<y-_y << " ," << width << " ," <<height << endl;

    }
    
   virtual void draw(ofxVectorGraphics &output, bool dselect) {
        output.setColor(0x000000);
        output.noFill();
        output.ellipse(x, y, width, height);
       // cout << "draw ellipse at " << x << " ," <<y << " ," << width << " ," <<height << endl;
    }
    
    double x;
    double y;
    double width;
    double height;

    
private:
    
};

#endif
