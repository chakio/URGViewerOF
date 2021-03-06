#pragma once

#include "ofMain.h"
#include "Urg_driver.h"
#include "Connection_information.h"
#include "math_utilities.h"
#include <iostream>

using namespace qrk;
using namespace std;

class ofApp : public ofBaseApp{
	
	public:
		ofApp(int argc, char *argv[]);
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		enum { Capture_times = 100 };
		Urg_driver urg;
		vector<long> data,data1;
		vector<unsigned short> intensity;
		vector<long> Ddata;
};
