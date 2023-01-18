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
    ofPath determineShape(string cluster);

    float radius;
    float baseRadius;
    float baseOffset;
    int alpha;
    int generationGap;

    float rotationFactor;
    float scaleFactor;

    float texOffsetX;
    float texOffsetY;

    ofColor draught_color;
    ofColor symbiosis_color;
    ofColor footprints_color;
    ofColor first_times_color;
    ofColor cracks_color;

    ofColor blendColor;
    int blendAlpha;
    ofPath shape;
    ofMesh mesh;

    ofTexture tex;
private:
    ofMatrix4x4 m;
};