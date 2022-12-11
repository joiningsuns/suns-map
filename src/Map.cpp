#include "ofApp.h"

ofColor Map::YELLOW = ofColor(201, 165, 72);
ofColor Map::BLUE = ofColor(58, 131, 104);
ofColor Map::GREEN = ofColor(78, 127, 54);
ofColor Map::ORANGE = ofColor(178, 96, 48);
ofColor Map::RED = ofColor(195, 73, 76);

void Map::setup(string _mode)
{
    mode = _mode;

    //-- allocating data for drawing into fbo
    fbo.allocate(MAP_WIDTH, MAP_HEIGHT, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();

    ofPlanePrimitive plane(MAP_WIDTH, MAP_HEIGHT, ROWS_NUM, COLS_NUM, OF_PRIMITIVE_TRIANGLES);
    mesh = plane.getMesh();

    ofLog() << "setting up mesh with " << mesh.getNumIndices() << " indices";
}

void Map::update()
{

    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();

    for (int i = 0; i < markers.size(); i++)
    {
        if (markers[i].generation > latestGeneration)
        {
            latestGeneration = markers[i].generation;
        };
    }

    for (Marker m : markers)
    {
        m.update(latestGeneration);
    }

    canPrint = true;
}

void Map::draw()
{
    fbo.begin();
    ofBackground(255, 255, 255);
    ofPushMatrix();
    ofTranslate(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    mesh.draw();
    for (int i = 0; i < markers.size(); i++)
    {
        markers[i].draw();
    }
    ofPopMatrix();
    fbo.end();

    fbo.draw(0, 0);

    if (canPrint)
    {
        printMap();
        canPrint = false;
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
        img.save(ofGetTimestampString() + "_map.png");
        img.save("map.png");
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

void Map::deformVertex()
{
    ofLog() << "deforming vertex";
    int i = int(ofRandom(mesh.getNumIndices() - 10));
    ofVec3f p = mesh.getVertex(i);
    ofVec3f n(p.x, p.y, p.z + ofRandom(10, 30));
    ofLog() << "setting #" << i << " to " << n.x << ", " << n.y << ", " << n.z;
    mesh.setVertex(i, n);
}