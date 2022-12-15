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


    void setup(string mode);
    void update();
    void draw();
    void drawBackground();
    void printMap();

    vector<Marker> markers;
    vector<Connection> connections;

private:
    ofFbo fbo;
    string mode;
    bool canPrint = false;
    bool canDraw = true;
    int latestGeneration;
};