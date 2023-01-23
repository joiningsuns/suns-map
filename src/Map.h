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

    static ofTexture TEX_BARK;
    static ofTexture TEX_BACTERIA;
    static ofTexture TEX_CRACK;
    static ofTexture TEX_SAND;
    static ofTexture TEX_WIND;
    static ofTexture TEX_WOOL;

    static ofTexture MASK_BARK;
    static ofTexture MASK_BACTERIA;
    static ofTexture MASK_CRACK;
    static ofTexture MASK_SAND;
    static ofTexture MASK_WIND;
    static ofTexture MASK_WOOL;

    void setup(string mode);
    void update();
    void draw();
    void drawBackground();
    void printMap();
    void loadTextures();
    void loadMasks();

    vector<MapMarker> markers;
    vector<Connection> connections;

private:
    ofFbo fbo;
    string mode;
    bool canPrint = false;
    bool canDraw = true;
    int latestGeneration;
    int markerDistance = 900;
};