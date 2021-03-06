#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //init canvas size
    canvasX =50;
    canvasWidth = ofGetWidth()-200;
    canvasY = 60;
    canvasHeight= ofGetHeight()-60;
    snapCounter=0;
    ofEnableSmoothing();
	ofBackground(0);
	weight =1.0;
	setDrawTools();
    setCanvases();
    numExamples = 4;
    
    
    
   /* font.loadFont("verdana.ttf", 12);
    
    N = 5; //The number of shapes for each individual
    unsigned int populationSize = 10; //The number of individuals
    evo.initPopulation(populationSize, N*SHAPE_FEATURE_SIZE);
    keyCommands.resize(populationSize);
    
    unsigned int index = 0;
    keyCommands[index++] = 'q';
    keyCommands[index++] = 'w';
    keyCommands[index++] = 'e';
    keyCommands[index++] = 'r';
    keyCommands[index++] = 't';
    keyCommands[index++] = 'a';
    keyCommands[index++] = 's';
    keyCommands[index++] = 'd';
    keyCommands[index++] = 'f';
    keyCommands[index++] = 'g';
    
    //Init the weights to 1
    for(unsigned int i=0; i<populationSize; i++){
        evo[i].fitness = 1;
    }
    
    //Setup the circular buffer
    history.resize( 10 );*/
    
    
}

void testApp::setDrawTools()
{
	float dim = 47;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
	hideGUI = false;
	drawTools = new ofxUICanvas(0, 0, dim+10    , ofGetHeight());
   // drawTools->addWidgetDown(new ofxUILabel("Drawing Tools", OFX_UI_FONT_LARGE));

    
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/pen.png","PENBTN"));
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/line.png","LINEBTN"));
    drawTools->addSpacer(dim, 1);

    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/ellipse.png","ELLIPSEBTN"));
    drawTools->addSpacer(dim, 1);
    
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/rect.png","RECTBTN"));
    drawTools->addSpacer(dim, 1);


    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/arrow.png","ARROWBTN"));
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/darrow.png","DARROWBTN"));
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/scale.png","SCALEBTN"));
    
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/parent.png","PARENTBTN"));
    
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/ind.png","INDBTN"));
    drawTools->addSpacer(dim, 1);
    drawTools->addWidgetDown(new ofxUIImageButton(dim, dim, true, "GUI/images/gen.png","GENBTN"));


    /*
    drawTools->addWidgetDown(new ofxUILabel("IMAGE TOGGLE", OFX_UI_FONT_MEDIUM));
    drawTools->addWidgetDown(new ofxUIImageToggle(dim*4.0, dim*4.0, false, "GUI/images/Preview.png","IMAGETGL"));
    
    drawTools->addSpacer(length-xInit, 2);
    drawTools->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM));
    drawTools->addWidgetDown(new ofxUIRotarySlider(dim*4, 0, 100, 50, "R2SLIDER"));
    drawTools->addSpacer(length-xInit, 2);
    drawTools->addWidgetDown(new ofxUILabel("DROP DOWN", OFX_UI_FONT_MEDIUM));
    
    vector<string> items;
    items.push_back("FIRST ITEM");
    items.push_back("SECOND ITEM");
    items.push_back("THIRD ITEM WHATS UP DOG");
    items.push_back("FOURTH ITEM");
    items.push_back("FIFTH ITEM");
    items.push_back("SIXTH ITEM");
    
    drawTools->addDropDownList("DROP DOWN LIST", items, 200);*/
    
	ofAddListener(drawTools->newGUIEvent,this,&testApp::guiEvent);
}


void testApp::setCanvases(){
    float dim = 150;
    canvases = new ofxUIScrollableCanvas(ofGetWidth()-dim-10, 0, dim+10, ofGetHeight());
    canvases->setSnapping(false);
 
    
    
    drawingSettings= new ofxUICanvas(57,0,ofGetWidth()-215,60);
    drawingSettings->addWidgetDown(new ofxUILabel("Weight", OFX_UI_FONT_MEDIUM));
    drawingSettings->addWidgetRight(new ofxUILabel("          Population Size", OFX_UI_FONT_MEDIUM));
    drawingSettings->addSlider("WEIGHT", 0.0, 2.0, weight, dim, 20);
    
    drawingSettings->addWidgetRight(new ofxUISlider("NUMB", 1, 10, 4, dim, 20));
    ofAddListener(drawingSettings->newGUIEvent,this,&testApp::guiEvent);

	ofAddListener(canvases->newGUIEvent,this,&testApp::canvasEvent);
}



void testApp::canvasEvent(ofxUIEventArgs &e)
{
    ofxUIImageButton *btn = (ofxUIImageButton *)e.widget;
    int trigger = btn->getValue();
	 if(trigger ==1){
    string name = e.widget->getName();
    
    cout << "got event from: " << name << endl;
    
    int index = atoi(name.c_str() );
     d.switchDrawing(index,((ofxUISlider*)(drawingSettings->getWidget("WEIGHT")))->getScaledValue());
    ((ofxUISlider*)(drawingSettings->getWidget("WEIGHT")))->setValue(d.getWeight());
     }
    

}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
	//cout << "got event from: " << kind << endl;
	
	if(name == "PENBTN")
	{
		d.drawMode();
        
    }
    if(name == "ELLIPSEBTN")
	{
		d.ellipseMode();
        
    }
    if(name=="LINEBTN"){
        d.lineMode();
    }
    
    if(name=="RECTBTN"){
        d.rectMode();
    }
	else if(name == "ARROWBTN")
	{
		d.selectMode();
	}
	
	else if(name == "DARROWBTN")
	{
		d.directMode();
	}
    else if(name == "SCALEBTN")
	{
		d.scaleMode();
	}
    else if(name == "WEIGHT"){
       ofxUISlider *slider = (ofxUISlider *) e.widget;
        weight = slider->getScaledValue();
        //cout<<"setting weight ="<<weight<<endl;

    }
    else if(name == "NUMB"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        numExamples = round(slider->getScaledValue());
        //cout<<"setting weight ="<<weight<<endl;
        
    }
    else if(name == "PARENTBTN"){
        d.parentMode();
    }


    
    else if(name == "INDBTN")
	{
        ofxUIImageButton *btn = (ofxUIImageButton *)e.widget;
       int trigger = btn->getValue();
        //cout << "trigger was: " << trigger << endl;
        if(trigger ==1) saveIndividual(true);
        
		
	}
    else if(name == "GENBTN")
	{
        ofxUIImageButton *btn = (ofxUIImageButton *)e.widget;
        int trigger = btn->getValue();
        //cout << "trigger was: " << trigger << endl;
        if(trigger ==1){
            
            d.populateFeatureTree();
            generateNewIndividual();
        }

	}
   	
	
}

bool testApp::generateNewIndividual(){
    d.clearLastSaved();

    cout<<"numExamples ="<<numExamples<<endl;
    cout<<"total population before generation= "<<d.savedDrawings.size()<<endl;
    cout<<"adding:"<<numExamples<<endl;

    for(int i=0;i<numExamples;i++){
        //d.clearAll();
        d.generateDrawing();
        //probModel.generateDrawing(d.currentShapes);
        ////d.addDrawing(newDrawing);
        if(i<numExamples-1) saveIndividual(false);
        else saveIndividual(true);
    }
    
    cout<<"total population = "<<d.savedDrawings.size()<<endl;
    
}

void testApp::saveIndividual(bool saveDraw){
    // grab a rectangle at 200,200, width and height of 300,180

  
    ofBackground(255);
    d.draw(output, false);
    snapshot.grabScreen(canvasX,canvasY,canvasWidth,canvasHeight);
    //cout<<"saving weight ="<<weight<<endl;
    if(saveDraw){
        d.saveDrawing(weight);
    }
    string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
    snapshot.saveImage(fileName);
    //sprintf(snapString, "saved %s", fileName.c_str());
    ostringstream convert;   // stream used for the conversion
    convert << snapCounter;
    
    string count = convert.str();
    canvases->addWidgetDown(new ofxUIImageButton(150,150, true, fileName,count));
    canvases->addSpacer(150, 1);
    snapCounter++;


    
}


//--------------------------------------------------------------
void testApp::update(){
    //d.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
	ofBackground(255);
	
	/*ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
	ofPopStyle();
    
    ofSetRectMode(OF_RECTMODE_CENTER);*/
    
    d.draw(output,true);
    ofSetHexColor(0x000000);
    ostringstream convertx;   // stream used for the conversion
    convertx << mouseX;
    
    string xString = convertx.str();
    ostringstream converty;   // stream used for the conversion
    converty << mouseY;

  
    string yString = converty.str();
    ofDrawBitmapString(xString+","+yString, mouseX,mouseY);

        
        
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
 /*
    for(unsigned int i=0; i<keyCommands.size(); i++){
        if( int(keyCommands[i]) == key ){
            evo[i].fitness++;
            return;
        }
    }
    
    switch( key ){
        case OF_KEY_RETURN:
            evolvePopulation();
            return;
            break;
    }*/
}



//--------------------------------------------------------------
void testApp::keyReleased(int key){
       
       
    switch( key ){
        case 99:
           d.clearLast();
            return;
            break;
        case 100:
            d.clearAll();
            return;
            break;
    }


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    d.mouseMove(x,y);
   
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
   if((x> canvasX && x<canvasX+canvasWidth) &&(y> canvasY && y<canvasY+canvasHeight)){
        
        d.mouseDrag(x,y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if((x> canvasX && x<canvasX+canvasWidth) &&(y> canvasY && y<canvasY+canvasHeight)){
        
        d.mouseDown(x,y);
    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  d.mouseUp(x,y);
    
  }

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::exit()
{
    d.deleteShapes();
	delete drawTools;
    delete canvases;
    delete drawingSettings;
}