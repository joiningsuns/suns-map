#include "ofApp.h"
#include "Connection.h"

Connection::Connection(ofVec3f a, ofVec3f b)
{
    start = a;
    end = b;
    middle = start.getMiddle(end);
    start.interpolate(middle, 0.5);
    end.interpolate(middle, 0.5);

    lineA.lineTo(middle);
    lineA.lineTo(start);
    lineA.close();

    lineB.lineTo(middle);
    lineB.lineTo(end);
    lineB.close();
}

void Connection::update()
{
}

void Connection::draw()
{
    lineA.setStrokeWidth(2);
    lineA.setStrokeColor(ofColor(0, 0, 0, 20));
    lineA.setFilled(false);
    lineA.draw();

    lineB.setStrokeWidth(6);
    lineB.setStrokeColor(ofColor(0, 0, 0, 20));
    lineB.setFilled(false);
    lineB.draw();
}