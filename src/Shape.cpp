//
//  Shape.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/6/13.
//
//

#include "Shape.h"

//register shape with base class
RegisterNodeModule< Shape > Shape::registerModule("Shape");

//default constructor
Shape::Shape(){
    
        closed = false;
        selected = false;
        selectedP = -1;
        parentSelected = false;
        childSelected = false;
        
        type="Shape";
}
//default deconstructor
Shape::~Shape(){
    
}


//copy constructor
Shape::Shape(const Shape &rhs){
    *this = rhs;
}
//Sets the equals operator, copies the data from the rhs instance to this instance
Shape& Shape::operator = (const Shape &rhs){
    if(this!= &rhs){
        copyBaseVariables( (Shape*)&rhs );
    }
    return *this;
}

//copies over base variables to new instances
bool Shape::copyBaseVariables(const Shape *shape){
    
    if( shape == NULL ){
        cout<<"shape is null, cannot copy base vars"<<endl;

        return false;
    }
    
    /*if( !this->copyBaseVariables( shape ) ){
        cout<<" shape copy failed"<<endl;

        return false;
    }*/
    
    
    this->closed = shape->closed;
    this->selected = shape->selected;
    this->selectedP = shape->selected;
    this->parentRelX = shape->parentRelX;
    this->parentRelY = shape->parentRelY;
    this->relX = shape->relY;
    this->relY = shape->relY;
    
    
    cout<<"shape copy base vars was successful"<<endl;
    bool success = Node::copyBaseVariables(shape);
    this->setParentChildRels();
    this->updateRelativeDist();
    return (success);
}


//update method
void Shape::Update(void)
{
    
    Node::Update(); // calls base class' function
    
}

bool Shape::updateRelativeDist(){
    if(this->GetParentNode()!=NULL){

        if(cPX != NULL && cPY!=NULL && pCX!=NULL && pCY!=NULL){
            parentRelX = *cPX - *pCX;
            parentRelY = *cPY - *pCY;
            return true;
        }
    }
    return false;
}

bool Shape::AddChildNode(Node* ChildNode){
    bool set= Node::AddChildNode(ChildNode);
    if(set){
        ((Shape*)ChildNode)->setParentChildRels();
        return ((Shape*)ChildNode)->updateRelativeDist();
       
    }
    else return false;


}

//method to set parametric relationship between parent and child
bool Shape::setParentChildRels(){
    if(this->GetParentNode()!=NULL){
        Shape* p = (Shape*)this->GetParentNode();
        
        pCX= &p->x2;
        pCY =&p->y2;
    
        cPX = &this->x1;
        cPY = &this->y1;
        return true;
    }
    return false;
}


//recursively deselects children (if any)
Shape* Shape::checkChildrenSelect(double x, double y){
    for (int i=0;i<m_Children.size();i++){
        if(((Shape*)m_Children[i])->checkSelect(x,y)!=NULL) return ((Shape*)m_Children[i])->checkSelect(x,y);
        
    }
    return NULL;
}

//recursively deselects children (if any)
int Shape::checkChildrenDSelect(double x, double y){
    for (int i=0;i<m_Children.size();i++){
        int k = ((Shape*)m_Children[i])->checkDSelect(x, y);
        if(k!=-1) return k;
    }
    return -1;
}
//deselects all objects (and children)
bool Shape::deselect(){
    selected = false;
    selectedP = -1;
    parentSelected = false;
    childSelected = false;
    deselectChildren();
}

//recursively deselects children (if any)
bool Shape::deselectChildren(){
    for (int i=0;i<m_Children.size();i++){
        ((Shape*)m_Children[i])->deselect();
        
    }
}

//recursively moves children  by point(if any)
bool Shape::moveChildrenPoint(double x, double y){
    for (int i=0;i<m_Children.size();i++){
        if(((Shape*)m_Children[i])->movePoint(x,y)) return true;
        
    }
    return false;
}

//recursively moves children (if any)
bool Shape::moveChildren(double x, double y){
    for (int i=0;i<m_Children.size();i++){
        if(((Shape*)m_Children[i])->move(x,y)) return true;
        
    }
    return false;
}

//recursively moves children (if any)
bool Shape::scaleChildren(double x, double y){
    for (int i=0;i<m_Children.size();i++){
        if(((Shape*)m_Children[i])->scale(x,y)) return true;
        
    }
    return false;
}




//sets color of shape to be drawn

void Shape::setColor(ofxVectorGraphics &output, int color){
    output.noFill();
    if(color==-1) output.setColor(Color_Const::deselected);
    else output.setColor(color);
    output.setLineWidth(Color_Const::regWeight);
    
    
    if(selected){
        output.setColor(Color_Const::selected);
        
    }
    else if(parentSelected){
        output.setColor(Color_Const::parent);
        output.setLineWidth(Color_Const::parentWeight);
    }
    else if(childSelected){
        output.setColor(Color_Const::child);
        output.setLineWidth(Color_Const::childWeight);
        
    }
    
}
bool Shape::drawChildren(ofxVectorGraphics &output, int color){
    for(int i=0;i<m_Children.size();i++){
        ((Shape*)m_Children[i])->draw(output, color);
        
    }
    return true;

}




