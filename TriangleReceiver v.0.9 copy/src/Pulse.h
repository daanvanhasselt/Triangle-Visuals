//
//  Pulse.h
//  emptyExample
//
//  Created by Daan on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include <list>

/* class Pulse
 * this class represents a pulse going through the field
 * TriangleReceiver class receives beat information over OSC (interval time and 'isbeat')
 */

class Pulse {
    
public:
    Pulse();
    void setup(int interval);
    void update();
    void draw();
    
    void beat();
    
    float currentRadius;
    int interval;
    int lastBeatTime;
    
private:
    bool  isSetup;
    
    float radiusAdditionPerMs;
    float maxRadius;
    int   lastUpdateTime;
};
