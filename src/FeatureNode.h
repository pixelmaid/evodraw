//
//  FeatureNode.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/12/13.
//
//

#ifndef __evodraw1__FeatureNode__
#define __evodraw1__FeatureNode__

#include <iostream>
#include "Node.h"
#include "Shape.h"
#include "Geom2D.h"
#include "Line.h"
#include "Ellipse.h"
#include <math.h>
class FeatureNode: public Node{
public:
    
    FeatureNode();
    
    virtual ~FeatureNode();
    bool clear();
    
    FeatureNode(const FeatureNode &rhs);
    FeatureNode& operator = (const FeatureNode &rhs);
    
    
    virtual bool deepCopyFrom(const Node *node);
    
    virtual bool copyBaseVariables(const Node *node);
    
    bool createChildrenFromShape(Shape* s);
    
    //recursively clears data from nodes
    bool clearNodeData();
    
    //stores all the features of the shape passed to the function
    bool getShapeFeatures(Shape* s);
    //calculates new values for the mean and standard dev based on current feature values
    bool calculateMeanStd();
    
    //generatively creates a new shape based on a parent shape
    Shape* generateShape(Shape* parent);
    
    
    
protected:
    //returns an int based on type value
    int typeCheck(string t);
    
    vector<double> indMeanSD(vector<double> values, vector<double> weights);
    
private:
    //vectors for storing features and weights
    vector<double> x1;
    //vector<double> x1Weight;

    vector<double> y1;
    //vector<double> y1Weight;

    vector<double> x2;
    //vector<double> x2Weight;
    
    vector<double> y2;
    //vector<double> y2Weight;
    
    //type of node
    vector <double> types;
    
    //relative distance between shape and parent
    vector<double> parentRelX;
    vector<double> parentRelY;
    
    vector<double> weights;
    
    //means and stand. dev for features
    double x1M;
    double x1Std;
    double x2M;
    double x2Std;
    double y1M;
    double y1Std;
    double y2M;
    double y2Std;
    double pXM;
    double pXStd;
    double pYM;
    double pYStd;
    double tM;
    double tStd;
    
    //random generator for gaussian
    GRT::Random random;
    
    //Module for registering with base class
    static RegisterNodeModule< FeatureNode > registerModule;


    //other features you might need eventually
    /*
    vector<double> angle;
    vector<double> centroidX;
    vector<double> centroidY;
    vector<double> wR;
    vector<double> hR;*/
    
    
};


#endif /* defined(__evodraw1__FeatureNode__) */
