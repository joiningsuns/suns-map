#include "ofMain.h"

class Map
{
public:
    void setup(ofJson);
    void update();
    void draw();
    void deformVertex();
    void printMap();

    vector<ofPoint> markers;
    ofMatrix4x4 m;
    ofFbo fbo;
    ofMesh mesh;
};