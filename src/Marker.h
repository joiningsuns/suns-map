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

    void draw();

    float radius;

    ofColor draught_color;
    ofColor symbiosis_color;
    ofColor footprints_color;
    ofColor first_times_color;
    ofColor cracks_color;

private:
    ofMatrix4x4 m;
};