//
//  DrawingManager.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/30/13.
//
//

#include "DrawingManager.h"

DrawingManager::DrawingManager(){
    treeBuilt=false;
    
}

DrawingManager::~DrawingManager(){
    
    clearModel();
    deleteShapes();
}

bool DrawingManager::clearModel(){
    for(int i=0;i<fnodes.size();i++){
        delete fnodes[i];
        fnodes[i]=NULL;
    }
    fnodes.clear();
    treeBuilt=false;
    return true;
 
}

//model methods
bool DrawingManager::populateFeatureTree(){
    //if(!treeBuilt)buildFeatureTree(drawings[0]);
    clearNodeData();
    if(!treeBuilt){
        buildFeatureTree();
    }
    for(int i=0;i<savedDrawings.size();i++){
        for(int j=0;j<savedDrawings[i].size();j++){
            cout<<"adding shape features "<< i <<" to feature node "<<j<<endl;
            fnodes[j]->getShapeFeatures(savedDrawings[i][j]);
            
        }
    }
    
}

bool DrawingManager::clearNodeData(){
    for(int i=0;i<fnodes.size();i++){
        fnodes[i]->clearNodeData();
    }
}

bool DrawingManager::buildFeatureTree(){ 
    for(int i=0;i<savedDrawings[0].size();i++){
        FeatureNode* f = new FeatureNode();
        f->createChildrenFromShape(savedDrawings[0][i]);
        fnodes.push_back(f);
        //cout<<"created a feature node at "<<i<<endl;
        
    }
    treeBuilt = true;
    //cout<<"completed building feature tree"<<endl;
}




//cleanup methods
void DrawingManager::clearAll(){
   /* for (int i=0;i<currentShapes.size();i++){
        delete(currentShapes[i]);
        currentShapes[i]=NULL;
    }
    currentShapes.clear();*/
}

void DrawingManager::clearLast(){
    //if(savedDrawings.size()!=0){
    if(savedDrawings[savedDrawings.size()-1].size()>0){
       int last =savedDrawings.size()-1;
        delete(savedDrawings[last][savedDrawings[last].size()-1]);
        savedDrawings[last][savedDrawings[last].size()-1]=NULL;
        savedDrawings[last].pop_back();
      
    }
  
   // }
}

void DrawingManager::clearLastSaved(){
    savedDrawings.pop_back();
    currentShapes=  &savedDrawings[savedDrawings.size()-1];
}


void DrawingManager::deleteShapes(){
    for (int i=0;i<savedDrawings.size();i++){
        for(int j=0;j<savedDrawings[i].size();j++){
            delete(savedDrawings[i][j]);
            savedDrawings[i][j]=NULL;
        }
    }
    savedDrawings.clear();
    
    /*if(!indexed){
    for (int i=0;i<currentShapes.size();i++){
        //cout<<"deleting shape at "<<i<<endl;
        delete(currentShapes[i]);
        //cout<<"setting NULL shape at "<<i<<endl;
        currentShapes[i]=NULL;
    }}
    //cout<<"clearing current shapes"<<endl;
    
    currentShapes.clear();*/
    _parent = NULL;
}

//mouse event detection
void DrawingManager::mouseDrag(double x, double y){
    if (mode == DRAW_M); //addPoint(x,y);
    else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M) sizeShape(x,y);
    else if (mode == SELECT_M) checkMove(x,y);
    else if (mode == DIRECT_M) checkDMove(x,y);
    else if (mode == SCALE_M) checkScale(x,y);
    
}

void DrawingManager::mouseDown(double x, double y){
    if (mode == DRAW_M); //addPoint(x,y);
    else if (mode == SELECT_M || mode == SCALE_M) checkSelect(x,y);
    else if (mode == DIRECT_M) checkDSelect(x,y);
    else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M) startShape(x,y);
    
    if (mode== PARENT_M) parent(x,y);
    
}


void DrawingManager::mouseUp(double x, double y){
    if (mode == DRAW_M) close();
    else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M)endShape(x,y);
    else if(mode==SCALE_M) deselectShapes();
    
    
}

//selection detection
void DrawingManager::checkSelect(double x, double y){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
      ((*currentShapes)[ i ])->checkSelect(x, y);
    };
    }
}


void DrawingManager::checkDSelect(double x, double y){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
       ((*currentShapes)[ i ])->checkDSelect(x, y);
    };
    }
}

void DrawingManager::checkMove(double x, double y){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
       ((*currentShapes)[ i ])->move(x, y);
    };
    }
}

void DrawingManager::checkDMove(double x, double y){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
       ((*currentShapes)[ i ])->movePoint(x, y);
    };
    }
}

void DrawingManager::checkScale(double x, double y){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
        ((*currentShapes)[ i ])->scale(x, y);
    };
    }
}

void DrawingManager::deselectShapes(){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
        ((*currentShapes)[ i ])->deselect();
    }
    }
}

//these methods control the creation of regular shapes
void DrawingManager::startShape(int x, int y){
    //cout << "start ellipse at " << x << " ," <<y << endl;
    Shape* s;
    switch (mode)
    {
        case ELLIPSE_M:
            s = new Ellipse(x,y);
            break;
        case LINE_M:
            s = new Line(x,y);
            break;
        case RECT_M:
            s = new Rectangle(x,y);
            break;
    }
    if(savedDrawings.size()==0){
        vector<Shape*> drawing;
        drawing.push_back(s);
        savedDrawings.push_back(drawing);
        
    }
    else{
        savedDrawings[savedDrawings.size()-1].push_back(s);
    }

    shapeStart = true;
    currentShapes=&savedDrawings[savedDrawings.size()-1];
    
}

void DrawingManager::sizeShape(int x, int y){
    if(shapeStart){
        ((*currentShapes)[ currentShapes->size()-1 ])->size(x,y);
    }
    
}

void DrawingManager::endShape(int x, int y){
    if(shapeStart){
        shapeStart = false;
    }
    
}

void DrawingManager::close(){
    if(currentShapes!=NULL){

    if(currentShapes->size()>0){
        int last = currentShapes->size()-1;
    }
    }
}


//drawing
void DrawingManager::draw(ofxVectorGraphics &output, bool history){
    bool dselect = false;
    int rv=70;
    if (mode == SELECT_M ||mode == DIRECT_M ) dselect = true;
    if(history){
     int lDp = dP-4;
     if(lDp<0)lDp=0;
     
     for(int i = dP-1;i>=lDp;i--){
     int color = createRGB(255,rv,rv);
         if(i>=0 && i<savedDrawings.size()){
             for(int j=0;j<savedDrawings[i].size();j++){
        
                 savedDrawings[i][j]->draw(output,color);
         
        
             }
         }
     rv+=70;
     if(rv>255){
     rv=255;
     }
     }
    
    /*   rv=70;
     int kDp = dP+4;
     if(kDp>savedDrawings.size()-1)kDp=savedDrawings.size()-1;
     for(int i = dP+1;i<=kDp;i++){
     int color = createRGB(rv,255,rv);
     for(int j=0;j<savedDrawings[i].size();j++){
     savedDrawings[i][j]->draw(output,dselect,color);
     }
     rv+=70;
     if(rv>255){
     rv=255;
     }
     }*/
    
    }
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
        (*currentShapes)[ i ]->draw(output);
    }
    }
}


//parent child handling
void DrawingManager::parent(double x, double y){
   if(currentShapes!=NULL){
    if (_parent ==NULL){
        for(int i=0;i<currentShapes->size();i++){
            Shape* s=  (*currentShapes)[ i ]->checkSelect(x, y);
            if(s!=NULL) {
                _parent=s;
                s->parentSelected= true;
               ((*currentShapes)[ i ])->selected = false;
                //cout<<"parent_selected"<<endl;
                
            }
            
            
            break;
        }
    }
    else {
        for(int i=0;i<currentShapes->size();i++){
            Shape* s=  (*currentShapes)[ i ]->checkSelect(x, y);
            if(s!=NULL && s!=_parent) {
                if(removeChild(s)){
                    _parent->AddChildNode(s);
                    s->childSelected= true;
                    s->selected = false;
                    
                    //cout<<"parent_child created"<<endl;
                    _parent = NULL;
                    break;
                }
            }
            
        }
        _parent = NULL;
        
    }
   }
    
}

bool DrawingManager::removeChild(Shape* c){
    int last = savedDrawings.size()-1;
     for(int i=0;i<savedDrawings[last].size();i++){
        if(savedDrawings[last][i]==c){
            savedDrawings[last].erase(savedDrawings[last].begin() + i );
            //cout<<"child to be removed found in current shapes "<<i<<endl;
            return true;
            break;
            
        }
        
        else if (savedDrawings[last][i]->RecursiveRemoveChildNode(c)){
            //cout<<"child to be removed found in child of current shapes"<<endl;
            
            return true;
            break;
        }
    };
    return false;
}


void DrawingManager::generateDrawing(){
    //cout<<"fnodes size="<<fnodes.size()<<endl;
    deselectShapes();
    
    vector<Shape*> drawing;
    if(fnodes.size()>0){
        for(int i=0;i<fnodes.size();i++){
            Shape* gShape = fnodes[i]->generateShape(NULL);
            //delete currentShapes[i];
            drawing.push_back(gShape);
            //currentShapes[i]->y1=100;
            //currentShapes[i]->y2=200;
            //delete gShape;
            //gShape = NULL;
        }
    }
    savedDrawings.push_back(drawing);
    currentShapes=&savedDrawings[savedDrawings.size()-1];
    
}
//saving, adding and copying (the troublemakers)
void DrawingManager::saveDrawing(double w){
    deselectShapes();
    int last = savedDrawings.size()-1;
    for(int i=0;i<savedDrawings[last].size();i++){
       savedDrawings[last][i]->setWeight(w);
    }
    vector<Shape*> c = copy(savedDrawings[last]);
    savedDrawings.push_back(c);
    cout<<"weight = "<<w<<endl;
    currentShapes=  &savedDrawings[savedDrawings.size()-1];
    indexed = false;
    dP++;
}

void DrawingManager::setWeight(double w){
    if(currentShapes!=NULL){
    for(int i=0;i<currentShapes->size();i++){
        (*currentShapes)[ i ]->setWeight(w);
        //cout<<"saving: x1="<<currentShapes[i]->x1<<", x2="<<currentShapes[i]->x2<<", y1="<<currentShapes[i]->x2<<", y2="<<currentShapes[i]->x2<<", pRx="<<currentShapes[i]->parentRelX<<", pRY="<<currentShapes[i]->parentRelY<<", type="<<currentShapes[i]->type<<", weight="<<currentShapes[i]->weight<<endl;
    }
    }

}

double DrawingManager::getWeight(){
    return (*currentShapes)[ 0 ]->weight;
}

bool DrawingManager::switchDrawing(int num, double weight){
    setWeight(weight);
    if(num<savedDrawings.size()){
       currentShapes = &savedDrawings[num];
        indexed=true;
    }
    
}
vector<Shape*> DrawingManager::copy(vector<Shape*>toCopy){
    vector<Shape*> copy;
    for(int i=0;i<toCopy.size();i++){
        Shape* s = setShape(toCopy[i]);
        copy.push_back(s);
    }
    return copy;
}

Shape* DrawingManager::setShape(const Shape* shape){
    Shape* nshape;
    //Create a new instance of the classifier and then clone the values across from the reference classifier
    nshape = (Shape*)shape->createNewInstance();
    
    if( nshape == NULL ){
        //errorMessage = "setClassifier(const Classifier classifier) - Classifier Module Not Set!";
        //errorLog << errorMessage << endl;
        //cout<<"shape not copied"<<endl;
        
        return NULL;
    }
    
    //Validate that the classifier was cloned correctly
    if( !nshape->deepCopyFrom( shape ) ){
        delete nshape;
        nshape=NULL;
        //cout<<"shape not copied because of deep copy"<<endl;
        return NULL;
    }
    return nshape;
}


