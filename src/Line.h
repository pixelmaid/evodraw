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
    Line(double _x, double _y):Shape(){
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
    
    virtual void Update(void)
    {
     
        cout<<"parent="<<this->GetParentNode()<<endl;
        if(NULL != this->GetParentNode()){
            Shape* s = (Shape*)this->GetParentNode();
            double xdiff = x2-x1;
            double ydiff = y2-y1;

            x1=s->getParams()[2];
            y1= s->getParams()[3];
            x2 = s->getParams()[2]+xdiff;
            y2 = s->getParams()[3]+ydiff;
            cout<<"line is updating with parent"<<endl;
        }
        
        cout<<"line is updating"<<endl;
        Shape::Update(); // calls base class' function            }
    } // Update()
    
    

    
    
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
    
    virtual bool checkSelect(double px, double py){
       //int k = Geom2D::pointOnLine(px,py,x1,y1,x2,y2,150);
        double k = Geom2D::distanceToLine(px, py, x1, y1, x2, y2);
        int r  = Geom2D::inRect(px, py, x1, y1, x2, y1, x2, y2, x1, y2, 0.01);
        
        selected = false;
        if(k<=2 && r >=0){
            selected = true;
        }
        relX = px-x1;
        relY= py-y1;
        return selected;
    }

    
    virtual void checkDSelect(double _x, double _y){
        selectedP=-1;
        if(abs(x1-_x) <= 5 && abs(y1-_y) <=5) selectedP=0;
        else if (abs(x2-_x) <= 5 && abs(y2-_y) <=5) selectedP = 1;
        
    }
    virtual void scale(double _x, double _y){
        
        if(selected){
            /*  double d1x = abs(width-x);
             double d1y = abs(height-y);
             double d2x = abs(_x-x);
             double d2y = abs(_y-y);
             double diffX = d2x-d1x;
             double diffY = d2y-d1y;
             
             
             cout<<"diffX ="<<diffX<<" diffY="<<diffY<<endl;
             width*=diffX;
             height*=diffY;*/
            
            
            
            //width = relX;
            //height = relY;
           /// relX = _x-x;
           // relY= _y-y;
        }
        
    }
    
    
    virtual void movePoint(double _x, double _y){
        
        if(selectedP==0){
            x1 = _x;
            y1 = _y;
        }
        else if(selectedP == 1){
            x2 = _x;
            y2 = _y;
        }
        this->Update();
    }
    
    
    virtual void move(double px, double py){
        if(selected){
           double xdiff = x1-(px-relX);
            double ydiff = y1-(py-relY);    
            x1  = px-relX;
            y1 = py-relY;
            x2 -= xdiff;
            y2-= ydiff;
        }
    this->Update();
    }
    
    
    
    virtual void draw(ofxVectorGraphics &output) {
        
       
        output.noFill();
        
        output.setColor(Color_Const::deselected);
        if(selected){
            output.setColor(Color_Const::selected);
            
        }
        
        output.line(x1, y1, x2,y2);
         if(selected){
             output.setColor(Color_Const::origin);
             output.fill();
        output.rect(x1-1.5,y1-1.5,3,3);
             output.setColor(Color_Const::end);

        output.rect(x2-1.5,y2-1.5,3,3);
         }
         output.setColor(0x00A4FF);
        if(selectedP==0){
           
            output.setColor(Color_Const::solid);
            output.fill();
            output.rect(x1-1.5,y1-1.5,3,3);
            output.noFill();
            output.setColor(Color_Const::origin);

            output.rect(x1-1.5,y1-1.5,3,3);

        }
        else if(selectedP == 1){
            output.setColor(Color_Const::solid);
            output.fill();
            output.rect(x2-1.5,y2-1.5,3,3);
            output.noFill();
            output.setColor(Color_Const::end);
            
            output.rect(x2-1.5,y2-1.5,3,3);

        }        // cout << "draw ellipse at " << x << " ," <<y << " ," << width << " ," <<height << endl;
    }
    
    double x1;
    double y1;
    double x2;
    double y2;
    
    
private:
    
};

#endif
