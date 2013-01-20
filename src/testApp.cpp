#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofxXmlSettings settings;
	settings.loadFile("../settings.xml");

	camWidth 		= settings.getValue("camWidth", 640);	// try to grab at this size.
	camHeight 		= settings.getValue("camHeight", 480);

	flipV = settings.getValue("flipVertical", 0);
	flipH = settings.getValue("flipHorizontal", 0);
	ofSetWindowShape(camWidth, camHeight);

	vidGrabber.listDevices();
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID( settings.getValue("cameraID", 0) );
	vidGrabber.initGrabber(camWidth,camHeight);

	ofSetVerticalSync(true);
	
	videoTexture.allocate(camWidth,camHeight, OF_IMAGE_COLOR);
	ofSetFrameRate( settings.getValue("appFrameRate", 5) );
	count = 0;
	char aux[128];
	sprintf(aux, "%d_%d_%d__%d_%d_%d",  ofGetYear() ,ofGetMonth() ,ofGetDay() ,ofGetHours()  ,ofGetMinutes() , ofGetSeconds() );
	folder = ofToString(aux);
	ofDirectory d;
	d.createDirectory(folder);

	settings.loadFile("settings.xml");
	interval = settings.getValue("interval", 10.0);
	settings.setValue("interval", interval);
	printf("interval: %f\n", interval);
	settings.saveFile("../settings.xml");

	//exporter = new ofxImageExportQueue( 1 ); // 2 threads
	//exporter->setRestTime(250);
	timer = 0;
	ofBackground(0);

}


//--------------------------------------------------------------
void testApp::update(){

	vidGrabber.update();
	timer += 1.0 / ofGetFrameRate();
	if (timer > interval && vidGrabber.isFrameNew()){
		timer = 0;
		printf("shoot %d\n", count);
		videoTexture.setFromPixels( vidGrabber.getPixels(), camWidth, camHeight, OF_IMAGE_COLOR);
		char aux[22];
		sprintf(aux, "%08d.jpg", count );
		string path = folder + "/" + ofToString( aux );
		videoTexture.saveImage( path );
		//exporter->saveImage( videoTexture, path );
		count++;
	}
	//exporter->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	ofSetRectMode(OF_RECTMODE_CENTER);
	vidGrabber.draw(	ofGetWidth() / 2 ,
						ofGetHeight() / 2,
						 vidGrabber.getWidth() * (flipH ? -1 : 1),
						 vidGrabber.getHeight() * (flipV ? -1 : 1)
						 );
	//exporter->draw( 10, 10);
	ofDrawBitmapString( "camera: " + ofToString(camWidth) + "x" + ofToString(camHeight) + "\ninterval: " + ofToString(interval,1) + "\nnext shot in " + ofToString( interval - timer, 1 ) +
					   "\nShots: " + ofToString(count),
					   10, ofGetHeight() - 50 );

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}

	if (key == ' '){
		ofToggleFullscreen();
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
