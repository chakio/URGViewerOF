#include "ofApp.h"


//using namespace qrk;
//using namespace std;

namespace
{
	void print_data(const Urg_driver& urg,
		const vector<long>& data, long time_stamp)
	{
#if 1
		// Shows only the front step
		int front_index = urg.step2index(0);
		//cout << data[front_index] << " [mm], ("<< time_stamp << " [msec])   " << data.size() << "ko" << endl;

#else
		// Prints the X-Y coordinates for all the measurement points
		long min_distance = urg.min_distance();
		long max_distance = urg.max_distance();
		size_t data_n = data.size();
		for (size_t i = 0; i < data_n; ++i) {
			long l = data[i];
			if ((l <= min_distance) || (l >= max_distance)) {
				continue;
			}

			double radian = urg.index2rad(i);
			long x = static_cast<long>(l * cos(radian));
			long y = static_cast<long>(l * sin(radian));
			cout << "(" << x << ", " << y << ")" << endl;
		}
		cout << endl;
#endif
	}
}
//--------------------------------------------------------------

ofApp::ofApp(int argc, char *argv[])
{
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	Connection_information information(argc, argv);
	
	// Connects to the sensor

	if (!urg.open(information.device_or_ip_name(),
		information.baudrate_or_port_number(),
		information.connection_type())) {
		cout << "Urg_driver::open(): "
			<< information.device_or_ip_name() << ": " << urg.what() << endl;
		
	}

	// Gets measurement data
#if 1
	// Case where the measurement range (start/end steps) is defined
	urg.set_scanning_parameter(urg.deg2step(-90), urg.deg2step(+90), 0);//360digree/1024ŒÂ 180“x•ª‚Å513ŒÂ
#endif
	
	urg.start_measurement(Urg_driver::Distance, Urg_driver::Infinity_times, 0);
	
}
void ofApp::setup(){
	ofSetFrameRate(15);
	
}

//--------------------------------------------------------------
void ofApp::update() {
	long time_stamp = 0;
	if (!urg.get_distance(data, &time_stamp)) {
		cout << "Urg_driver::get_distance(): " << urg.what() << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPoint center(ofGetWidth()/2, ofGetHeight());
	ofSetColor(0, 0, 255);
	double Avedata = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] < 20)
		{
			data[i] = 5000;
		}
		if (data[i] > 300)
		{
			data[i] = 300;
		}
		ofDrawLine(center, ofPoint(ofGetWidth() / 2+data[i]*2*cos((data.size() - i)*0.35/180*M_PI+M_PI), data[i] *2* sin((data.size() - i)*0.35 / 180 * M_PI + M_PI)+ ofGetHeight()));
		
	}
	


 	ofSetColor(255, 0, 0);
	Ddata = data;
	data1 = data;

	for (int i = 1; i < data.size(); i++)
	{
		data1[i] = data1[i - 1] + (data[i] - data[i - 1])/2;
		Avedata += data1[i];
	}
	Avedata /= data.size();
	double pos = 0,posnum=0;
	for (int i = 0; i < data1.size(); i++)
	{
		if (data1[i] < Avedata)
		{
			pos += i;
			posnum++;
		}
	}
	pos /= posnum;
	for (int i = 1; i < data.size(); i++)
	{
		Ddata[i-1] = abs(data1[i - 1] - data1[i]);
	}
	
	ofSetColor(0, 0, 255);
	for (int i = 0; i < data.size(); i++)
	{

		ofDrawLine(center, ofPoint(ofGetWidth() / 2 + Ddata[i] * 2 * cos((data.size()-i)*0.35 / 180 * M_PI + M_PI), Ddata[i] * 2 * sin((data.size() - i)*0.35 / 180 * M_PI + M_PI) + ofGetHeight()));
	}
	if ((int)pos < 0)
	{
		pos=0;
	}
	if ((int)pos > data.size()-1)
	{
		pos = data.size()-1;
	}
	ofSetColor(255, 0, 0);
	ofDrawCircle(ofPoint(ofGetWidth() / 2 +data[(int)pos] * 2 * cos((data.size()-pos)*0.35 / 180 * M_PI+M_PI), data[(int)pos] * 2 * sin((data.size()-pos)*0.35 / 180 * M_PI + M_PI) + ofGetHeight()),30);

	stringstream ss;
	ss << "framerate: " << ofToString(ofGetFrameRate(), 0);
	ofDrawBitmapString(ss.str(), 10, 20);
	stringstream pp;
	pp << "position " << ofToString(pos*0.35);
	ofDrawBitmapString(pp.str(), 10, 35);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

