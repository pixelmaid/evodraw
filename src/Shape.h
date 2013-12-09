//
//  Shape.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/12/13.
//
//

#ifndef evodraw1_Shape_h
#define evodraw1_Shape_h


#include "ofMain.h"
#include "ofxVectorGraphics.h"
#include "Geom2D.h"
#include <string>
#include "Node.h"
#include "Color_Const.h"

#define OVERLAP_DIST 0.5
#define RESCALE_RES 4

class Shape: public Node{
    public:
    Shape():Node(NULL,NULL)
            {
            closed = false;
            dselected = false;
            selected = false;
            selectedP = -1;
            type="shape";
        }
    
        Shape(const Shape &rhs){
            *this = rhs;
        }
        
        Shape& operator = (const Shape &rhs){
            if(this!= &rhs){
                copyBaseVariables( (Shape*)&rhs );
            }
            return *this;
        }
        
        
        virtual ~Shape(){
            
        }
    
       virtual void Update(void)
        {
           Node::Update(); // calls base class' function            }
        } // Update()
    
        
        virtual vector<double>centroid(){
            vector<double>c;
            c.push_back(0);
            c.push_back(0);
            return c;
        }
        //returns bounding box as a vector (x,y,width,height)
        virtual vector<double>boundingbox(){
            vector<double>bb;
            bb.push_back(0);
            bb.push_back(0);
            bb.push_back(0);
            bb.push_back(0);
            return bb;
        }
        	
        virtual vector<double> getParams(){
            vector<double> params;
            return params;
            
        }
        
        virtual void size(double _x, double _y){
        
        }
        

        
        bool copyBaseVariables(const Shape *shape){
            
            if( shape == NULL ){
               // errorMessage = "copyBaseVariables(const Classifier *classifier) - Classifier is NULL!";
                //errorLog << errorMessage << endl;
                return false;
            }
            
            if( !this->copyBaseVariables( shape ) ){
                return false;
            }
            
            this->closed = shape->closed;
            this->selected = shape->selected;
            this->dselected = shape->selected;
            this->selectedP = shape->selected;
            this->points = shape->points;
            this->type = shape->type;
            
            Node:copyBaseVariables(shape);

            return true;
        }
        
               
      void addPoint(double x, double y){
          
          std::cout << "adding point" << std::endl;
          points.push_back(ofPoint());
            int last = points.size()-1;
            
            points[last].x = x;
            points[last].y = y;
          if(points.size()>2){
              double dist = Geom2D::euclidDist(x,y,points[0].x,points[0].y);
              if(dist<=OVERLAP_DIST)
                  closed=true;
          }
          
        }
        
       virtual bool checkSelect(double x, double y){
            selected=false;
            selectedP = -1;
            int numPts = points.size();
            for(int i = 0; i < numPts; i++){
               // bool select = Geom2D::pointOnLine(points[i].x, points[i].y, points[i-1].x, points[i-1].y, x, y, 10);
                if(i % RESCALE_RES == 0){
                    double dist = Geom2D::euclidDist(x,y,points[i].x,points[i].y);
                    cout<<dist<<endl; 
                    if(dist<=3){
                        selected=true;
                        selectedP = i;
                        break;
                    }
                    
                }
                
                
            }
           return selected;

            
        }
        
        virtual void checkDSelect(double x, double y){
            selectedP=-1;
            
        }
        
        
        
        virtual void movePoint(double x, double y){
           if(selectedP!=-1){
            points[selectedP].x = x;
            points[selectedP].y = y;
           }
        }
        virtual void move(double x, double y){
            
        }
        
        virtual void scale(double x, double y){
            
        }
        
       virtual void deselect(){
            selected = false;
            selectedP = -1;
        }
      
       
        virtual void draw(ofxVectorGraphics &output){
            cout << "draw shape " <<  endl;
            if( points.size() > 0 ){
                
                int numPts = points.size();
                
                output.setColor(Color_Const::deselected);
                if(selected){
                    output.setColor(Color_Const::selected);

                }
               // if(!closed)
                    output.noFill();
                //else
                    //output.fill();
                output.beginShape();
                
                               
                for(int i = 0; i < numPts; i++){
                    
                    //we need to draw the first and last point
                    //twice for a catmull curve
                    if(i == 0 || i == numPts -1){
                        output.curveVertex(points[i].x, points[i].y);
                    }
                    if(i % RESCALE_RES  == 0) output.curveVertex(points[i].x, points[i].y);
                    //output.curveVertex(points[i].x, points[i].y);
                }
                
                output.endShape();
               /*if(dselect){
                    for(int i = 0; i < numPts; i++){
                    
                        output.setColor(0x0088EE);
                        if(i ==selectedP){
                            output.setColor(0x00EA4E);
                            
                        }
                        //we need to draw the first and last point
                        //twice for a catmull curve
                        if(i == 0 || i == numPts -1){
                            output.rect(points[i].x, points[i].y,5,5);
                        }
                        if(i % RESCALE_RES  == 0)
                            output.rect(points[i].x, points[i].y,5,5);
                        }
                    
                }*/

            }
            

        }
       
        
        vector<ofPoint> points;
        bool closed;
        bool selected;
        bool dselected;
        int selectedP;
        string type; 
        int selectedColor= 0xF20606;
        double relX;
        double relY;


};


#endif

