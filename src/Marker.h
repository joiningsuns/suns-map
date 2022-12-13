#pragma once

#include "ofMain.h"

class Marker
{
public:
    int generation;
    string status;
    string cluster;
    ofPoint pos;

    Marker(int gen, string status, string cluster, float lat, float lng);

    void update(int latestGen);
    void draw();

    float radius;
    float baseRadius;
    float baseOffset;
    int alpha;
    int generationGap;

    ofColor draught_color;
    ofColor symbiosis_color;
    ofColor footprints_color;
    ofColor first_times_color;
    ofColor cracks_color;

    ofColor fillColor;
    ofPath shape;
    vector<ofPath> rings;
    vector<ofVec2f> points;
private:
    ofMatrix4x4 m;
};