#include "ofApp.h"
#include "Marker.h"

Marker::Marker(int gen, string status, string cluster, float lng, float lat)
{
    //-- matrix operations to have input data to match bottom-left origin of leaflet
    m.rotate(-90, 0, 0, 1);
    m.translate(-MAP_WIDTH/4, MAP_HEIGHT/4, 0);
    m.scale(2, 2, 2);
    ofPoint p = ofPoint(lng, lat);

    this->generation = gen;
    this->status = status;
    this->cluster = cluster;
    this->pos = p * m;
}