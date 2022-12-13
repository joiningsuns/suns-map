#include "ofApp.h"
#include "Marker.h"

Marker::Marker(int gen, string status, string cluster, float lng, float lat)
{
    generation = gen;
    status = status;
    cluster = cluster;

    //-- matrix operations to have input data to match bottom-left origin of leaflet
    m.rotate(-90, 0, 0, 1);
    m.translate(-MAP_WIDTH / 4, MAP_HEIGHT / 4, 0);
    m.scale(2, 2, 2);
    ofVec3f p = ofVec3f(lng, lat);

    pos = p * m;
    baseRadius = 80;
    baseOffset = ofRandom(20);
    radius = baseRadius + baseOffset;
    generationGap = 0;

    alpha = 50;

    draught_color = Map::YELLOW;
    symbiosis_color = Map::GREEN;
    footprints_color = Map::RED;
    first_times_color = Map::BLUE;
    cracks_color = Map::ORANGE;

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
        ofLog() << "cluster not recognized: " << cluster;
        fillColor = ofColor(0, 0, 0);
    }
}

void Marker::update(int latestGen)
{
    alpha = 100 - (generation * 2);
    fillColor.a = alpha;
    generationGap = latestGen - generation;

    rings.clear();
    int i = 0;
    while (i < generationGap)
    {
        ofPath r;
        for (int j = 0; j < points.size(); j++)
        {
            r.curveTo(points.at(j));
        }
        float s = 1 + (i + 1) * 0.3;
        r.scale(s, s);
        r.setStrokeWidth(2);
        r.setFilled(false);
        r.setStrokeColor(fillColor);
        r.close();
        rings.push_back(r);
        i++;
    }
}

void Marker::draw()
{
    ofPushMatrix();
    ofTranslate(pos);

    //-- draw the marker
    shape.setFilled(true);
    shape.setFillColor(fillColor);
    shape.setStrokeColor(Map::NONE);
    shape.draw();

    // -- draw the generation lines
    for (auto r : rings)
    {
        r.draw();
    }

    ofPopMatrix();
}