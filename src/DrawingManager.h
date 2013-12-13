//
//  DrawingManager.h
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/12/13.
//
//

#ifndef evodraw1_DrawingManager_h
#define evodraw1_DrawingManager_h
    
#include <iostream>
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "ofxVectorGraphics.h"
#include "ofMain.h"
#include "Color_Const.h"
#include "Ellipse.h"
    
#define DRAW_M 0
#define SELECT_M 1
#define DIRECT_M 2
#define ELLIPSE_M 3
#define RECT_M 4
#define LINE_M 5
#define SCALE_M 6
#define PARENT_M 7



class DrawingManager{
    
public:
    
    void mouseDrag(double x, double y){
        if (mode == DRAW_M); //addPoint(x,y);
        else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M) sizeShape(x,y);
        else if (mode == SELECT_M) checkMove(x,y);
        else if (mode == DIRECT_M) checkDMove(x,y);
        else if (mode == SCALE_M) checkScale(x,y);
        
    }
    
    void mouseMove(double x, double y){
        
    }
    
    void mouseDown(double x, double y){
        if (mode == DRAW_M); //addPoint(x,y);
        else if (mode == SELECT_M || mode == SCALE_M) checkSelect(x,y);
        else if (mode == DIRECT_M) checkDSelect(x,y);
        else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M) startShape(x,y);
        
        if (mode== PARENT_M) parent(x,y);
         
    }
    
    void mouseUp(double x, double y){
        if (mode == DRAW_M) close();
         else if (mode == ELLIPSE_M || mode== LINE_M || mode==RECT_M)endShape(x,y);
         else if(mode==SCALE_M) deselectShapes();


    }
    
    
    /*void addPoint(double x, double y){
     int last = currentShapes.size()-1;
     if(last==-1||currentShapes[last]->closed){
     Shape* s = new Shape();
     currentShapes.push_back(s);
     }
     else {
         currentShapes[last]->addPoint(x,y);
     
     };
     
     }*/
    
    void parent(double x, double y){
        if (_parent ==NULL){
        for(int i=0;i<currentShapes.size();i++){
            Shape* s=  currentShapes[i]->checkSelect(x, y);
            if(s!=NULL) {
                _parent=s;
                s->parentSelected= true;
                currentShapes[i]->selected = false;
                cout<<"parent_selected"<<endl;

            }
        

            break;
            }
        }
        else {
            for(int i=0;i<currentShapes.size();i++){
                    Shape* s=  currentShapes[i]->checkSelect(x, y);
                if(s!=NULL && s!=_parent) {
                    if(removeChild(s)){
                    _parent->AddChildNode(s);
                    s->childSelected= true;
                    s->selected = false;
                    
                    cout<<"parent_child created"<<endl;
                    _parent = NULL;
                    break;
                }
            }
            
        }
            _parent = NULL;

        }
        
    }
    
    bool removeChild(Shape* c){
        for(int i=0;i<currentShapes.size();i++){
            if(currentShapes[i]==c){
                currentShapes.erase(currentShapes.begin() + i );
                cout<<"child to be removed found in current shapes "<<i<<endl;
                return true;
                break;
                
            }

            else if (currentShapes[i]->RecursiveRemoveChildNode(c)){
            cout<<"child to be removed found in child of current shapes"<<endl;
          
            return true;
            break;
            }
        };
        return false;
    }
    
    void checkSelect(double x, double y){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->checkSelect(x, y);
        };
    }
    
    
    void checkDSelect(double x, double y){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->checkDSelect(x, y);
        };
    }
    
    void checkMove(double x, double y){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->move(x, y);
        };
    }
    
    void checkDMove(double x, double y){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->movePoint(x, y);
        };
    }
    
    void checkScale(double x, double y){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->scale(x, y);
        };
    }
    
    
    /*void update(){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->Update();
        }
    }*/
    
     void draw(ofxVectorGraphics &output, bool history){
         bool dselect = false;
         int rv=70;
         if (mode == SELECT_M ||mode == DIRECT_M ) dselect = true;
         if(history){
             int lDp = dP-4;
             if(lDp<0)lDp=0;
             
         for(int i = dP-1;i>=lDp;i--){
              int color = createRGB(255,rv,rv);
             for(int j=0;j<savedDrawings[i].size();j++){
                savedDrawings[i][j]->draw(output,color);
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

         for(int i=0;i<currentShapes.size();i++){
             currentShapes[i]->draw(output);
     }
     }
    
    
    unsigned long createRGB(int r, int g, int b)
    {
        return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    }
    
    //these methods control the creation of regular shapes
    
    void startShape(int x, int y){
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
        currentShapes.push_back(s);
        shapeStart = true;
        
    }
    
    void sizeShape(int x, int y){
       if(shapeStart){
           currentShapes[currentShapes.size()-1]->size(x,y);
       }

    }
    
    void endShape(int x, int y){
        if(shapeStart){
            shapeStart = false;
        }
  
    }
    
    void close(){
        if(currentShapes.size()>0){
            int last = currentShapes.size()-1;
        }
    }
    
    void deselectShapes(){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->deselect();
        }
    }

    
    void clearAll(){
        for (int i=0;i<currentShapes.size();i++){
            delete(currentShapes[i]);
            currentShapes[i]=NULL;
        }
        currentShapes.clear();
    }
    
    void clearLast(){
        if(currentShapes.size()!=0){
            delete(currentShapes[currentShapes.size()-1]);
            currentShapes[currentShapes.size()-1]=NULL;
            currentShapes.pop_back();
        }
    }
    
    
    void drawMode(){
        mode = DRAW_M;
        deselectShapes();
    }
    
    void ellipseMode(){
        mode = ELLIPSE_M;
        deselectShapes();
       
    }
    void lineMode(){
        mode = LINE_M;
        deselectShapes();
        
    }
    
    void rectMode(){
        mode = RECT_M;
        deselectShapes();
        
    }
    
    void parentMode(){
        mode = PARENT_M;
        deselectShapes();
        
    }
    
    void selectMode(){
        mode = SELECT_M;
        deselectShapes();

        //close();
        
    }
    
    void directMode(){
        mode = DIRECT_M;
        deselectShapes();

        //close();
    }
    
    void scaleMode(){
        mode = SCALE_M;
        deselectShapes();

        //close();
    }
    
    void saveDrawing(double w){
        for(int i=0;i<currentShapes.size();i++){
            currentShapes[i]->setWeight(w);
        }
        vector<Shape*> c = copy(currentShapes);
        savedDrawings.push_back(c);
        //weights.push_back(w);
        cout<<"weight = "<<w<<endl;
        //currentShapes.clear();
        dP++;
    }
    bool addDrawing(vector<Shape*> &drawing){
        clearAll();
        currentShapes = drawing;
        return true;
    }
    
    vector<Shape*> copy(vector<Shape*>toCopy){
        vector<Shape*> copy;
        for(int i=0;i<toCopy.size();i++){
            Shape* s = setShape(toCopy[i]);
            copy.push_back(s);
        }
        return copy;
    }
    
   Shape* setShape(const Shape* shape){
       Shape* nshape;
        //Create a new instance of the classifier and then clone the values across from the reference classifier
       nshape = (Shape*)shape->createNewInstance();
        
        if( nshape == NULL ){
            //errorMessage = "setClassifier(const Classifier classifier) - Classifier Module Not Set!";
            //errorLog << errorMessage << endl;
            cout<<"shape not copied"<<endl;
            
            return NULL;
        }
        
        //Validate that the classifier was cloned correctly
        if( !nshape->deepCopyFrom( shape ) ){
            delete nshape;
            nshape=NULL;
            cout<<"shape not copied because of deep copy"<<endl;
            return NULL;
        }
        return nshape;
    }
    
    
    void deleteShapes(){
        for (int i=0;i<savedDrawings.size();i++){
            for(int j=0;j<savedDrawings[i].size();j++){
                delete(savedDrawings[i][j]);
                    savedDrawings[i][j]=NULL;
            }
        }
        savedDrawings.clear();

        for (int i=0;i<currentShapes.size();i++){
            cout<<"deleting shape at "<<i<<endl;
            delete(currentShapes[i]);
            cout<<"setting NULL shape at "<<i<<endl;
            currentShapes[i]=NULL;
        }
        cout<<"clearing current shapes"<<endl;

        currentShapes.clear();
        _parent = NULL;
    }

    vector<Shape*> currentShapes;
    vector<vector<Shape*>> savedDrawings;
    vector<double> weights;
    
     private:
    int mode;
    int dP; //position for current drawing
    bool shapeStart;
    Shape* _parent;
};



#endif
