//
//  Person.h
//  emptyExample
//
//  Created by Daan on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"

/* class Person
 * this class represents a person connected to another person or the base triangle
 * it's functionality includes a 'hittest' with the pulse
 */

class Person {
    
public:
    void setup(int interval, ofPoint pos, int timeAtBeat, int id);
    void update();
    void draw();
    void beat();

    int id;
    ofPoint pos;
    
private:
    int     interval;
    float   distToCenterSquared;
    float   maxRadiusSquared;
    int     timeAtBeat;
    float   hitTime;
    bool    isHit;
    
    float   hitRadius;
    float   hitAlpha;
    ofPoint lastPos;
};
