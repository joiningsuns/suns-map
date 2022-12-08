#include "ofApp.h"
#include "Marker.h"

Marker::Marker(int gen, string status, string cluster, float lng, float lat)
{
    //-- matrix operations to have input data to match bottom-left origin of leaflet
    m.rotate(-90, 0, 0, 1);
    m.translate(-MAP_WIDTH / 4, MAP_HEIGHT / 4, 0);
    m.scale(2, 2, 2);
    ofPoint p = ofPoint(lng, lat);

    this->generation = gen;
    this->status = status;
    this->cluster = cluster;
    this->pos = p * m;
    this->radius = 80 + ofRandom(30);

    draught_color = ofColor(200, 200, 100, 150);
    symbiosis_color = ofColor(100, 200, 100, 150);
    footprints_color = ofColor(200, 100, 100, 150);
    first_times_color = ofColor(100, 100, 200, 150);
    cracks_color = ofColor(200, 100, 200, 150);
}

void Marker::draw()
{
    if (cluster == "Draught")
    {
        ofSetColor(draught_color);
    }
    else if (cluster == "Symbiosis")
    {
        ofSetColor(symbiosis_color);
    }
    else if (cluster == "Footprints")
    {
        ofSetColor(footprints_color);
    }
    else if (cluster == "Combining First Times")
    {
        ofSetColor(first_times_color);
    }
    else if (cluster == "Cracks")
    {
        ofSetColor(cracks_color);
    }

    ofFill();

    ofDrawEllipse(pos, radius, radius);
}