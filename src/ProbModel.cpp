//
//  ProbModel.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#include "ProbModel.h"

ProbModel::ProbModel(){
    treeBuilt = false;
}

ProbModel::~ProbModel(){
    clear();
}

bool ProbModel::clear(){
    for(int i=0;i<fnodes.size();i++){
        delete fnodes[i];
        fnodes[i]=NULL;
    }
    fnodes.clear();
    treeBuilt = false;
    return true;
}

bool ProbModel::buildFeatureTree(vector<Shape*> &drawing){
    clear();
    for(int i=0;i<drawing.size();i++){
         FeatureNode* f = new FeatureNode();
        f->createChildrenFromShape(drawing[i]);
         fnodes.push_back(f);
        cout<<"created a feature node at "<<i<<endl;

    }
    cout<<"completed building feature tree"<<endl;
}
//recursively clears data from nodes

bool ProbModel::clearNodeData(){
    for(int i=0;i<fnodes.size();i++){
        fnodes[i]->clearNodeData();
    }
}

bool ProbModel::populateFeatureTree(vector<vector<Shape*>> &drawings){
   //if(!treeBuilt)buildFeatureTree(drawings[0]);
   // clearNodeData();
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
         Shape* gShape = fnodes[i]->generateShape(NULL);
            
          // Shape*  gShape = new Line(100,100);
            //gShape->size(200,200);
            if(NULL==gShape) cout<<"gshape is NULL yo!"<<endl;
            else{
               /* Shape* nshape = (Shape*)(gShape->createNewInstance());
                delete nshape;
                nshape = NULL;
                delete gShape;
                gShape = NULL;*/
                drawing.push_back(gShape);
                cout<<"created a parent shape at "<<i<<endl;
            }
            
        }
    }
    else{
        cout<<"tried to generate drawing, but feature tree was not built"<<endl;

    }
    return drawing;
}


