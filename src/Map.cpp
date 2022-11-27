#include "ofApp.h"

void Map::setup(ofJson data)
{
    for (int i = 0; i < data.size(); i++)
    {
        Marker marker = Marker(data[i]["generation"], data[i]["status"], data[i]["cluster"], data[i]["lat"], data[i]["lng"]);

        markers.push_back(marker);
    }

    //-- allocating data for drawing into fbo
    fbo.allocate(MAP_WIDTH, MAP_HEIGHT, GL_RGBA);

    ofPlanePrimitive plane(MAP_WIDTH, MAP_HEIGHT, ROWS_NUM, COLS_NUM, OF_PRIMITIVE_LINES);
    mesh = plane.getMesh();

    vector<ofColor> cs;
    mesh.setColorForIndices(0, mesh.getNumIndices(), ofColor::black);
    for (int i = 0; i < mesh.getNumColors(); i++)
    {
        ofColor c;
        float n = ofNoise(i*0.001, (i % COLS_NUM)*0.001)*50 + 200;
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

    if(canPrint){
        printMap();
        canPrint = false;
    }
}

void Map::printMap()
{
    ofLog() << "printing image";
    ofPixels pix;
    ofImage img;

    fbo.readToPixels(pix);
    img.setFromPixels(pix);
    img.setImageType(OF_IMAGE_COLOR_ALPHA);
    img.save(ofGetTimestampString()+"_map.png");
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