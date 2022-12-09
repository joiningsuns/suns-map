#include "ofMain.h"
#include "Marker.h"

class Map
{
public:
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