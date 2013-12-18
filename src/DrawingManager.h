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
#include "Line.h"
#include "Rectangle.h"
#include "ofxVectorGraphics.h"
#include "ofMain.h"
#include "Color_Const.h"
#include "Ellipse.h"
#include "FeatureNode.h"
    
#define DRAW_M 0
#define SELECT_M 1
#define DIRECT_M 2
#define ELLIPSE_M 3
#define RECT_M 4
#define LINE_M 5
#define SCALE_M 6
#define PARENT_M 7



class DrawingManager{
    
public:
    
    DrawingManager();
    
    ~DrawingManager();
    
   
    //model methods
     void generateDrawing();
    //builds the intial feature tree
    bool buildFeatureTree();
    //populates feature tree with values across all drawings
    bool populateFeatureTree();
    bool clearNodeData();
    
    //cleanup methods
    bool clearModel();
    void clearAll();
    void clearLast();
    //clears last drawing on canvas, or last in stack of saved drawings
    void clearLastSaved();
    
    void deleteShapes();
    
    //mouse event detection
    void mouseDrag(double x, double y);
    
    void mouseMove(double x, double y){}
    
    void mouseDown(double x, double y);    
    
    void mouseUp(double x, double y);
    
    //mode toggles
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
    
    void parentMode(){
        mode = PARENT_M;
        deselectShapes();
        
    }
    
    void selectMode(){
        mode = SELECT_M;
        deselectShapes();
        
        //close();
        
    }
    
    void directMode(){
        mode = DIRECT_M;
        deselectShapes();
        
        //close();
    }
    
    void scaleMode(){
        mode = SCALE_M;
        deselectShapes();
        
        //close();
    }
    
    //selection detection
    void checkSelect(double x, double y);
    void checkDSelect(double x, double y);
    void checkMove(double x, double y);
    void checkDMove(double x, double y);
    void checkScale(double x, double y);
    void deselectShapes();
    
    //these methods control the creation of regular shapes
    void startShape(int x, int y);
    void sizeShape(int x, int y);
    void endShape(int x, int y);
    void close();
    
    //drawing
    void draw(ofxVectorGraphics &output, bool history);
    
    unsigned long createRGB(int r, int g, int b)
    {
        return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    }
    
    //parent child handling
    void parent(double x, double y);
    bool removeChild(Shape* c);
    
    //saving, adding and copying (the troublemakers)
    void saveDrawing(double w);
    void setWeight(double w);
    double getWeight();
    bool switchDrawing(int num, double weight);
    vector<Shape*> copy(vector<Shape*>toCopy);
    Shape* setShape(const Shape* shape);
    
    
    vector< Shape* > *currentShapes = NULL; 
    vector<vector<Shape*>> savedDrawings;
    vector<double> weights;
    
     private:
    int mode;
    int dP; //position for current drawing
    bool shapeStart;
    Shape* _parent;
    bool treeBuilt;
    //controls if user is looking at indexed drawing or current drawing
    bool indexed;
    
    //vector of feature trees for storing features of drawings
    vector<FeatureNode*> fnodes;
};



#endif
