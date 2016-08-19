#include "ofApp.h"
using namespace ofxCv;
using namespace cv;
//http://www.deathbysoftware.com/colors/index.html

void rgb2ryb(unsigned char &r, unsigned char g, unsigned char &b, unsigned char&y) {
	// Remove the white from the color
	unsigned char iWhite = min(r, min(g, b));

	r -= iWhite;
	g -= iWhite;
	b -= iWhite;

	unsigned char iMaxGreen = max(r, max(g, b));

	// Get the yellow out of the red+green

	y = min(r, g);

	r -= y;
	g -= y;

	// If this unfortunate conversion combines blue and green, then cut each in half to
	// preserve the value's maximum range.
	if (b > 0 && b > 0)	{
		b /= 2;
		g /= 2;
	}

	// Redistribute the remaining green.
	y += g;
	b += g;

	// Normalize to values.
	unsigned char iMaxYellow = max(r, max(y, b));

	if (iMaxYellow > 0)	{
		unsigned char iN = iMaxGreen / iMaxYellow;

		r *= iN;
		y *= iN;
		b *= iN;
	}

	// Add the white back in.
	r += iWhite;
	y += iWhite;
	b += iWhite;

	//this.pRyb = [Math.floor(iRed), Math.floor(iYellow), Math.floor(iBlue)];
}
void ofApp::setup() {
	cam.setup(640, 480);
	contourFinder.setMinAreaRadius(10);
	contourFinder.setMaxAreaRadius(500);// initial was 150
	//contourFinder.setInvert(true); // find black instead of white

	gui.setup();
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(trackHs.set("Track Hue/Saturation", false));
	gui.add(hue.set("hue", 0, 0, 255));
	gui.add(brightness.set("brightness", 0, 0, 255));
	gui.add(saturation.set("saturation", 0, 0, 255));
	gui.add(r.set("r", 0, 0, 255));
	gui.add(g.set("g", 0, 0, 255));
	gui.add(b.set("b", 0, 0, 255));
	gui.add(r2.set("r2", 0, 0, 255));
	gui.add(y.set("y", 0, 0, 255));
	gui.add(b2.set("b2", 0, 0, 255));
}

void ofApp::update() {
	cam.update();
	if (cam.isFrameNew()) {
		contourFinder.setTargetColor(targetColor, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_HSV);
		contourFinder.setThreshold(threshold);
		contourFinder.findContours(cam);
	}
}

void ofApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	//http://www.creativeapplications.net/tutorials/arduino-servo-opencv-tutorial-openframeworks/
	ofSetLineWidth(2);
	ofPushStyle();
	ofFill();
	ofSetColor(255, 0, 0);
	for (int i = 0; i < (int)contourFinder.getPolylines().size(); i++) {
		contourFinder.getPolylines()[i].draw();
		//ofDrawRectangle(toOf(contourFinder.getBoundingRect(i)));
	}
	ofPopStyle();
	//contourFinder.draw();

	gui.draw();

	ofTranslate(8, 275);
	ofFill();
	ofSetColor(0);
	ofDrawRectangle(-3, -3, 64 + 6, 64 + 6);
	ofSetColor(targetColor);
	ofDrawRectangle(0, 0, 64, 64);
	hue = targetColor.getHue();
	brightness = targetColor.getBrightness();
	saturation = targetColor.getSaturation();
	unsigned char x1, x2, x3;
	x1 = r = targetColor.r;
	g = targetColor.g;
	x2 = b = targetColor.b;
	
	rgb2ryb(x1, g, x2, x3);
	r2 = x1;
	b2 = x2;
	y = x3;
}

void ofApp::mousePressed(int x, int y, int button) {
	targetColor = cam.getPixels().getColor(x, y);
}
