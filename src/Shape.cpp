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
    cout<<"shape copy base vars was successful"<<endl;
    return Node::copyBaseVariables(shape);
    
}


//update method
void Shape::Update(void)
{
    Node::Update(); // calls base class' function
}


bool Shape::deselect(){
    selected = false;
    selectedP = -1;
    parentSelected = false;
    childSelected = false;
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




