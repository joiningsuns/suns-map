#include "ofMain.h"
#include "Marker.h"

class Map
{
public:

    static ofColor YELLOW;
    static ofColor BLUE;
    static ofColor GREEN;
    static ofColor ORANGE;
    static ofColor RED;


    void setup(string mode);
    void update();
    void draw();
    void deformVertex();
    void printMap();

    vector<Marker> markers;

private:
    ofFbo fbo;
    ofMesh mesh;
    string mode;
    bool canPrint = false;
    int latestGeneration;
};