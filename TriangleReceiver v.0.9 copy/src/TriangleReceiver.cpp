//
//  TriangleReceiver.cpp
//  emptyExample
//
//  Created by Daan on 11/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "TriangleReceiver.h"

void TriangleReceiver::setup(int port){
    receiver.setup(port);
    cout << "TriangleReceiver::setup(int port) -- will start listening on port " << port << endl;
}


void TriangleReceiver::update(){
    list<Person*>::iterator personIt;
    for(personIt = persons.begin(); personIt != persons.end(); personIt++){
        (*personIt)->update();
    }

    // check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        
		// check for didAppear
		if ( m.getAddress() == "/triangle/didAppear" )
		{
            Triangle *tri = new Triangle;
            tri->id = m.getArgAsInt32(0);
            tri->A = ofPoint(m.getArgAsFloat(1) * ofGetWidth(), m.getArgAsFloat(2) * ofGetHeight());
			tri->tensionA = m.getArgAsFloat(3);
            tri->B = ofPoint(m.getArgAsFloat(4) * ofGetWidth(), m.getArgAsFloat(5) * ofGetHeight());
			tri->tensionB = m.getArgAsFloat(6);
            tri->C = ofPoint(m.getArgAsFloat(7) * ofGetWidth(), m.getArgAsFloat(8) * ofGetHeight());
			tri->tensionC = m.getArgAsFloat(9);
			tri->tension = m.getArgAsFloat(10);
            triangles.push_back(tri);
		}
		// check for didMove
		else if ( m.getAddress() == "/triangle/didMove" )
		{
            int id = m.getArgAsInt32(0);
            list<Triangle*>::iterator triangleIt;
            for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
                if((*triangleIt)->id == id){
					(*triangleIt)->A = ofPoint(m.getArgAsFloat(1) * ofGetWidth(), m.getArgAsFloat(2) * ofGetHeight());
					(*triangleIt)->tensionA = m.getArgAsFloat(3);
					(*triangleIt)->B = ofPoint(m.getArgAsFloat(4) * ofGetWidth(), m.getArgAsFloat(5) * ofGetHeight());
					(*triangleIt)->tensionB = m.getArgAsFloat(6);
					(*triangleIt)->C = ofPoint(m.getArgAsFloat(7) * ofGetWidth(), m.getArgAsFloat(8) * ofGetHeight());
					(*triangleIt)->tensionC = m.getArgAsFloat(9);
					(*triangleIt)->tension = m.getArgAsFloat(10);
                    return;
                }
            }
		}
        // check for didDisappear
		else if ( m.getAddress() == "/triangle/didDisappear" )
		{
            int id = m.getArgAsInt32(0);
            list<Triangle*>::iterator triangleIt;
            for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
                if((*triangleIt)->id == id){
                    triangles.remove((*triangleIt));
                    return;
                }
            }
		}

        
        
        // check for didAppear
		else if ( m.getAddress() == "/person/didAppear" )
		{
            Person *person = new Person();
            person->setup(pulse.interval, ofPoint(m.getArgAsFloat(1) * ofGetWidth(), m.getArgAsFloat(2) * ofGetHeight()), pulse.lastBeatTime, m.getArgAsInt32(0));
            persons.push_back(person);
		}
		// check for didMove
		else if ( m.getAddress() == "/person/didMove" )
		{
            int id = m.getArgAsInt32(0);
            list<Person*>::iterator personIt;
            for(personIt = persons.begin(); personIt != persons.end(); personIt++){
                if((*personIt)->id == id){
                    (*personIt)->pos = ofPoint(m.getArgAsFloat(1) * ofGetWidth(), m.getArgAsFloat(2) * ofGetHeight());
                    return;
                }
            }
		}
        // check for didDisappear
		else if ( m.getAddress() == "/person/didDisappear" )
		{
            int id = m.getArgAsInt32(0);
            list<Triangle*>::iterator triangleIt;
            list<Person*>::iterator personIt;
            for(personIt = persons.begin(); personIt != persons.end(); personIt++){
                if((*personIt)->id == id){
                    persons.remove((*personIt));
                    return;
                }
            }
		}
        
        
        else if ( m.getAddress() == "/sequencer/interval" )
		{
            pulse.setup(m.getArgAsInt32(0));
        }
        
        else if ( m.getAddress() == "/sequencer/isBeat" )
		{
            pulse.beat();
            
            list<Person*>::iterator personIt;
            for(personIt = persons.begin(); personIt != persons.end(); personIt++){
                (*personIt)->beat();
            }
        }
        
        // unrecognized address
		else
		{
			cout << "TriangleReceiver::update() -- unrecognized address: " << m.getAddress() << endl;
		}
	}
}

void TriangleReceiver::draw(){
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangles.begin(); triangleIt != triangles.end(); triangleIt++){
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
    }
    
    list<Person*>::iterator personIt;
    for(personIt = persons.begin(); personIt != persons.end(); personIt++){
        (*personIt)->draw();
    }
}





