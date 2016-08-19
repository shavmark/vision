#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void mousePressed(int x, int y, int button);

	ofVideoGrabber cam;
	ofxCv::ContourFinder contourFinder;
	ofColor targetColor;

	ofxPanel gui;
	ofParameter<float> threshold;
	ofParameter<bool> trackHs;
	ofParameter<float>hue;
	ofParameter<float>brightness;
	ofParameter<float>saturation;
	ofParameter<unsigned char>r;
	ofParameter<unsigned char>g;
	ofParameter<unsigned char>b;
	ofParameter<unsigned char>r2;
	ofParameter<unsigned char>y;
	ofParameter<unsigned char>b2;
};
