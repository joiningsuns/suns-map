#pragma once

#include "ofMain.h"

class Connection
{
public:
    Connection(ofVec3f a, ofVec3f b);
    void update();
    void draw();

private:
    ofVec3f start;
    ofVec3f middle;
    ofVec3f end;
    ofPath lineA;
    ofPath lineB;
};