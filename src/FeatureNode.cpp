//
//  FeatureNode.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/12/13.
//
//

#include "FeatureNode.h"

//register feature node with base class
RegisterNodeModule< FeatureNode > FeatureNode::registerModule("FeatureNode");


FeatureNode::FeatureNode(){
    x1M =0;
    x1Std = 0;
    x2M=0;
    x2Std=0;
    y1M=0;
    y1Std=0;
    y2M=0;
    y2Std=0;
    pXM=0;
    pXStd=0;
    pYM=0;
    pYStd=0;
    type="FeatureNode";

}

FeatureNode::~FeatureNode(){
    clear();
    for(int i=0;i<m_Children.size();i++){
        m_Children[i]->clear();
        delete m_Children[i];
        m_Children[i]=NULL;
    }

    m_Children.clear();
}

bool FeatureNode::clear(){
    x1M =0;
    x1Std = 0;
    x2M=0;
    x2Std=0;
    y1M=0;
    y1Std=0;
    y2M=0;
    y2Std=0;
    pXM=0;
    pXStd=0;
    pYM=0;
    pYStd=0;
    this->types.clear();
    this->x1.clear();
    this->x2.clear();
    this->y1.clear();
    this->y2.clear();
    this->parentRelX.clear();
    this->parentRelY.clear();
    return true;
}

FeatureNode::FeatureNode(const FeatureNode &rhs){
    *this = rhs;
}

FeatureNode& FeatureNode:: operator = (const FeatureNode &rhs){
    if(this!= &rhs){
        if(copyBaseVariables((FeatureNode*)&rhs))return *this;
    }
    return *this;

}

//deep copy method
bool FeatureNode::deepCopyFrom(const Node *node){
    cout<<"feature node deep copy attempt"<<endl;
    
    
    if( node == NULL ){
        cout<<"feature not deep copied because node = NULL"<<endl;
        return false;
        
    }
    //cout<<"this type="<<this->getType()<<endl;
    //cout<<"node type="<<node->getType()<<endl;
    if( this->getType() == node->getType() ){
        //Clone the values and return
        cout<<"feature deep copy success"<<endl;
        if( copyBaseVariables( (FeatureNode*)node ) && Node::deepCopyFrom(node)) return true;
        else return false;
    }
    else{
        cout<<"feature node not deep copied because of type mismatch"<<endl;
        
    }
    return false;
}


bool FeatureNode::copyBaseVariables(const Node *node){
    if( node == NULL ){
               return false;
    }
    
    
    FeatureNode* fNode = (FeatureNode*) node;
    this->x1M =fNode->x1M;
    this->x1Std = fNode->x1Std;
    this->x2M=fNode->x2M;
    this->x2Std=fNode->x2M;
    this->y1M=fNode->y1M;
    this->y1Std=fNode->y1Std;
    this->y2M=fNode->y2M;
    this->y2Std=fNode->y2Std;
    this->pXM=fNode->pXM;
    this->pXStd=fNode->pXStd;
    this->pYM=fNode->pYM;
    this->pYStd=fNode->pYStd;
    this->types = fNode->types;
    this->x1= fNode->x1;
    this->x2 = fNode->x2;
    this->y1 = fNode->y1;
    this->y2 = fNode->y2;
    this->parentRelX = fNode->parentRelX;
    this->parentRelY = fNode->parentRelY;
    
    bool success = Node::copyBaseVariables(node);
    return (success);
}


bool FeatureNode::clearNodeData(){
    this->x1M =0;
    this->x1Std = 0;
    this->x2M=0;
    this->x2Std=0;
    this->y1M=0;
    this->y1Std=0;
    this->y2M=0;
    this->y2Std=0;
    this->pXM=0;
    this->pXStd=0;
    this->pYM=0;
    this->pYStd=0;
    this->types.clear();
    this->x1.clear();
    this->x2.clear();
    this->y1.clear();
    this->y2.clear();
    this->parentRelX.clear();
    this->parentRelY.clear();
    /*for(int i=0;i<m_Children.size();i++){
        ((FeatureNode*)m_Children[i])->clearNodeData();
    }*/
    
}
//recursive function to build feature tree- called by probmodel
bool FeatureNode::createChildrenFromShape(Shape* s){
    cout<<"trying to create children from shape "<<endl;
    cout<<"num children= "<<s->m_Children.size()<<endl;

    for(int i=0;i<s->m_Children.size();i++){
        FeatureNode* f = new FeatureNode();
        this->AddChildNode(f);
        f->createChildrenFromShape((Shape*)s->m_Children[i]);
        cout<<"created a feature child node at "<<i<<endl;
        
    }
    return true;
}

//stores feature values of a given shape recursively
bool FeatureNode::getShapeFeatures(Shape* s){
    
    cout<<"shape = null: "<<s<<endl;
    x1.push_back(s->x1);
    y1.push_back(s->y1);
    x2.push_back(s->x2);
    y2.push_back(s->y2);
    
    parentRelX.push_back(s->parentRelX);
    parentRelY.push_back(s->parentRelY);
    weights.push_back(s->weight);
    types.push_back(typeCheck(s->type));
    
    
    cout<<"x1="<<s->x1<<", y1="<<s->y1<<", x2="<<s->x2<<", y2="<<s->y2<<", pRx="<<s->parentRelX<<", pRy="<<s->parentRelY<<endl;
    cout<<"type="<<s->type<<endl;
    
    for(int i=0;i<s->m_Children.size();i++){
        cout<<"trying to add shape features at child "<<i<<endl;
        cout<<"x1="<<((Shape*)m_Children[i])->x1<<", y1="<<((Shape*)m_Children[i])->y1<<", x2="<<((Shape*)m_Children[i])->x2<<", y2="<<((Shape*)m_Children[i])->y2<<", pRx="<<((Shape*)m_Children[i])->parentRelX<<", pRy="<<((Shape*)m_Children[i])->parentRelY<<endl;

         ((FeatureNode*)this->m_Children[i])->getShapeFeatures((Shape*)s->m_Children[i]);
    }
                    
}

//calculates normalized mean and standard deviation for each group of features;
bool FeatureNode::calculateMeanStd(){
    
    cout<<"weights are:"<<endl;
    for(int i=0;i<weights.size();i++){
        cout<<i<<"="<<weights[i]<<endl;
    }
    vector<double> nweights = Geom2D::normalize(weights);
    cout<<"normalized weights are:"<<endl;
    for(int i=0;i<nweights.size();i++){
        cout<<i<<"="<<nweights[i]<<endl;
    }
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
    
    vector<double>tms = indMeanSD(types,nweights);
    tM = tms[0];
    tStd = tms[1];
}

Shape* FeatureNode::generateShape(Shape *parent){
    calculateMeanStd();
    double _x1 = random.getRandomNumberGauss(x1M,x1Std);
    double _x2 = random.getRandomNumberGauss(x2M,x2Std);
    double _y1 =  random.getRandomNumberGauss(y1M,y1Std);
    double _y2 =  random.getRandomNumberGauss(y2M,y2Std);
    double _parentRelX =  random.getRandomNumberGauss(pXM,pXStd);
    double _parentRelY =  random.getRandomNumberGauss(pYM,pYStd);
    int _type = round(tM);
    cout<<"_x1="<<_x1<<"_y1="<<_y1<<"_x2="<<_x2<<"_y2="<<_y2<<"_pRx="<<_parentRelX<<"_pRy="<<_parentRelY<<"_type="<<_type<<endl;

    Shape* s;
    cout<<"attempting to generate shape"<<endl;

    if(parent == NULL){
        if(_type == 1) s = new Ellipse(_x2,_y2,_x1,_y1);
        else{
            s = new Line(_x1,_y1);
            s->size(_x2,_y2);
        }

        cout<<"no parent, created new shape"<<endl;
    }
    else{
        if(_type == 1) s = new Ellipse(_x2,_y2,_x1,_y1);
        else{
            s = new Line(_x1,_y1);
            s->size(_x2,_y2);
        }

        parent->AddChildNode(s);
           s->parentRelX = _parentRelX;
            s->parentRelY = _parentRelY;
            s->calcConstrainedPoint();
            s->x2= _x2;
            s->y2= _y2;
        
            cout<<"child generated shape parented succesfully"<<endl;
    }
        for(int i=0;i<this->m_Children.size();i++){
            cout<<"generating shape at child "<<i<<endl;

                ((FeatureNode*)m_Children[i])->generateShape(s);
            }
            return s;
            
        
        
                
        
        
        
    
    //cout<<"child generated shape parent failed"<<endl;
   // return NULL;
}

//assumes weights have already been normalized
vector<double> FeatureNode::indMeanSD(vector<double> values, vector<double> weights){
    double mean = Geom2D::weightedMean(values,weights);
    double sd = Geom2D::standardDev(values, mean);
    if(sd != sd) sd=1;
    vector<double> results;
    results.push_back(mean);
    results.push_back(sd);
    cout<<"mean="<<mean<<", sd="<<sd<<endl;

    return results;
    
}
//returns int based on type string
int FeatureNode::typeCheck(string t){
    if(t=="Line"){
        return 0;
    }
    else if(t=="Rectangle"){
        return 2;
    }
    else if(t=="Ellipse"){
        return 1;
    }
    else{
        return -1;
    }

}