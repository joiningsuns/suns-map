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

    generationGap = 0;

    alpha = 255;
    blendAlpha = 250;
    blendColor = determineColor(status);

    rotationFactor = ofRandom(360);
    //-- todo
    //-- get the age of the marker
    //-- determine scale factor based on age and status (old open = small, old completed = large)
    scaleFactor = ofRandom(1.5, 2);

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
    tex = determineTexture(cluster);

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
        p.curveTo(0, 30); //-- start from the end
        p.curveTo(20, 25);
        p.curveTo(45, 10);
        p.curveTo(30, -80);
        p.curveTo(10, -45);
        p.curveTo(-35, -40);
        p.curveTo(-15, -5);
        p.curveTo(-20, 10);
        p.curveTo(0, 30);
        p.curveTo(20, 25);
        p.curveTo(20, 25);
    }
    else if (cluster == "Symbiosis")
    {
        p.curveTo(-10, -40);
        p.curveTo(0, -40);
        p.curveTo(-20, -20);
        p.curveTo(-10, 0);
        p.curveTo(-20, 20);
        p.curveTo(-40, 30);
        p.curveTo(-20, 0);
        p.curveTo(-25, -30);
        p.curveTo(-10, -40);
        p.curveTo(0, -40);
        p.curveTo(0, -40);
        p.moveTo(0, -40);

        p.moveTo(20, -35);
        p.moveTo(20, -35);
        p.curveTo(20, -40);
        p.curveTo(6, -20);
        p.curveTo(16, 0);
        p.curveTo(0, 20);
        p.curveTo(-20, 30);
        p.curveTo(0, 0);
        p.curveTo(-5, -30);
        p.curveTo(10, -35);
        p.curveTo(20, -35);
        p.curveTo(20, -35);

        p.scale(2, 2);
    }
    else if (cluster == "Footprints")
    {
        p.circle(0, 0, 20);
        p.circle(30, 25, 22);
        p.circle(-20, 55, 32);
        p.circle(20, -55, 35);
    }
    else if (cluster == "Combining First Times")
    {
        p.triangle(ofVec2f(-10, 0), ofVec2f(5, 5), ofVec2f(10, 0));
    }
    else if (cluster == "Cracks")
    {
        p.lineTo(50, -40);
        p.lineTo(30, -30);
        p.lineTo(15, -20);
        p.lineTo(-15, 40);
        p.lineTo(-30, 5);
        p.lineTo(-15, 15);
        p.lineTo(-5, -5);
        p.lineTo(5, -35);
        p.lineTo(50, -40);
    }
    else if (cluster == "Prompts")
    {
        p.circle(0, 0, ofRandom(70, 90));
    }
    else
    {
        ofLog() << "cluster not recognized: " << cluster;
        p.triangle(ofVec2f(-30, 0), ofVec2f(5, 5), ofVec2f(30, 0));
    }

    return p;
}

ofTexture Marker::determineTexture(string cluster)
{
    ofTexture t;
    if (cluster == "Draught")
    {
        t = Map::TEX_SAND;
    }
    else if (cluster == "Symbiosis")
    {
        t = Map::TEX_BARK;
    }
    else if (cluster == "Footprints")
    {
        t = Map::TEX_BACTERIA;
    }
    else if (cluster == "Combining First Times")
    {
        t = Map::TEX_WOOL;
    }
    else if (cluster == "Cracks")
    {
        t = Map::TEX_CRACK;
    }
    else if (cluster == "Prompts")
    {
        t = Map::TEX_WIND;
    }
    else
    {
        ofLog() << "cluster not recognized: " << cluster;
        t = Map::TEX_BACTERIA;
    }

    return t;
}

ofColor Marker::determineColor(string status)
{
    ofColor c;
    if (status == "open")
    {
        c = ofColor(100, 200, 100, blendAlpha);
    }
    else if (status == "pending")
    {
        c = ofColor(200, 200, 200, blendAlpha);
    }
    else if (status == "completed")
    {
        c = ofColor(100, 100, 100, blendAlpha);
    }
    else if (status == "sacrificed")
    {
        c = ofColor(230, 230, 230, blendAlpha);
    }
    else
    {
        ofLog() << "status not recognized: " << status;
        c = ofColor(0, 0, 0, 255);
    }

    return c;
}