//
//  Rect.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/27/13.
//
//

#ifndef evodraw1_Rectangle_h
#define evodraw1_Rectangle_h
#include "Shape.h"
#include <cmath>  

class Rectangle: public Shape{
public:
    Rectangle(double _x, double _y){
        closed=false;
        dselected = false;
        selected = false;
        selectedP = -1;
        width=0;
        height=0;
        x = _x;
        y = _y;
        type = "rect";
        cout << "created Rect" << endl;
    }
    
    Rectangle(const Rectangle &rhs){
        *this = rhs;
    }
    
    Rectangle& operator = (const Rectangle &rhs){
        if(this!= &rhs){
         
            this->width = rhs.width;
            this->height = rhs.height;
            this->x=rhs.x;
            this->y=rhs.y;
           
            copyBaseVariables( (Rectangle*)&rhs );
        }
        return *this;
    }
    
    
    virtual ~Rectangle(){
        
    }
    
    virtual vector<double>centroid(){
        vector<double>c;
        c.push_back(x+width/2);
        c.push_back(y+height/2);
        return c;
    }
    
    
    virtual void checkSelect(double px, double py){
        double k = Geom2D::inRect(px, py, x, y, x+width, y, x+width, y+height, x, y+height,0.01);
        selected = false;
        cout <<"actual rectArea="<<width*height<<endl;

        cout<<"select val="<<k<<endl;
        if(k==0){
            selected = true;
        }
        relX = px-x;
        relY= py-y;
    }
   
    //returns bounding box as a vector (x,y,width,height)
    virtual vector<double>boundingbox(){
        vector<double>bb;
        bb.push_back(x);
        bb.push_back(y);
        bb.push_back(width);
        bb.push_back(height);
        return bb;
    }
    
    virtual vector<double> getParams(){
        vector<double> params;
        params.push_back(x);
        params.push_back(y);
        params.push_back(width);
        params.push_back(height);
        return params;
        
    }

    
    virtual void size(double _x, double _y){
        width = (_x-x);
        height = (_y-y);
        
       // cout << "width and height " << x-_x << " ," <<y-_y << " ," << width << " ," <<height << endl;

    }
    
    virtual void move(double px, double py){
        if(selected){
            x = px-relX;
            y= py-relY;
        }
    }

    
   virtual void draw(ofxVectorGraphics &output, bool dselect, int color) {
        output.setColor(color);
       if(selected) output.setColor(selectedColor);

        output.noFill();
        output.rect(x, y, width, height);
       // cout << "draw Rect at " << x << " ," <<y << " ," << width << " ," <<height << endl;
    }
    
    double x;
    double y;
    double width;
    double height;

    
private:
    
};

#endif
