//
//  ProbModel.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#include "ProbModel.h"

ProbModel::ProbModel(){
    //total number of shapes in a drawing
    shapeNum=3;
    //total number of shapes in drawing minus keystone
    nonKNum = shapeNum-1;
    keystoneFeatureNum=4;
}

ProbModel::~ProbModel(){
    
}

bool ProbModel::evalKeystone(vector< vector<Shape*> > &drawings){
    cout << "total # of drawings = "<<drawings.size()<<endl;
    vector< vector<double> > keystoneFeatures;
    for(int i=0;i<keystoneFeatureNum;i++){
        vector<double> v;
        for(int j=0;j<drawings.size();j++){
            //assume that keystone is always first shape in drawing array
            vector<double> params = drawings[j][0]->getParams();
            cout << "param at "<<i<<"="<<params[i]<<endl;
            v.push_back(params[i]);
        }

        
        keystoneFeatures.push_back(v);
        vector<double>ms = Geom2D::meanSd(v,false);
        keystoneValues.push_back(ms[0]);
        keystoneValues.push_back(ms[1]);
    
    }
    if(drawings[0][0]->type=="ellipse") keystoneValues.push_back(0);
    else if(drawings[0][0]->type=="rect") keystoneValues.push_back(1);
    else if(drawings[0][0]->type=="line") keystoneValues.push_back(2);

    cout << "evaluated keystone!"<<endl;

    return true;

}

vector <double> ProbModel::generateKeystoneValues(){
    cout << "generating gaussian values:"<<endl;

    vector<double>gKeystone;
    for(int i=0;i<keystoneFeatureNum*2;i+=2){
        double v =  random.getRandomNumberGauss(keystoneValues[i],keystoneValues[i+1]);
        cout << "gaussian v="<<v<<endl;
        gKeystone.push_back(v);
    }
    gKeystone.push_back(keystoneValues[keystoneValues.size()-1]);
    return gKeystone;
    
}

vector <vector <double> > ProbModel::generateShapeValues(){
    cout << "generating shape gaussian values:"<<endl;
    
     vector <vector <double> >gShapes;
    for(int i=0;i<lookup.size();i++){
        vector<double> gShape;
        for(int j=0;j<lookup[i].size();j+=2){
            double v =  random.getRandomNumberGauss(lookup[i][j],lookup[i][j+1]);
            cout << "gaussian v="<<v<<endl;
            gShape.push_back(v);
        }
        gShape[gShape.size()-1]=lookup[i][lookup[i].size()-2];
        cout << "gaussian v="<<gShape[gShape.size()-1]<<endl;

        cout << "\n=================\n"<<endl;
        gShapes.push_back(gShape);
    }
    
    return gShapes;
}


bool ProbModel::evalRelativeDrawing(vector<double> keystoneV,vector< vector<Shape*> > &drawings)   {
       
vector<double> kc = Geom2D::getMidpoint(keystoneV[0], keystoneV[1], keystoneV[2], keystoneV[3]);
   double kw = abs(keystoneV[0]-keystoneV[2]);
    double kh = abs(keystoneV[1]-keystoneV[3]);
    for( int i =1; i<shapeNum;i++){
        vector<double> x1diff;
        vector<double> y1diff;
        vector<double> x2diff;
        vector<double> y2diff;
        vector<double> angle;
        vector<double> centroidX;
        vector<double> centroidY;
        vector<double> wR;
        vector<double> hR;
        vector<double> type;
      
        vector< vector<double> > ssF;
        for(int j=0;j<drawings.size();j++){
            vector<double> params = drawings[j][i]->getParams();
            vector<double> centroid = drawings[j][i]->centroid();
            vector<double> bb = drawings[j][i]->boundingbox();
            x1diff.push_back(kc[0]-params[0]);
            y1diff.push_back(kc[1]-params[1]);
            x2diff.push_back(kc[0]-params[2]);
            y2diff.push_back(kc[1]-params[3]);
            angle.push_back(Geom2D::angle(kc[0],kc[1],centroid[0],centroid[1]));
            centroidX.push_back(centroid[0]);
            centroidY.push_back(centroid[1]);
            wR.push_back(bb[2]/kw);
            hR.push_back(bb[3]/kh);
            if(drawings[j][i]->type=="ellipse") type.push_back(0);
            else if(drawings[j][i]->type=="rect") type.push_back(1);
            else if(drawings[j][i]->type=="line") type.push_back(2);
        }
        ssF.push_back(x1diff);
        ssF.push_back(y1diff);
        ssF.push_back(x2diff);
        ssF.push_back(y2diff);
        ssF.push_back(angle);
        ssF.push_back(centroidX);
        ssF.push_back(centroidY);
        ssF.push_back(wR);
        ssF.push_back(hR);
        ssF.push_back(type);
        
        vector<double> shapefeatures;
        for(int k=0;k<ssF.size();k++){
            vector<double>ms = Geom2D::meanSd(ssF[k],false);
            shapefeatures.push_back(ms[0]);
            shapefeatures.push_back(ms[1]);
            cout << "mean and sd for shape:"<<ms[0]<<","<<ms[1]<<endl;

        }
        cout << "shapeFeatures size:"<<shapefeatures.size()<<endl;
        cout << "\n=================\n"<<endl;
        lookup.push_back(shapefeatures);
       /*
         vector<double>y1diffms = Geom2D::meanSd(y1diff,true);
         vector<double>x2diffms = Geom2D::meanSd(x2diff,true);
         vector<double>y2diffms = Geom2D::meanSd(y2diff,true);
        vector<double>anglems = Geom2D::meanSd(angle,true);
         vector<double>centroidXms = Geom2D::meanSd(centroidX,true);
         vector<double>centroidYms = Geom2D::meanSd(centroidY,true);
         vector<double>wRms = Geom2D::meanSd(wR,true);
         vector<double>hRms = Geom2D::meanSd(hR,true);
        vector<double>typems = Geom2D::meanSd(type,true);*/
               
    }
    
    
    return true;
    
    

}


vector <vector <double> > ProbModel::analyzeDrawing(vector <vector <Shape*> > &drawings){
    lookup.clear();
    keystoneValues.clear();
    shapeNum=drawings[0].size();
    //total number of shapes in drawing minus keystone
    nonKNum = shapeNum-1;

    evalKeystone(drawings);
    vector<double> ksv =generateKeystoneValues();
    evalRelativeDrawing(ksv, drawings);
    vector <vector <double> > sv = generateShapeValues();
    sv.insert(sv.begin(),ksv);
    return sv;
}



/*

bool ProbModel::analyzeDrawing(vector<Shape*> &drawings){
   
    lookup.clear();

    
    for(int i=0;i<drawings.size();i++){
        
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
        
         vector<double>ci =drawings[i]->centroid();
        
        for(int j=0;j<drawing.size();j++){
            if(j!=i){
               
                vector<double>cj = drawing[j]->centroid();
                double xd = abs(ci[0]-cj[0]);
                xdist.push_back(xd);
                double yd = abs(ci[1]-cj[1]);
                ydist.push_back(yd);
                
                cAngle.push_back(Geom2D::angle(ci[0],ci[1],cj[0],cj[1]));
                
                vector<double>bb_i = drawing[i]->boundingbox();
                vector<double> bb_j = drawing[i]->boundingbox();
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
}*/