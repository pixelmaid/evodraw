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

#define OVERLAP_DIST 0.5
#define RESCALE_RES 4

    class Shape{
    public:
        Shape(){
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
        
        void checkSelect(double x, double y, bool dselect){
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

            
        }
        
        void deselect(){
            selected = false;
            dselected = false;
        }
      
       
        virtual void draw(ofxVectorGraphics &output, bool dselect){
            cout << "draw shape " <<  endl;
            if( points.size() > 0 ){
                
                int numPts = points.size();
                
                output.setColor(0x0088EE);
                if(selected){
                    output.setColor(0xF20606);

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
                if(dselect){
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
                    
                }

            }
            

        }
       
        
        vector<ofPoint> points;
        bool closed;
        bool selected;
        bool dselected;
        int selectedP;
        string type; 
        


};


#endif

