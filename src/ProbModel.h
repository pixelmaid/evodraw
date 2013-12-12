//
//  ProbModel.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#ifndef __evodraw1__ProbModel__
#define __evodraw1__ProbModel__

#include <iostream>
#include "ofMain.h"
#include "Shape.h"
#include "Geom2D.h"
#include <math.h>
#include "GRT.h"
#include "FeatureNode.h"
class ProbModel{

public:
    
    ProbModel();
    
    ~ProbModel();
    
    bool clear();
        
    vector<Shape*> generateDrawing();
    
    //builds the intial feature tree
    bool buildFeatureTree(vector<Shape*> drawing);
  
    
    //populates feature tree with values across all drawings
    bool populateFeatureTree(vector<vector<Shape*>>drawings);
    
    FeatureNode* recurseTree(FeatureNode* pN, Shape* pS, int pos);
    
private:
    //vector of feature trees for storing features of drawings
    vector<FeatureNode*> fnodes;
    //records number of shapes in the drawing for error checking purposes.
    int shapeNum;
};



#endif /* defined(__evodraw1__ProbModel__) */
