//
//  Shape.h
/* base class for all geometric data structures. Should never be directly initialized*/
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
    Shape();
    Shape(const Shape &rhs);
    Shape& operator = (const Shape &rhs);
    virtual ~Shape();
    
    virtual bool deepCopyFrom(const Node *node){ cout<< "shape deep copy attempt"<<endl; return Node::deepCopyFrom(node); }

    //copies over base variables to new instances
    virtual bool copyBaseVariables(const Shape *shape);
    
    // Update method
    virtual void Update(void);
    
    //method to update relative distance to parent
    virtual bool updateRelativeDist();
    
    //method to set parametric relationship between parent and child
    bool setParentChildRels();
    
    // add child node method
    virtual bool AddChildNode(Node* ChildNode);
    
    //geom functions//
    
    //calculates centroid
    virtual vector<double>centroid(){return vector<double>();};
    //returns bounding box as a vector (x,y,width,height)
    virtual vector<double>boundingbox(){return vector<double>();};
    //returns vector containing x1,x2,w,h (empty for shape at the moment)
    
    //virtual function for sizing shape based on user drawing methods
    virtual bool size(double _x, double _y){return false;}
    
    //virtual functions for accessing basic parameters of a shape
    virtual vector<double> getParams(){return vector<double>();};

    //selection functions//
    
    //virtual function for checking selection- always returns false
    virtual Shape* checkSelect(double x, double y){return checkChildrenSelect(x,y);}
    // function for recursively checking children
   Shape* checkChildrenSelect(double x, double y);
    //virtual function for checking direct selection - always returns -1
    virtual int checkDSelect(double x, double y){return checkChildrenDSelect(x,y);}
    // function for recursively checking children
    int checkChildrenDSelect(double x, double y);
    
    //deselects all elements
    bool deselect();
    bool deselectChildren();

    
    //transformation functions//
    
    //virtual function for moving point - always returns false
    virtual bool movePoint(double x, double y){return moveChildrenPoint(x,y);};
    virtual bool moveChildrenPoint(double x, double y);
    //virtual function for moving shape - returns false
    virtual bool move(double x, double y){return moveChildren(x,y);};
    virtual bool moveChildren(double x, double y);
    //virtual function for scaling shape- returns false
    virtual bool scale(double x, double y){return scaleChildren(x,y);};
    virtual bool scaleChildren(double x, double y);
    
    
    //appearance functions//
    
    //sets color of shape to be drawn
    void setColor(ofxVectorGraphics &output, int color);
    
    //draw functions//
    
    //virtual function to draw shape, returns false
    virtual bool draw(ofxVectorGraphics &output, int color = -1){return false;};
    bool drawChildren(ofxVectorGraphics &output, int color =-1);
    
    //boolean to indicate selection
    bool selected;
    //int to indicate direct selection point
    int selectedP;
    //boolean to indicate if object is selected as parent
    bool parentSelected;
    // boolean to indicate if object is selected as child
    bool childSelected;	
    
    
   protected:
    //whether shape is open or closed (consider removing?)
    bool closed;
    //double for x for relative selection point
    double relX;
    //double for y relative selection point
    double relY;
    
    double cX;
    double cY;
    double x1;
    double x2;
    double y1;
    double y2;
    
    //pointer to double for correctly updating parent 
    double parentRelX;
    double parentRelY;
    //pointer to doubles for correctly calculating relative distance between shape and parent
    double* cPX;
    double* cPY;
    double* pCX;
    double* pCY;
    
    //Module for registering with base class
    static RegisterNodeModule< Shape > registerModule;



};


#endif

