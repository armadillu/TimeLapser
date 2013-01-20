#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxImageExportQueue.h"


class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		void exit(){ delete exporter;}
	
		ofVideoGrabber 		vidGrabber;
		ofImage				videoTexture;

		int 				camWidth;
		int 				camHeight;
		int count;
		string folder;
		float interval;
		ofxImageExportQueue * exporter;
		float timer;
		bool flipV, flipH;
};