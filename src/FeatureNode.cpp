//
//  FeatureNode.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/12/13.
//
//

#include "FeatureNode.h"

//stores feature values of a given shape
bool FeatureNode::getShapeFeatures(Shape* s){
    
    x1.push_back(s->x1);
    y1.push_back(s->y1);
    x2.push_back(s->x2);
    y2.push_back(s->y2);
    
    parentRelX.push_back(s->parentRelX);
    parentRelY.push_back(s->parentRelY);
    weights.push_back(s->weight);
    type.push_back(typeCheck(s->type));
                    
}

//calculates normalized mean and standard deviation for each group of features;
bool FeatureNode::calculateMeanStd(){
    vector<double> nweights = Geom2D::normalize(weights);
    
    vector<double>x1ms = indMeanSD(x1,nweights);
    x1M = x1ms[0];
    x1Std = x1ms[1];
    
    vector<double>x2ms = indMeanSD(x2,nweights);
    x2M = x2ms[0];
    x2Std = x2ms[1];
    
    vector<double>y1ms = indMeanSD(y1,nweights);
    y1M = y1ms[0];
    y1Std = y1ms[1];
    
    vector<double>y2ms = indMeanSD(y2,nweights);
    y2M = y2ms[0];
    y2Std = y2ms[1];
    
    vector<double>pXms = indMeanSD(parentRelX,nweights);
    pXM = pXms[0];
    pXStd = pXms[1];
    
    vector<double>pYms = indMeanSD(parentRelY,nweights);
    pYM = pYms[0];
    pYStd = pYms[1];
}

//assumes weights have already been normalized
vector<double> FeatureNode::indMeanSD(vector<double> values, vector<double> weights){
    double mean = Geom2D::weightedMean(values,weights);
    double sd = Geom2D::standardDev(values, mean);
    vector<double> results;
    results.push_back(mean);
    results.push_back(sd);
    return results;
    
}
//returns int based on type string
int FeatureNode::typeCheck(string t){
    if(t=="Line"){
        return 0;
    }
    else if(t=="Rectangle"){
        return 1;
    }
    else if(t=="Ellipse"){
        return 2;
    }
    else{
        return -1;
    }

}