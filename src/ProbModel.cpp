//
//  ProbModel.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#include "ProbModel.h"

ProbModel::ProbModel(){
 
}

ProbModel::~ProbModel(){
    
}

bool ProbModel::clear(){
    for(int i=0;i<fnodes.size();i++){
        delete fnodes[i];
        fnodes[i]=NULL;
    }
    fnodes.clear();
    return true;
}

bool ProbModel::buildFeatureTree(vector<Shape*> drawing){
    clear();
    for(int i=0;i<drawing.size();i++){
         FeatureNode* f = new FeatureNode();
        f->createChildrenFromShape(drawing[i]);
         fnodes.push_back(f);
        cout<<"created a feature node at "<<i<<endl;

    }
    cout<<"completed building feature tree"<<endl;
}

bool ProbModel::populateFeatureTree(vector<vector<Shape*>> drawings){
    buildFeatureTree(drawings[0]);
    for(int i=0;i<drawings.size();i++){
        for(int j=0;j<drawings[i].size();j++){
            cout<<"adding shape features "<< i <<" to feature node "<<j<<endl;
            fnodes[j]->getShapeFeatures(drawings[i][j]);
            
        }
    }
    
}


vector<Shape*> ProbModel::generateDrawing(){
    
    vector<Shape*> drawing;
    if(fnodes.size()>0){
        for(int i=0;i<fnodes.size();i++){
            drawing.push_back(fnodes[i]->generateShape(NULL));
            cout<<"created a parent shape at "<<i<<endl;
        }
    }
    else{
        cout<<"tried to generate drawing, but feature tree was not built"<<endl;

    }
    return drawing;
}


