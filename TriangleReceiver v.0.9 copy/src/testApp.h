#pragma once

#include "ofMain.h"
#include <vector>
#include "ofVectorMath.h"
#include "ofVec2f.h"
#include "ofVec3f.h"
#include "ofVec4f.h"
#include "ofMatrix3x3.h"
#include "ofMatrix4x4.h"
#include "ofQuaternion.h"
#include "TriangleReceiver.h"
#include "ofxImageSequence.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    float getMaximumTriangleArea();
    float getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C);
    float getTriangleArea(ofPoint A, ofPoint B, ofPoint C);
    ofPoint getTriangleCenter(ofPoint A, ofPoint B, ofPoint C);
    void drawShapeWithRotation(ofPoint centerPoint, int rotation, int radius, int layer);

    float maximumAreaThreshold;    
    vector<ofPoint> points;
    TriangleReceiver triangleReceiver;
    
    //png sequence
    ofxImageSequence sequence;
	ofImage background;
	bool playing;
    
    //img loader
    ofxImageSequence shape1;
	bool playingImg;
};

