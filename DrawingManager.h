//
//  DrawingManager.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/12/13.
//
//

#ifndef evodraw1_DrawingManager_h
#define evodraw1_DrawingManager_h
    
#include <iostream>
#include "Shape.h"
#include "Ellipse.h"
#include "Line.h"
#include "Rectangle.h"
#include "ofxVectorGraphics.h"
    
#define DRAW_M 0
#define SELECT_M 1
#define DIRECT_M 2
#define ELLIPSE_M 3
#define RECT_M 4
#define LINE_M 5



class DrawingManager{
    
public:
    
    void mouseDrag(double x, double y){
        if (mode == DRAW_M) addPoint(x,y);
        else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M)sizeShape(x,y);
        else if (mode == SELECT_M) checkSelect(x,y,false);
        else if (mode == DIRECT_M) checkSelect(x,y,true);
    }
    
    void mouseMove(double x, double y){
        
    }
    
    void mouseDown(double x, double y){
        if (mode == DRAW_M) addPoint(x,y);
        else if (mode == SELECT_M) checkSelect(x,y,false);
        else if (mode == DIRECT_M) checkSelect(x,y,true);
        else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M) startShape(x,y);
         
    }
    
    void mouseUp(double x, double y){
        if (mode == DRAW_M) close();
         else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M)endShape(x,y);


    }
    
    
    void addPoint(double x, double y){
     int last = currentShapes.size()-1;
     if(last==-1||currentShapes[last]->closed){
     Shape* s = new Shape();
     currentShapes.push_back(s);
     }
     else {
     currentShapes[last]->addPoint(x,y);
     
     };
     
     }
    
    void checkSelect(double x, double y, bool dselect){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->checkSelect(x, y, dselect);
        };
    }
     
     void draw(ofxVectorGraphics &output){
         bool dselect = false;
         if (mode == SELECT_M ||mode == DIRECT_M ) dselect = true;
         
     for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->draw(output,dselect);
     }
     }
    
    
    //these methods control the creation of regular shapes
    
    void startShape(int x, int y){
        //cout << "start ellipse at " << x << " ," <<y << endl;
        Shape* s;
        switch (mode)
        {
            case ELLIPSE_M:
                s = new Ellipse(x,y);
                break;
            case LINE_M:
                s = new Line(x,y);
                break;
            case RECT_M:
                s = new Rectangle(x,y);
                break;
        }
        currentShapes.push_back(s);
        shapeStart = true;
        
    }
    
    void sizeShape(int x, int y){
       if(shapeStart){
           currentShapes[currentShapes.size()-1]->size(x,y);
       }

    }
    
    void endShape(int x, int y){
        if(shapeStart){
            shapeStart = false;
        }
  
    }
    
    void close(){
        if(currentShapes.size()>0){
            int last = currentShapes.size()-1;
            currentShapes[last]->closed=true;
        }
    }
    
    void deselectShapes(){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->deselect();
        }
    }

    
    void clearAll(){
        deleteShapes();
    }
    
    void clearLast(){
        delete(currentShapes[currentShapes.size()-1]);
        currentShapes[currentShapes.size()-1]=NULL;
        currentShapes.pop_back();
    }
    
    
    void drawMode(){
        mode = DRAW_M;
        deselectShapes();

    }
    
    void ellipseMode(){
        mode = ELLIPSE_M;
        deselectShapes();
       
    }
    void lineMode(){
        mode = LINE_M;
        deselectShapes();
        
    }
    
    void rectMode(){
        mode = RECT_M;
        deselectShapes();
        
    }
    
    void selectMode(){
        mode = SELECT_M;
        close();
        
    }
    
    void directMode(){
        mode = DIRECT_M;
        close();
    }
    
    void saveDrawing(){
        savedDrawings.push_back(currentShapes);
        currentShapes.clear();
    }
    
    void generateKeystone(vector<double>values){
        Shape* s = new Line(values[0],values[1]);
        s->size(values[2],values[3]);
        currentShapes.push_back(s);
    }
    
    void generateShapes(vector <vector <double> > values){
       
        vector<double> k = values[0];
        generateKeystone(k);
        vector<double> kc = Geom2D::getMidpoint(k[0],k[1],k[2],k[3]);
        for(int i=1;i<values.size();i++){
            double  x1 = kc[0]+values[i][0];
            double  y1= kc[1]+values[i][1];
            double x2= kc[0]+values[i][2];
            double y2= kc[1]+values[i][3];
            Shape* s = new Line(x1,y1);
            s->size(x2,y2);
            currentShapes.push_back(s);

        }
       
        
    }
    
    void deleteShapes(){
        for (int i=0;i<savedDrawings.size();i++){
            for(int j=0;j<savedDrawings[i].size();j++){
                delete(savedDrawings[i][j]);
                    savedDrawings[i][j]=NULL;
            }
        }
        savedDrawings.clear();

        for (int i=0;i<currentShapes.size();i++){
            delete(currentShapes[i]);
            currentShapes[i]=NULL;
        }
        currentShapes.clear();
    }

    vector<Shape*> currentShapes;
    vector<vector<Shape*>> savedDrawings;

    
     private:
    int mode;
    bool shapeStart;
};



#endif
