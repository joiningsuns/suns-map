#include "ofApp.h"

#define ROWS_NUM 200
#define COLS_NUM 200

ofMesh mesh;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog() << "parsing cli args...";
    for (int i = 0; i < args.size(); i++)
    {
        ofLog() << "- " << i << ": " << args.at(i);
    }

    if (args.size() == 0)
    {
        ofLog() << "no arguments provided, loading defaults";
        filepath = ofToDataPath("dummy.json");
    }
    else
    {
        filepath = ofToDataPath(args.at(0));
    }

    //-- allocating data for drawing into fbo
    fbo.allocate(1000, 1000, GL_RGBA);

    //-- matrix operations to have input data to match bottom-left origin of leaflet
    m.rotate(-90, 0, 0, 1);
    m.translate(0, ofGetHeight(), 0);

    //-- load data points
    ofFile file(filepath);
    if (file.exists())
    {
        ofLog() << "found file " << filepath << ", loading...";
        input_data = ofLoadJson(file);
        for (int i = 0; i < input_data.size(); i++)
        {
            ofPoint p = ofPoint(input_data[i]["lat"], input_data[i]["lng"]);
            ofPoint p2 = p * m;
            markers.push_back(p2);
        }
    }
    else
    {
        ofLogWarning() << "could not open file!";
    }

    ofPlanePrimitive plane;
    plane.set(1000, 1000);
    plane.setResolution(ROWS_NUM, COLS_NUM);
    mesh = plane.getMesh();

    ofLog() << "setting up mesh with " << mesh.getNumIndices() << " indices";
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
    {
    case 110:
        deformVertex();
        break;
    case 112:
        printMap();
        break;
    default:
        ofLog() << "key pressed: " << key;
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::printMap()
{
    ofLog() << "printing image";
    ofPixels pix;
    fbo.readToPixels(pix);

    ofImage img;
    img.setFromPixels(pix);
    img.save("map.png");
}

void ofApp::deformVertex()
{
    ofLog() << "deforming vertex";
    int i = int(ofRandom(mesh.getNumIndices() - 10));
    ofVec3f p = mesh.getVertex(i);
    ofVec3f n(p.x, p.y, p.z + ofRandom(30));
    ofLog() << "setting #" << i << " to " << n.x << ", " << n.y << ", " << n.z;
    mesh.setVertex(i, n);
}