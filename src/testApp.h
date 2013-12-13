#pragma once

#include "ofMain.h"
#include "GRT.h"
#include "ofxVectorGraphics.h"
#include "DrawingManager.h"
#include "ofxUI.h"
#include "Shape.h"
using namespace GRT;

#define SHAPE_FEATURE_SIZE 6


//The size features are: r,g,b, x,y and size

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    //evolution
     void evolvePopulation();
    
    UINT N;
    LabelledClassificationData trainingData;
    EvolutionaryAlgorithm< Individual > evo;
    CircularBuffer< vector< Individual > > history;
    vector< char > keyCommands;
    ofTrueTypeFont font;
    ofImage image;
    Random random;
    
   
    //graphics
    ofxVectorGraphics output;
    DrawingManager d;
    
    //ui
    void guiEvent(ofxUIEventArgs &e);
    void canvasEvent(ofxUIEventArgs &e);
    void setDrawTools();
    void setCanvases();
    void saveIndividual();
    bool generateNewIndividual();
    
    ofxUICanvas *drawTools;
    ofxUIScrollableCanvas *canvases;
    ofxUICanvas *drawingSettings;
    
    vector<ofxUIImageButton> canvasImgs;
    bool hideGUI;
    ofImage snapshot;
    int snapCounter;
    
    double weight;
    int numExamples;
    
    //canvas dimensions
    int canvasX;
    int canvasWidth;
    int canvasY;
    int canvasHeight;
    
    
    
    
       
};
