#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog() << "parsing "<< args.size() << "cli args...";
    for (int i = 0; i < args.size(); i++)
    {
        ofLog() << "- " << i << ": " << args.at(i);
    }

    if(ofGetEnv("MODE") == "prod" || ofGetEnv("MODE") == "dev"){
        MODE = ofGetEnv("MODE");
        ofLog() << "setting MODE to: " << MODE;
    }else{
        ofLogWarning() << "no environment found, defaulting to dev!";
        MODE = "dev";
    }

    server_settings.setPort(8080);
    server.setup(server_settings);
    server.postRoute().registerPostEvents(this);
    server.start();
    
    map.setup(MODE);
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    map.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
    {
    case 110:
        map.deformVertex();
        break;
    case 112:
        map.printMap();
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::onHTTPPostEvent(ofxHTTP::PostEventArgs &args)
{
    ofLogNotice() << "Not handling post events";
}

void ofApp::onHTTPFormEvent(ofxHTTP::PostFormEventArgs &args)
{
    ofLogNotice("ofApp::onHTTPFormEvent") << ofGetTimestampString();
    Poco::Net::NameValueCollection data = args.getForm();

    map.markers.clear();
    for (const auto &entry : data)
    {
        ofLog() << entry.first << ": " << entry.second;
        
        auto val = ofSplitString(entry.second, ",");

        int gen = ofToInt(val[0]);
        string status = ofToString(val[1]);
        string cluster = ofToString(val[2]);
        float lat = ofToFloat(val[3]);
        float lng = ofToFloat(val[4]);

        Marker m = Marker(gen, status, cluster, lat, lng);
        map.markers.push_back(m);
    }

    map.update();
}

void ofApp::onHTTPUploadEvent(ofxHTTP::PostUploadEventArgs &args)
{
    ofLogNotice() << "Not handling upload events";
}