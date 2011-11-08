//
//  Pulse.cpp
//  emptyExample
//
//  Created by Daan on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Pulse.h"

Pulse::Pulse(){
    isSetup = false;
}

void Pulse::setup(int _interval){
    interval = _interval;
    currentRadius = 0;
    lastBeatTime = ofGetElapsedTimeMillis();
    maxRadius = 0.5 * ofDist(0, 0, ofGetWidth(), ofGetHeight());    // diagonal of screen
    radiusAdditionPerMs = maxRadius / interval;
    lastUpdateTime = ofGetElapsedTimeMillis();
    isSetup = true;
}

void Pulse::update(){
    if(!isSetup)
        return;
    
    int currentTime = ofGetElapsedTimeMillis();
    float addition = (currentTime - lastUpdateTime) * radiusAdditionPerMs;
    currentRadius += addition;
    while(currentRadius >= maxRadius)
        currentRadius -= maxRadius;
    
    lastUpdateTime = ofGetElapsedTimeMillis();
}

void Pulse::draw(){
    ofNoFill();
    ofSetColor(255, 255, 0);
    ofSetLineWidth(4);
    ofSetCircleResolution(100);
    ofCircle(ofGetWidth() / 2.0, ofGetHeight() / 2.0, currentRadius);
}

void Pulse::beat(){
    currentRadius = 0;
    lastBeatTime = ofGetElapsedTimeMillis();
}