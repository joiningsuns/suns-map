#pragma once

#include "ofMain.h"

class MapMarker
{
public:
    int generation;
    string status;
    string cluster;
    ofPoint pos;

    MapMarker(int gen, string status, string cluster, float lat, float lng);

    void update(int latestGen);
    void draw();

    int alpha;
    int generationGap;

    float rotationFactor;
    float scaleFactor;

    float getWidth();
    float getHeight();

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

    ofTexture tex;
    ofMesh mesh;

    ofTexture mask;

    ofFbo temp;

private:
    ofMatrix4x4 m;
    ofPath determineShape(string cluster);
    ofTexture determineTexture(string cluster);
    ofTexture determineMask(string cluster);
    ofColor determineColor(string status);
};