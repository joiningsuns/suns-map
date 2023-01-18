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
    baseRadius = 30;
    baseOffset = ofRandom(20);
    radius = baseRadius + baseOffset;
    generationGap = 0;

    alpha = 255;
    blendAlpha = 50;
    blendColor = ofColor(255, 0, 0, blendAlpha);

    rotationFactor = ofRandom(360);
    scaleFactor = ofRandom(1, 2);

    texOffsetX = ofRandom(0, 400);
    texOffsetY = ofRandom(0, 400);

    draught_color = Map::MUD;
    symbiosis_color = Map::GREEN;
    footprints_color = Map::CORAL;
    first_times_color = Map::BLUE;
    cracks_color = Map::PURPLE;

    shape = determineShape(cluster);
    shape.scale(scaleFactor, scaleFactor);
    shape.setFilled(true);

    //-- set texture
    if (cluster == "Draught")
    {
        tex = Map::TEX_BACTERIA;
    }
    else if (cluster == "Symbiosis")
    {
        tex = Map::TEX_BARK;
    }
    else if (cluster == "Footprints")
    {
        tex = Map::TEX_CRACK;
    }
    else if (cluster == "Combining First Times")
    {
        tex = Map::TEX_SAND;
    }
    else if (cluster == "Cracks")
    {
        tex = Map::TEX_WIND;
    }
    else if (cluster == "Prompts")
    {
        tex = Map::TEX_WOOL;
    }
    else
    {
        ofLog() << "cluster not recognized: " << cluster;
        tex = Map::TEX_BACTERIA;
    }

    mesh = shape.getTessellation();
    for (auto &v : mesh.getVertices())
    {
        mesh.addTexCoord(tex.getCoordFromPoint(v.x + texOffsetX, v.y + texOffsetY));
        mesh.addColor(ofColor::white);
    }
}

void Marker::update(int latestGen)
{
    // alpha = ofClamp(50 - (generation * 2), 5, 50);
    // fillColor.a = alpha;
    // generationGap = latestGen - generation;

    shape.setFillColor(blendColor);
}

void Marker::draw()
{
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(rotationFactor);
    ofScale(scaleFactor);

    tex.bind();
    mesh.draw();
    tex.unbind();

    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    shape.draw();
    ofDisableBlendMode();

    ofPopMatrix();
}

ofPath Marker::determineShape(string cluster)
{
    ofPath p;

    if (cluster == "Draught")
    {
        p.circle(0, 0, 30);
    }
    else if (cluster == "Symbiosis")
    {
        p.moveTo(0, 0);
        p.curveTo(10, 10);
        p.curveTo(30, 5);
        p.curveTo(80, 20);
        p.curveTo(90, 130);
        p.curveTo(105, 210);
        p.curveTo(60, 180);
        p.curveTo(35, 70);
        p.curveTo(10, 10);
        p.close();
    }
    else if (cluster == "Footprints")
    {
        p.rectangle(0, 0, 40, 40);
    }
    else if (cluster == "Combining First Times")
    {
        p.triangle(ofVec2f(-10, 0), ofVec2f(5, 5), ofVec2f(10, 0));
    }
    else if (cluster == "Cracks")
    {
        p.ellipse(ofVec2f(0, 0), 40, 10);
    }
    else if (cluster == "Prompts")
    {
        p.rectangle(0, 0, 80, 40);
    }
    else
    {
        ofLog() << "cluster not recognized: " << cluster;
        p.triangle(ofVec2f(-30, 0), ofVec2f(5, 5), ofVec2f(30, 0));
    }

    return p;
}