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

private:
    ofMatrix4x4 m;
};