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
    this->baseRadius = 80;
    this->baseOffset = ofRandom(20);
    this->radius = baseRadius + baseOffset;

    this->alpha = 50;

    draught_color = ofColor(200, 200, 100);
    symbiosis_color = ofColor(100, 200, 100);
    footprints_color = ofColor(200, 100, 100);
    first_times_color = ofColor(100, 100, 200);
    cracks_color = ofColor(200, 100, 200);

    for (float i = 0; i < TWO_PI; i += 0.01)
    {
        int r = radius * (1 + ofNoise(i + baseOffset));
        ofVec2f p = ofVec2f(sin(i) * r, cos(i) * r);

        // lerp to get a smooth wrap
        if (i > TWO_PI * 0.925f)
        {
            p.interpolate(points.at(0), (i / TWO_PI));
        }

        points.push_back(p);
    }

    for (int i = 0; i < points.size(); i++)
    {
        shape.curveTo(points.at(i));
    }
    shape.close();

    if (cluster == "Draught")
    {
        fillColor = ofColor(draught_color, alpha);
    }
    else if (cluster == "Symbiosis")
    {
        fillColor = ofColor(symbiosis_color, alpha);
    }
    else if (cluster == "Footprints")
    {
        fillColor = ofColor(footprints_color, alpha);
    }
    else if (cluster == "Combining First Times")
    {
        fillColor = ofColor(first_times_color, alpha);
    }
    else if (cluster == "Cracks")
    {
        fillColor = ofColor(cracks_color, alpha);
    }
    else
    {
        fillColor = ofColor(0, 0, 0);
    }
}

void Marker::update(int latestGen)
{
    alpha = 150 - (generation * 2);
    fillColor.a = alpha;
    generationGap = latestGen - generation;
}

void Marker::draw()
{
    shape.setFilled(true);
    shape.setFillColor(fillColor);

    ofPushMatrix();
    ofTranslate(pos);
    shape.draw();
}