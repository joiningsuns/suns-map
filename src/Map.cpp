#include "ofApp.h"

void Map::setup()
{
    //-- allocating data for drawing into fbo
    fbo.allocate(MAP_WIDTH, MAP_HEIGHT, GL_RGB);
    fbo.begin();
    ofClear(255, 255, 255);
    fbo.end();

    ofPlanePrimitive plane(MAP_WIDTH, MAP_HEIGHT, ROWS_NUM, COLS_NUM, OF_PRIMITIVE_LINES);
    mesh = plane.getMesh();

    vector<ofColor> cs;
    mesh.setColorForIndices(0, mesh.getNumIndices(), ofColor::black);
    for (int i = 0; i < mesh.getNumColors(); i++)
    {
        ofColor c;
        float n = ofNoise(i * 0.001, (i % COLS_NUM) * 0.001) * 50 + 200;
        c.set(n, n, 255);
        cs.push_back(c);
        mesh.setColor(i, c);
    }

    ofLog() << "setting up mesh with " << mesh.getNumIndices() << " indices";
}

void Map::update()
{

    for (int i = 0; i < markers.size(); i++)
    {
        ofPoint m = markers[i].pos;
        // ofLog() << "marker: " << i << " x: " << m.x << " y: " << m.y;
        for (int j = 0; j < mesh.getNumVertices(); j++)
        {
            ofVec3f v = mesh.getVertex(j);
            if (m.distance(v) < AFFECTED_DISTANCE)
            {
                ofVec3f n(v.x, v.y, v.z + ofRandom(10, 30));
                // ofLog() << "setting #" << j << " to x:" << n.x << ", y:" << n.y << ", z:" << n.z;
                // mesh.setVertex(j, n);

                ofColor c(ofRandom(0, 25), ofRandom(0, 25), ofRandom(0, 25));
                if (markers[i].cluster == "Draught")
                {
                    c.set(ofRandom(100, 255), 0, 0);
                }
                else if (markers[i].cluster == "Symbiosis")
                {
                    c.set(0, ofRandom(100, 255), 0);
                }
                else if (markers[i].cluster == "Footprints")
                {
                    c.set(0, 0, ofRandom(100, 255));
                }
                else
                {
                }
                mesh.setColor(j, c);
            }
        }
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

    if (MODE == "dev")
    {
        img.save(ofGetTimestampString() + "_map.png");
    }
    else if (MODE == "prod")
    {
        img.save("/var/www/" + ofGetTimestampString() + "_map.png");
        img.save("/var/www/map.png");
    }else{
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