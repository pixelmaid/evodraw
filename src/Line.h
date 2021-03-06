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
#include "Node.h"

class Line: public Shape{
public:
    
    //default constructor
    Line();
    
    //constructor to intialize start point
    Line(double _x, double _y);
    
    //constructor to intialze both start and end points
    Line(double _x1, double _y1, double _x2, double _y2);
    
    //copy constructor
    Line(const Line &rhs);
    
    //equals operator
    Line& operator = (const Line &rhs);
    
    //default deconstructor
    virtual ~Line();
    
    //deep copy method
    virtual bool deepCopyFrom(const Node *node);
    
    //copies over base variables to new instances
    virtual bool copyBaseVariables(const Line *line);
    
    //update method
    virtual void Update(void);
    //virtual bool AddChildNode(Node* ChildNode);
    
    //method to reverse engineer constrained part based on shape generation.
    virtual bool calcConstrainedPoint();
    
    //virtual bool updateRelativeDist();
    
    
    //geom functions //
    
    //returns centroid
    virtual vector<double>centroid();

    //returns bounding box as a vector (x,y,width,height)
    virtual vector<double>boundingbox();
    
    //returns start and end points as a vector of 4 values
    virtual vector<double> getParams();
    
    //sizes line based on new coordinates (used for user drawing)
    virtual bool size(double _x, double _y);

    //selection functions //
    
    //checks to see if line has been selected
    virtual Shape* checkSelect(double px, double py);
    
    //checks to see if point has been directly selected
    virtual int checkDSelect(double _x, double _y);
    
    //transformation functions//
    
    //scale method (right now there is no scaling for lines)
    virtual bool scale(double _x, double _y){  return Shape::scale(_x,_y);};
    
    //move function
    virtual bool move(double px, double py);
    
    //move indivdual point function
    virtual bool movePoint(double _x, double _y);
    
    
    //line draw function
    virtual bool draw(ofxVectorGraphics &output, int color);
    
    
protected:
    
    //Module to register type with base class
    static RegisterNodeModule< Line > registerModule;
    
    
private:
    
};



#endif
