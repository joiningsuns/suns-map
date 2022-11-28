#pragma once

#include "ofMain.h"
#include "ofxHTTP.h"
#include "Map.h"

#define MAP_WIDTH 2000
#define MAP_HEIGHT 2000
#define ROWS_NUM 100
#define COLS_NUM 100
#define AFFECTED_DISTANCE 70
#define MODE "dev"

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

	Map map;
};
