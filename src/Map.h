#include "ofMain.h"
#include "Marker.h"
#include "Connection.h"

class Map
{
public:

    static ofColor YELLOW;
    static ofColor BLUE;
    static ofColor GREEN;
    static ofColor ORANGE;
    static ofColor RED;
    static ofColor NONE;
    static ofColor PINK;
    static ofColor MUD;
    static ofColor PURPLE;
    static ofColor CORAL;
    static ofColor SAND;
    static ofColor AMBER;


    void setup(string mode);
    void update();
    void draw();
    void drawBackground();
    void printMap();

    vector<MarkerClass> markers;
    vector<Connection> connections;

private:
    ofFbo fbo;
    string mode;
    bool canPrint = false;
    bool canDraw = true;
    int latestGeneration;
    int markerDistance = 900;
};