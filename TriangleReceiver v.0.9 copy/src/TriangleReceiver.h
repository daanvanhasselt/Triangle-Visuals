//
//  TriangleReceiver.h
//  emptyExample
//
//  Created by Daan on 11/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "Pulse.h"
#include "ofxOsc.h"
#include <list>
#include "Person.h"

enum TriangleState {
	TriangleStateDrawFirstLayer,
	TriangleStateDrawSecondLayer,
	TriangleStateDrawThirdLayer,
	TriangleStateDrawFourthLayer,
	TriangleStateDrawFifthLayer
};

struct Triangle {
    int id;
    ofPoint A;
	float tensionA;
    ofPoint B;
	float tensionB;
    ofPoint C;
	float tensionC;
	
    float tension;
    float radius;
    float radius1;
    float radius2;
    float radius3;
    float radius4;
    float radius5;
    float lengthOfAB;
    float lengthOfBC;
    float lengthOfCA;
    ofPoint center;
	TriangleState state;
};


/* class TriangleReceiver
 * this class provides a simple interface for receiving data formatted in the Triangle protocol
 * it receives the data via OSC and keeps a list of triangles
 */

class TriangleReceiver {
    
public:
    void setup(int port);
    void update();
    void draw();
    
    Pulse pulse;    
    list<Triangle*> triangles;
    list<Person*> persons;
    
private:
    ofxOscReceiver receiver;
};
