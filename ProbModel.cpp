//
//  ProbModel.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#include "ProbModel.h"
bool ProbModel::analyzeDrawing(vector<Shape*> &shapes){
   
    lookup.clear();

    
    for(int i=0;i<shapes.size();i++){
        
        //x distance between origin of selected shape(centroid) and other shape centroid
        vector<double> xdist;
        //y distance between origin of selected shape(centroid) and other shape centroid
        vector<double> ydist;
        //angle between centroids
        vector<double> cAngle;
        //ratio of size between bounding box
        vector<double> sR;
        //probability that user draws shape first
        vector<double> first;
        //probability of where shape is drawn in the screen (x)
        vector<double> sX;
        //probability of where shape is drawn in the screen (y)
        vector<double> sY;
        //type of shape
        vector<double> type;
        
         vector<double>ci = shapes[i]->centroid();
        for(int j=0;j<shapes.size();j++){
            if(j!=i){
               
                vector<double>cj = shapes[j]->centroid();
                double xd = abs(ci[0]-cj[0]);
                xdist.push_back(xd);
                double yd = abs(ci[1]-cj[1]);
                ydist.push_back(yd);
                
                cAngle.push_back(Geom2D::angle(ci[0],ci[1],cj[0],cj[1]));
                
                vector<double>bb_i = shapes[i]->boundingbox();
                vector<double> bb_j = shapes[i]->boundingbox();
                double a_i=bb_i[2]*bb_i[3];
                double a_j=bb_j[2]*bb_j[3];
                sR.push_back(a_i/a_j);
                
                
            }

        }
        //here is where I calculate mean / sd?
        vector<double>features;
        vector<double> xdist_ms = Geom2D::meanSd(xdist);
        features.push_back(xdist_ms[0]);
        features.push_back(xdist_ms[1]);
        
        vector<double> ydist_ms = Geom2D::meanSd(ydist);
        features.push_back(ydist_ms[0]);
        features.push_back(ydist_ms[1]);
        
        vector<double> cAngle_ms = Geom2D::meanSd(cAngle);
        features.push_back(cAngle_ms[0]);
        features.push_back(cAngle_ms[1]);

        vector<double> sR_ms = Geom2D::meanSd(sR);
        features.push_back(sR_ms[0]);
        features.push_back(sR_ms[1]);
        
        if(i==0) features.push_back(1);
        else features.push_back(0);
        
        features.push_back(ci[0]);
        features.push_back(ci[1]);
        
        if(shapes[i]->type=="ellipse") features.push_back(0);
        else if(shapes[i]->type=="rect") features.push_back(1);
        else if(shapes[i]->type=="line") features.push_back(2);
        
        lookup.push_back(features);
        std::cout << "features=" << features[0] <<","<< features[1] <<","<<features[2] <<","<<features[3] <<std::endl;
        
    }
    
    return true;
}