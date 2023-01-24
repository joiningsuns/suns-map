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

    texOffsetX = ofRandom(80, 400);
    texOffsetY = ofRandom(80, 400);

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

    if (cluster == "Drought")
    {
        vector<ofPoint> pts;
        pts.push_back(ofPoint(0, 30));
        pts.push_back(ofPoint(20, 25));
        pts.push_back(ofPoint(45, 10));
        pts.push_back(ofPoint(30, -60));
        pts.push_back(ofPoint(10, -45));
        pts.push_back(ofPoint(-35, -40));
        pts.push_back(ofPoint(-15, -5));
        pts.push_back(ofPoint(-20, 10));
        pts.push_back(ofPoint(0, 30));
        pts.push_back(ofPoint(20, 25));
        pts.push_back(ofPoint(20, 25));

        p.curveTo(pts.at(0));
        p.curveTo(pts.at(1));
        for (int i = 2; i < pts.size() - 3; i++)
        {
            float factor = ofRandom(0.9, 1.6);
            p.curveTo(pts.at(i) * factor);
        }
        p.curveTo(pts.at(pts.size() - 3));
        p.curveTo(pts.at(pts.size() - 2));
        p.curveTo(pts.at(pts.size() - 1));
    }
    else if (cluster == "Symbiosis")
    {
        // offset rotation and scale
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

        float scaleFactorFirst = ofRandom(0.8, 1.2);
        p.scale(scaleFactorFirst, scaleFactorFirst);
        p.rotateDeg(ofRandom(90), ofVec2f(0, 1));

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

        float scaleFactor = ofRandom(1.2, 1.8);
        p.scale(scaleFactor, scaleFactor);
    }
    else if (cluster == "Footprints")
    {
        vector<ofPoint> locations;
        locations.push_back(ofPoint(0, 0));
        locations.push_back(ofPoint(30, 25));
        locations.push_back(ofPoint(-20, 55));
        locations.push_back(ofPoint(20, -55));
        locations.push_back(ofPoint(-20, -45));
        locations.push_back(ofPoint(20, 45));

        int max = ofRandom(4, locations.size());
        for (int i = 0; i < max; i++)
        {
            float rad = ofRandom(15, 35);
            p.circle(locations.at(i), rad);
        }
    }
    else if (cluster == "Combining First Times")
    {
        p.ellipse(ofVec2f(-15 + ofRandom(5), 0 + ofRandom(5)), 60, 80 + ofRandom(15));
        p.ellipse(ofVec2f(15 + ofRandom(5), 12 + ofRandom(5)), 65, 70 + ofRandom(20));
    }
    else if (cluster == "Cracks")
    {
        //-- add another branch and randomize the tips
        float f = ofRandomf();
        if (f < 0)
        {
            p.lineTo(-50, -40);
            p.lineTo(15, -20);
            p.lineTo(30, -30);
            p.lineTo(10, -5);
            p.lineTo(22, 30);
            p.lineTo(2, -5);
            p.lineTo(-15, 40);
            p.lineTo(-30, 5);
            p.lineTo(-15, 15);
            p.lineTo(-5, -5);
            p.lineTo(5, -35);
            p.lineTo(-50, -40);
        }
        else
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
    if (cluster == "Drought")
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