#include "ofApp.h"

#define ROWS_NUM 200
#define COLS_NUM 200

void Map::setup(ofJson data)
{
    for (int i = 0; i < data.size(); i++)
    {
        ofPoint p = ofPoint(data[i]["lat"], data[i]["lng"]);
        ofPoint p2 = p * m;
        markers.push_back(p2);
    }

    //-- allocating data for drawing into fbo
    fbo.allocate(1000, 1000, GL_RGBA);

    //-- matrix operations to have input data to match bottom-left origin of leaflet
    m.rotate(-90, 0, 0, 1);
    m.translate(0, ofGetHeight(), 0);

    ofPlanePrimitive plane;
    plane.set(1000, 1000);
    plane.setResolution(ROWS_NUM, COLS_NUM);
    mesh = plane.getMesh();

    ofLog() << "setting up mesh with " << mesh.getNumIndices() << " indices";
}

void Map::draw()
{
    fbo.begin();
    ofPushMatrix();
    ofTranslate(500, 500);
    mesh.drawWireframe();
    ofPopMatrix();

    for (int i = 0; i < markers.size(); i++)
    {
        ofDrawCircle(markers[i], 20);
    }
    fbo.end();

    fbo.draw(0, 0);
}


void Map::printMap()
{
    ofLog() << "printing image";
    ofPixels pix;
    fbo.readToPixels(pix);

    ofImage img;
    img.setFromPixels(pix);
    img.save("map.png");
}

void Map::deformVertex()
{
    ofLog() << "deforming vertex";
    int i = int(ofRandom(mesh.getNumIndices() - 10));
    ofVec3f p = mesh.getVertex(i);
    ofVec3f n(p.x, p.y, p.z + ofRandom(30));
    ofLog() << "setting #" << i << " to " << n.x << ", " << n.y << ", " << n.z;
    mesh.setVertex(i, n);
}