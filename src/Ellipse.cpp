//
//  Ellipse.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/13/13.
//
//

#include "Ellipse.h"

//register line with base class
RegisterNodeModule< Ellipse > Ellipse::registerModule("Ellipse");

//default constructor
Ellipse::Ellipse(){
    Shape::Shape();
    type = "Ellipse";
    
}

Ellipse::Ellipse(double _x, double _y){
    closed=false;
    selected = false;
    selectedP = -1;
    x1=0;
    y1=0;
    x2 = _x;
    y2 = _y;
    type = "Ellipse";
}

//constructor to intialze both start and end points
Ellipse::Ellipse(double _x1, double _y1, double _x2, double _y2){
    x2 = _x1;
    y2 = _y1;
    x1 = _x2;
    y1 = _y2;
    Ellipse();
    type = "Ellipse";
    //cout<<"line type="<<this->getType()<<endl;
    
    
}

Ellipse::~Ellipse(){
    
    
    
}

Ellipse::Ellipse(const Ellipse &rhs){
    *this = rhs;
}

Ellipse& Ellipse::operator = (const Ellipse &rhs){
    if(this!= &rhs){
        copyBaseVariables( (Ellipse*)&rhs );
    }
    return *this;
}


//deep copy method
bool Ellipse::deepCopyFrom(const Node *node){
    cout<<"Ellipse deep copy attempt"<<endl;
    
    
    if( node == NULL ){
        cout<<"Ellipse not deep copied because node = NULL"<<endl;
        return false;
        
    }
    //cout<<"this type="<<this->getType()<<endl;
    //cout<<"node type="<<node->getType()<<endl;
    if( this->getType() == node->getType() ){
        //Clone the values and return
        cout<<"ellipse deep copy success"<<endl;
        if( copyBaseVariables( (Ellipse*)node ) && Shape::deepCopyFrom(node)) return true;
        else return false;
    }
    else{
        cout<<"Ellipse not deep copied because of type mismatch"<<endl;
        
    }
    return false;
}



//copies over base variables to new instances
bool Ellipse::copyBaseVariables(const Ellipse *ellipse){
    
    if( ellipse == NULL ){
        cout<<"ellipse is null, cannot copy base vars"<<endl;
        return false;
    }
    
    /*if( !this->copyBaseVariables( line ) ){
     cout<<" line copy failed"<<endl;
     return false;
     }*/
    
    
    this->x1 = ellipse->x1;
    this->y1 = ellipse->y1;
    this->x2=ellipse->x2;
    this->y2=ellipse->y2;
    
    cout<<"ellipse copy base vars was successful"<<endl;
    
    
    return Shape::copyBaseVariables(ellipse);
    //return false;
    
}

/*update method for  ellipse
 *calculates relative positioning for ellipse based on current
 *position of parent shape
 */
void Ellipse::Update(void)
{
    
    if(NULL != this->GetParentNode()){
        
        Shape* parent = (Shape*)this->GetParentNode();
        double nx = parent->x2 + parentRelX;
        double ny = parent->y2 + parentRelY;
        double dx = nx - x1;
		double dy = ny- y1;
        x2+=dx;
        y2+=dy;
       // x2+=dx;
        //y2+=dy;
        
    }
    Shape::Update(); // calls base class' function
    
}
//method to reverse engineer constrained part based on shape generation.
bool Ellipse::calcConstrainedPoint(){
    
    double nx = *pCX + parentRelX;
    double ny = *pCY + parentRelY;
    double dx = nx - *cPX;
    double dy = ny- *cPY;
    x2+=dx;
    y2+=dy;
    return true;
    
}


vector<double> Ellipse::centroid(){
    vector<double>c;
    c.push_back(x2);
    c.push_back(y2);
    return c;
}

//returns bounding box as a vector (x,y,width,height)
vector<double> Ellipse::boundingbox(){
    vector<double>bb;
    bb.push_back(x2-x1/2);
    bb.push_back(y2-y1/2);
    bb.push_back(x1);
    bb.push_back(y1);
    return bb;
}

Shape* Ellipse::checkSelect(double px, double py){
    double k = Geom2D::inEllipse(px,py,x2,y2,x1/2,y1/2);
    selected = false;
    //cout<<"select val="<<k<<endl;
    if(k<=1.5&&k>=0.5){
        selected = true;
    }
    relX = px-x2;
    relY= py-y2;
    if(selected) return this;
    else return Shape::checkSelect(px, py);
}

//checks to see if point has been directly selected with an error range of 5
int Ellipse::checkDSelect(double _x, double _y){
    return Shape::checkDSelect(_x, _y);
}

bool Ellipse::move(double px, double py){
    if(selected){
        x2 = px-relX;
        y2= py-relY;
        this->Update();
    }
    else{
        return Shape::move(px,py);
    }
    return false;
}

bool Ellipse::scale(double _x, double _y){
    cout<<"attempt to scale"<<endl;
    if(selected){
        x1 = relX*2;
        y1 = relY*2;
        relX = _x-x2;
        relY= _y-y2;
        //this->Update();
    }
    else{ return Shape::movePoint(_x,_y);}
    
}

vector<double> Ellipse::getParams(){
    vector<double> params;
    params.push_back(x1);
    params.push_back(y1);
    params.push_back(x2);
    params.push_back(y2);
    return params;
    
}

bool Ellipse::size(double _x, double _y){
    x1 = std::abs(x2-_x)*2;
    y1 = std::abs(y2-_y)*2;
    
    // cout << "width and height " << x-_x << " ," <<y-_y << " ," << width << " ," <<height << endl;
    return true;
    
}

bool Ellipse::draw(ofxVectorGraphics &output,int color = -1) {
    setColor(output, color);
    output.ellipse(x2, y2, x1, y1);
    // cout << "draw ellipse at " << x << " ," <<y << " ," << width << " ," <<height << endl;
    drawChildren(output,color);

    return true;
}





