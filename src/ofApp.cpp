#include "ofApp.h"

#define ROWS_NUM 200
#define COLS_NUM 200

ofMesh mesh;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofPlanePrimitive plane;
    plane.set(1024, 768);
    plane.setPosition(512, 384, 0);
    plane.setResolution(ROWS_NUM, COLS_NUM);

    mesh = plane.getMesh();

    ofLog() << "manipulating " << mesh.getNumIndices() << " indices";

    // for (int i = 0; i < mesh.getNumIndices(); i++)
    // {
    //     ofPoint p = mesh.getVertex(i);
    //     ofPoint n(p.x, p.y, p.z + ofRandom(10));
    //     mesh.setVertex(i, n);
    // }
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofPushMatrix();
    ofTranslate(512, 384);
    mesh.drawWireframe();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    int i = int(ofRandom(mesh.getNumIndices() -10 ));
    ofVec3f p = mesh.getVertex(i);
    ofVec3f n(p.x, p.y, p.z + ofRandom(30));
    ofLog() << "setting #" << i << " to " << n.x << ", " << n.y << ", " << n.z;
    mesh.setVertex(i, n);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}