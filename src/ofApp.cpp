#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofLog() << "parsing cli args...";
    for (int i = 0; i < args.size(); i++)
    {
        ofLog() << "- " << i << ": " << args.at(i);
    }

    if (args.size() == 0)
    {
        ofLog() << "no filepath provided, loading defaults";
        filepath = ofToDataPath("dummy.json");
    }
    else
    {
        filepath = ofToDataPath(args.at(0));
    }

    server_settings.setPort(8080);
    server.setup(server_settings);
    server.postRoute().registerPostEvents(this);
    server.start();
    

    //-- load data points
    ofFile file(filepath);
    if (file.exists())
    {
        input_data = ofLoadJson(file);
        map.setup(input_data);
    }
    else
    {
        ofLogWarning() << "could not open file!";
    }
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
    ofLogNotice("ofApp::onHTTPFormEvent") << "";
    Poco::Net::NameValueCollection data = args.getForm();
    for (const auto &entry : data)
    {
        ofLog() << entry.first << ": " << entry.second;
    }
}

void ofApp::onHTTPUploadEvent(ofxHTTP::PostUploadEventArgs &args)
{
    ofLogNotice() << "Not handling upload events";
}