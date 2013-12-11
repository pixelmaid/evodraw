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
    
    virtual Shape* checkSelect(double px, double py){
        double k = Geom2D::inEllipse(px,py,x,y,width/2,height/2);
        selected = false;
        //cout<<"select val="<<k<<endl;
        if(k<=1.05&&k>=0.95){
            selected = true;
        }
        relX = px-x;
        relY= py-y;
        if(selected) return this;
        return NULL;
    }
   
    virtual bool move(double px, double py){
        if(selected){
            x = px-relX;
            y= py-relY;
        }
        return true;
    }
    
    virtual bool scale(double _x, double _y){
        
        if(selected){
            width = relX*2;
            height = relY*2;
            relX = _x-x;
            relY= _y-y;
        }
        return true;
        
    }
    
    virtual vector<double> getParams(){
        vector<double> params;
        params.push_back(x);
        params.push_back(y);
        params.push_back(width);
        params.push_back(height);
        return params;
        
    }
    
    virtual bool size(double _x, double _y){
        width = std::abs(x-_x)*2;
        height = std::abs(y-_y)*2;
        
       // cout << "width and height " << x-_x << " ," <<y-_y << " ," << width << " ," <<height << endl;
        return true;

    }
    
   virtual bool draw(ofxVectorGraphics &output,int color = -1) {
       setColor(output, color);
        output.ellipse(x, y, width, height);
       // cout << "draw ellipse at " << x << " ," <<y << " ," << width << " ," <<height << endl;
       return true;
    }
    
    double x;
    double y;
    double width;
    double height;

    
private:
    
};

#endif
