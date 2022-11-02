#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
	ofApp(vector<string> args)
	{
		this->args = args;
	}

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void deformVertex();
	void printMap();

	vector<string> args;

	string filepath;
	ofJson input_data;
	vector<ofPoint> markers;

	ofMatrix4x4 m; 
	ofFbo fbo;
};
