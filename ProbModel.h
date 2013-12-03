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
class ProbModel{

public:
    
    ProbModel();
    
    ~ProbModel();
    
    bool evalKeystone(vector< vector<Shape*> > &drawings);
    vector <double> generateKeystoneValues();
    vector <vector <double> > generateShapeValues();
    bool evalRelativeDrawing(vector<double> keystoneV,vector< vector<Shape*> > &drawings);
    
    vector <vector <double> >   analyzeDrawing(vector <vector <Shape*> > &drawings);
    
    //stores average features for keystone
    vector <double> keystoneValues;
    
    //total number of shapes in a drawing
    int shapeNum;
    //total number of shapes in drawing minus keystone
    int nonKNum;
    //number of features in the keystone
    int keystoneFeatureNum;
    
    GRT::Random random;
    
    //stores probabilities for lookup table
    vector< vector< double > > lookup;
    
    //stores values for drawing
    vector<int> dType;
        
private:
    
};



#endif /* defined(__evodraw1__ProbModel__) */
