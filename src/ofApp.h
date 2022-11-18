#pragma once

#include "ofMain.h"
#include "ofxHTTP.h"
#include "Map.h"

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

	void onHTTPPostEvent(ofxHTTP::PostEventArgs &evt);
	void onHTTPFormEvent(ofxHTTP::PostFormEventArgs &evt);
	void onHTTPUploadEvent(ofxHTTP::PostUploadEventArgs &evt);

	ofxHTTP::SimplePostServer server;
	ofxHTTP::SimplePostServerSettings server_settings;

	vector<string> args;

	string filepath;
	ofJson input_data;

	Map map;
};
