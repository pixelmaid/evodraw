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
class ProbModel{

public:
    
    bool analyzeDrawing(vector<Shape*> &shapes);
    
    //stores values for drawing
    vector<int> dType;
    //stores probabilities for lookup table
    vector<vector<double>> lookup;
    
private:
    
};



#endif /* defined(__evodraw1__ProbModel__) */
