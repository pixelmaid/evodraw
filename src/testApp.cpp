#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //init canvas size
    canvasX =50;
    canvasWidth = ofGetWidth()-160;
    canvasY = 0;
    canvasHeight= ofGetHeight();
    snapCounter=0;
    ofEnableSmoothing();
	ofBackground(0);
	
	setDrawTools();
    setCanvases();
    

    
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
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
	cout << "got event from: " << kind << endl;
	
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
    
    else if(name == "INDBTN")
	{
        ofxUIImageButton *btn = (ofxUIImageButton *)e.widget;
       int trigger = btn->getValue();
        cout << "trigger was: " << trigger << endl;
        if(trigger ==1) saveIndividual();
        
		
	}
    else if(name == "GENBTN")
	{
        ofxUIImageButton *btn = (ofxUIImageButton *)e.widget;
        int trigger = btn->getValue();
        cout << "trigger was: " << trigger << endl;
        if(trigger ==1){
            
           // probModel.evalKeystone(d.savedDrawings);
            //probModel.generateKeystoneValues();
           vector <vector <double> > values = probModel.analyzeDrawing(d.savedDrawings);
            
            
           cout << "total vals:" <<values.size()<<endl;
            d.generateShapes(values);
        }

	}
    /*
	else if(name == "DRAW GRID")
	{
		ofxUIButton *button = (ofxUIButton *) e.widget;
		bdrawGrid = button->getValue();
	}
	else if(name == "D_GRID")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		bdrawGrid = toggle->getValue();
	}
    else if(name == "TEXT INPUT")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }*/
	
	
	
}

void testApp::saveIndividual(){
    // grab a rectangle at 200,200, width and height of 300,180
   
    
    snapCounter++;
  
    ofBackground(255);
    d.draw(output, false);
    snapshot.grabScreen(canvasX,canvasY,canvasWidth,canvasHeight);

    d.saveDrawing();
    string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
    snapshot.saveImage(fileName);
    //sprintf(snapString, "saved %s", fileName.c_str());
    canvases->addWidgetDown(new ofxUIImageToggle(150,150, true, fileName,"snapCounter"));
    canvases->addSpacer(150, 1);

    
}


//--------------------------------------------------------------
void testApp::update(){

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

void testApp::evolvePopulation(){
    
    //Evolve the current population
    evo.evolvePopulation();
    
    //Store the population in the history
    history.push_back( evo.getPopulation() );
    
    //Reset the population fitness
    for(unsigned int i=0; i<evo.getPopulationSize(); i++){
        evo[i].fitness = 1;
    }
    
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
    if(x> canvasX && x<canvasX+canvasWidth){
        
        d.mouseDrag(x,y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(x> canvasX && x<canvasX+canvasWidth){
        
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
}