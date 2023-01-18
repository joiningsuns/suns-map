#include "ofApp.h"

ofColor Map::YELLOW = ofColor(201, 165, 72);
ofColor Map::BLUE = ofColor(126, 171, 195);
ofColor Map::GREEN = ofColor(131, 160, 116);
ofColor Map::ORANGE = ofColor(178, 96, 48);
ofColor Map::RED = ofColor(195, 73, 76);
ofColor Map::NONE = ofColor(255, 255, 255, 0);
ofColor Map::PINK = ofColor(250, 209, 225);
ofColor Map::MUD = ofColor(211, 174, 166);
ofColor Map::PURPLE = ofColor(124, 112, 130);
ofColor Map::CORAL = ofColor(255, 156, 150);
ofColor Map::SAND = ofColor(255, 251, 235);
ofColor Map::AMBER = ofColor(120, 53, 15, 50);

ofTexture Map::TEX_BARK;
ofTexture Map::TEX_BACTERIA;
ofTexture Map::TEX_CRACK;
ofTexture Map::TEX_SAND;
ofTexture Map::TEX_WIND;
ofTexture Map::TEX_WOOL;

void Map::setup(string _mode)
{
    mode = _mode;
    loadTextures();

    //-- allocating data for drawing into fbo
    fbo.allocate(MAP_WIDTH, MAP_HEIGHT, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();
}

void Map::update()
{

    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();

    //-- get latest generation
    for (Marker m : markers)
    {
        if (m.generation > latestGeneration)
        {
            latestGeneration = m.generation;
        };
    }

    for (Marker &m : markers)
    {
        m.update(latestGeneration);
    }

    canPrint = true;
}

void Map::draw()
{

    fbo.begin();
    drawBackground();

    ofPushMatrix();
    ofTranslate(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    for (Marker m : markers)
    {
        m.draw();
    }
    ofPopMatrix();
    fbo.end();

    if (canDraw)
    {
        fbo.draw(0, 0);
    }

    if (canPrint)
    {
        printMap();
        canPrint = false;
    }
}

void Map::drawBackground()
{
    ofBackground(ofColor::white);
    ofSetColor(ofColor::lightGray);
    ofFill();
    int gridStep = 15;
    int rad = 3;
    int pad = 10;
    for (int x = pad; x < MAP_WIDTH-pad; x += gridStep)
    {
        for (int y = pad; y < MAP_WIDTH-pad; y += gridStep)
        {
            ofDrawEllipse(x, y, rad, rad);
        }
    }
}

void Map::printMap()
{
    ofLog() << "printing image";
    ofPixels pix;
    ofImage img;
    pix.allocate(MAP_WIDTH, MAP_HEIGHT, OF_PIXELS_RGB);
    img.allocate(MAP_WIDTH, MAP_HEIGHT, OF_IMAGE_COLOR);

    fbo.readToPixels(pix);
    img.setFromPixels(pix);

    if (mode == "dev")
    {
        img.save("output/" + ofGetTimestampString() + "_map.png");
        img.save("output/map.png");
    }
    else if (mode == "prod")
    {
        img.save("/var/www/" + ofGetTimestampString() + "_map.png");
        img.save("/var/www/map.png");
    }
    else
    {
        ofLog() << "Wrong mode specified, not writing to file";
    }
}

void Map::loadTextures()
{
    if(TEX_BARK.bAllocated() == false){
        ofLoadImage(TEX_BARK, "textures/bark.png");
    }

    if(TEX_BACTERIA.bAllocated() == false){
        ofLoadImage(TEX_BACTERIA, "textures/bacteria.png");
    }

    if(TEX_CRACK.bAllocated() == false){
        ofLoadImage(TEX_CRACK, "textures/crack.png");
    }

    if(TEX_SAND.bAllocated() == false){
        ofLoadImage(TEX_SAND, "textures/sand.png");
    }

    if(TEX_WIND.bAllocated() == false){
        ofLoadImage(TEX_WIND, "textures/windbrush.png");
    }

    if(TEX_WOOL.bAllocated() == false){
        ofLoadImage(TEX_WOOL, "textures/wool_cloth.png");
    }
}