#pragma once

#include "ofMain.h"
#include "ofxHTTP.h"
#include "Map.h"

#define MAP_WIDTH 5000
#define MAP_HEIGHT 5000
#define ROWS_NUM 100
#define COLS_NUM 100
#define AFFECTED_DISTANCE 70

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
	void addMarkers(int num);

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void onHTTPPostEvent(ofxHTTP::PostEventArgs &evt);
	void onHTTPFormEvent(ofxHTTP::PostFormEventArgs &evt);
	void onHTTPUploadEvent(ofxHTTP::PostUploadEventArgs &evt);

	string MODE;
	ofxHTTP::SimplePostServer server;
	ofxHTTP::SimplePostServerSettings server_settings;

	vector<string> args;
	vector<string> clusters;
	vector<string> statuses;

	Map map;
};
