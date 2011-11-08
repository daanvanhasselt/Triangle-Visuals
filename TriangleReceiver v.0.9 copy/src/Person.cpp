//
//  Person.cpp
//  emptyExample
//
//  Created by Daan on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "Person.h"

void Person::setup(int _interval, ofPoint _pos, int _timeAtBeat, int _id){
    interval = _interval;
    pos = _pos;
    timeAtBeat = _timeAtBeat;
    id = _id;
    isHit = false;

    maxRadiusSquared = 0.5 * ofDist(0, 0, ofGetWidth(), ofGetHeight());    // diagonal of screen (squared)
    
    distToCenterSquared = ofDist(pos.x, pos.y, ofGetWidth() / 2.0, ofGetHeight() / 2.0);
    hitTime = ( (distToCenterSquared / maxRadiusSquared) * interval ) + timeAtBeat;
    
    hitRadius = 25;
    hitAlpha = 0;
}

void Person::update(){
    if (lastPos != pos) {
        distToCenterSquared = ofDist(pos.x, pos.y, ofGetWidth() / 2.0, ofGetHeight() / 2.0);
        hitTime = ( (distToCenterSquared / maxRadiusSquared) * interval ) + timeAtBeat;
    }
    if(ofGetElapsedTimeMillis() >= hitTime){
        if(!isHit){
            isHit = true;
            hitRadius = 25;
            hitAlpha = 255;
        }
    }
    else{
        isHit = false;
    }
    lastPos = pos;
}

void Person::draw(){
    ofSetColor(0, 0, 255);
    ofSetLineWidth(5);
    ofNoFill();
    ofCircle(pos.x, pos.y, 25);
    
    if(isHit){
        ofSetColor(0, 0, 255, hitAlpha);
        ofCircle(pos.x, pos.y, hitRadius);
        hitRadius += 5;
        hitAlpha -= 10;
    }
}

void Person::beat(){
    timeAtBeat = ofGetElapsedTimeMillis();
    hitTime = ( (distToCenterSquared / maxRadiusSquared) * interval ) + timeAtBeat;
}