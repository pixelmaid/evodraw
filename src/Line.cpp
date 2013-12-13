//
//  Line.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 12/6/13.
//
//

#include "Line.h"

//register line with base class
RegisterNodeModule< Line > Line::registerModule("Line");

//default constructor
Line::Line(){
    Shape::Shape();
    type = "Line";

}

//constructor to intialize start point
Line::Line(double _x, double _y){
    x1 = _x;
    y1 = _y;
    x2 = _x;
    y2 = _y;
    Line();
    type = "Line";
}

//constructor to intialze both start and end points
Line::Line(double _x1, double _y1, double _x2, double _y2){
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
    Line();
    type = "Line";
    cout<<"Line init x1="<<this->x1<<", y1="<<this->y1<<", x2="<<this->x2<<", y2="<<this->y2<<endl;

    //cout<<"line type="<<this->getType()<<endl;
    

}

//default deconstructor
Line::~Line(){
    
}


//equals operator
Line::Line(const Line &rhs){
    *this = rhs;
}

//copy constructor
Line& Line::operator = (const Line &rhs){
    if(this!= &rhs){
        copyBaseVariables( (Line*)&rhs );
    }
    return *this;
    
}

//deep copy method
bool Line::deepCopyFrom(const Node *node){
    cout<<"line deep copy attempt"<<endl;

    
    if( node == NULL ){
        cout<<"line not deep copied because node = NULL"<<endl;
        return false;

    }
    cout<<"this type="<<this->getType()<<endl;
    cout<<"node type="<<node->getType()<<endl;
    if( this->getType() == node->getType() ){
        //Clone the values and return
        cout<<"line deep copy success"<<endl;
        if( copyBaseVariables( (Line*)node ) && Shape::deepCopyFrom(node)) return true;
        else return false;
    }
    else{
        cout<<"line not deep copied because of type mismatch"<<endl;
  
    }
    return false;
}



//copies over base variables to new instances
bool Line::copyBaseVariables(const Line *line){
   
    if( line == NULL ){
        cout<<"line is null, cannot copy base vars"<<endl;
        return false;
    }
    
    /*if( !this->copyBaseVariables( line ) ){
        cout<<" line copy failed"<<endl;
        return false;
    }*/
    
   
    this->x1 = line->x1;
    this->y1 = line->y1;
    this->x2=line->x2;
    this->y2=line->y2;
    
    cout<<"line copy base vars was successful"<<endl;
    
    
    return Shape::copyBaseVariables(line);
    //return false;
    
}

/*update method for line
*calculates relative positioning for line based on current 
*position of parent shape
 */
void Line::Update(void)
{
    
    if(NULL != this->GetParentNode()){
                
        double nx = *pCX + parentRelX;
        double ny = *pCY + parentRelY;
        double dx = nx - *cPX;
		double dy = ny- *cPY;
        x1+=dx;
        y1+=dy;
        x2+=dx;
        y2+=dy;
                    
    }
    Shape::Update(); // calls base class' function

}
//method to reverse engineer constrained part based on shape generation.
bool Line::calcConstrainedPoint(){
    
    double nx = *pCX + parentRelX;
    double ny = *pCY + parentRelY;
    double dx = nx - *cPX;
    double dy = ny- *cPY;
    x1+=dx;
    y1+=dy;
    return true;

}
//adds a child node and calculates relative parent values used
/*
bool Shape::AddChildNode(Node* ChildNode){
    /*  vector<double> pC = this->centroid();
     vector<double> cC = ((Shape*)ChildNode)->centroid();
     ((Shape*)ChildNode)->parentRelX = cC[0]-pC[0];
     ((Shape*)ChildNode)->parentRelY = cC[1]-pC[1];*/
  /*  return Node::AddChildNode(ChildNode);
}
*/

//returns midpoint of the line as centroid
vector<double> Line::centroid(){
    
    vector<double> c = Geom2D::getMidpoint(x1,y1,x2,y2);
    cX = c[0];
    cY = c[1];
    return c;
}

//returns bounding box as a vector (x,y,width,height)
vector<double> Line::boundingbox(){
    vector<double>bb;
    if(Geom2D::isLeft(x1,x2))bb.push_back(x1);
    else bb.push_back(x2);
    if(Geom2D::isTop(y1,y2))bb.push_back(y1);
    else bb.push_back(y2);
    bb.push_back(abs(x1-x2));
    bb.push_back(abs(y1-y2));
    return bb;
}

//returns start and end points as a vector of 4 values
vector<double> Line::getParams(){
    vector<double> params;
    params.push_back(x1);
    params.push_back(y1);
    params.push_back(x2);
    params.push_back(y2);
    return params;
}

//sizes line based on new coordinates (used for user drawing)
bool Line::size(double _x, double _y){
    x2 = _x;
    y2 = _y;
    return true;
}

/*checks to see if line has been selected using distance to line method
* with error value of 0.01
* sets relX and relY values based on selection point
*/
Shape* Line::checkSelect(double px, double py){
    double k = Geom2D::distanceToLine(px, py, x1, y1, x2, y2);
    int r  = Geom2D::inRect(px, py, x1, y1, x2, y1, x2, y2, x1, y2, 0.01);
    
    selected = false;
    if(k<=2 && r >=0){
        selected = true;
    }
    relX = px-x1;
    relY= py-y1;
    if(selected) return this;
    else return Shape::checkSelect(px, py);
}

//checks to see if point has been directly selected with an error range of 5
int Line::checkDSelect(double _x, double _y){
    int dist = 5;
    selectedP=-1;
    if(abs(x1-_x) <= dist && abs(y1-_y) <=dist) selectedP=0;
    else if (abs(x2-_x) <= dist && abs(y2-_y) <=dist) selectedP = 1;
    if(selectedP!=-1) return selectedP;
    else return Shape::checkDSelect(_x, _y);
}


//move function- moves based on relative point defined at selection
bool Line::move(double px, double py){
    if(selected){
        double xdiff = x1-(px-relX);
        double ydiff = y1-(py-relY);
        x1  = px-relX;
        y1 = py-relY;
        x2 -= xdiff;
        y2-= ydiff;
        this->Update();
        return true;
    }
    else{
        return Shape::move(px,py);
    }
    return false;
}



/*move indivdual point function
* moves start or end based on value of selectedP
*/
bool Line::movePoint(double _x, double _y){
    
    if(selectedP==0){
        x1 = _x;
        y1 = _y;
        this->updateRelativeDist();
        this->Update();
        return true;

    }
    else if(selectedP == 1){
        x2 = _x;
        y2 = _y;
        this->updateRelativeDist();
        this->Update();
    
        return true;

    }
    else{
        return Shape::movePoint(_x,_y);
    }

    return false;
}


/*line draw function
 *draws line according to manner of user selection
 */
bool Line::draw(ofxVectorGraphics &output, int color=-1) {
    
    setColor(output, color);
    output.line(x1, y1, x2,y2);
    if(selected){
        output.setColor(Color_Const::origin);
        output.fill();
        output.rect(x1-1.5,y1-1.5,3,3);
        output.setColor(Color_Const::end);
        
        output.rect(x2-1.5,y2-1.5,3,3);
    }
    output.setColor(0x00A4FF);
    if(selectedP==0){
        
        output.setColor(Color_Const::solid);
        output.fill();
        output.rect(x1-1.5,y1-1.5,3,3);
        output.noFill();
        output.setColor(Color_Const::origin);
        
        output.rect(x1-1.5,y1-1.5,3,3);
        
    }
    else if(selectedP == 1){
        output.setColor(Color_Const::solid);
        output.fill();
        output.rect(x2-1.5,y2-1.5,3,3);
        output.noFill();
        output.setColor(Color_Const::end);
        
        output.rect(x2-1.5,y2-1.5,3,3);
        
    }
    drawChildren(output,color);
    return true;
}





