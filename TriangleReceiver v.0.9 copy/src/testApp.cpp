#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    maximumAreaThreshold = getMaximumTriangleArea()/5;  // we'll use this value for determining which layers to enable
    triangleReceiver.setup(3334);       // setup trianglereceiver to listen on port 3334
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    // img player
    shape1.loadSequence("image/shape_layer", "png", 1, 20, 2);
	shape1.preloadAllFrames();	
    
    playingImg = false; 
}

//--------------------------------------------------------------
void testApp::update(){
    triangleReceiver.update();  // receive triangle data
    triangleReceiver.pulse.update();
        
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){             // set radius, center for every triangle
        (*triangleIt)->radius       = getMaximumRadiusInTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        (*triangleIt)->center       = getTriangleCenter((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        (*triangleIt)->lengthOfAB   = (ofDist((*triangleIt)->A.x, (*triangleIt)->A.y, (*triangleIt)->B.x, (*triangleIt)->B.y));     // set linelengths
        (*triangleIt)->lengthOfBC   = (ofDist((*triangleIt)->B.x, (*triangleIt)->B.y, (*triangleIt)->C.x, (*triangleIt)->C.y));
        (*triangleIt)->lengthOfCA   = (ofDist((*triangleIt)->C.x, (*triangleIt)->C.y, (*triangleIt)->A.x, (*triangleIt)->A.y));
        
        (*triangleIt)->radius1      = (*triangleIt)->radius/5;
        (*triangleIt)->radius2      = ((*triangleIt)->radius/5)*2;
        (*triangleIt)->radius3      = ((*triangleIt)->radius/5)*3;
        (*triangleIt)->radius4      = ((*triangleIt)->radius/5)*4;
        (*triangleIt)->radius5      = (*triangleIt)->radius;
        
        cout << "AB: " << (*triangleIt)->lengthOfAB << endl;
        cout << "BC: " << (*triangleIt)->lengthOfBC << endl;
        cout << "CA: " << (*triangleIt)->lengthOfCA << endl;
        
        // enable or disable each of the 5 layers according to the area of the triangle
        float triangleArea = getTriangleArea((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        if(triangleArea < maximumAreaThreshold){
			(*triangleIt)->state = TriangleStateDrawFirstLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold && triangleArea < maximumAreaThreshold*2 ){
			(*triangleIt)->state = TriangleStateDrawSecondLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold*2 && triangleArea < maximumAreaThreshold*3){
			(*triangleIt)->state = TriangleStateDrawThirdLayer;
        }
        
        else if(triangleArea > maximumAreaThreshold*3 && triangleArea < maximumAreaThreshold*4){
            (*triangleIt)->state = TriangleStateDrawFourthLayer;
        }        
        else{
            (*triangleIt)->state = TriangleStateDrawFifthLayer;
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0); 
    triangleReceiver.pulse.draw();
    
    list<Triangle*>::iterator triangleIt;
    for(triangleIt = triangleReceiver.triangles.begin(); triangleIt != triangleReceiver.triangles.end(); triangleIt++){
        // draw (red) filled triangle, opacity determined by tension
        ofFill();
        ofSetColor(255, 0, 0, (*triangleIt)->tension * 255.0f);
        ofTriangle((*triangleIt)->A, (*triangleIt)->B, (*triangleIt)->C);
        
        // draw (white) lines, full opacity
        ofSetColor(255);      
        ofSetLineWidth(2);
        ofLine((*triangleIt)->A.x,(*triangleIt)->A.y, (*triangleIt)->B.x,(*triangleIt)->B.y);
        ofLine((*triangleIt)->B.x,(*triangleIt)->B.y,(*triangleIt)->C.x,(*triangleIt)->C.y);
        ofLine((*triangleIt)->C.x,(*triangleIt)->C.y, (*triangleIt)->A.x,(*triangleIt)->A.y);
        
        // draw (green) animation placeholders
        //ofSetColor(0, 255, 0);
        ofSetLineWidth(1);
        ofNoFill();    
		
		if((*triangleIt)->state == TriangleStateDrawFirstLayer){
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius1, 1);
			
            //ofCircle((*triangleIt)->center, (*triangleIt)->radius/5);  
		}
		else if((*triangleIt)->state == TriangleStateDrawSecondLayer){
//			ofCircle((*triangleIt)->center, (*triangleIt)->radius/5);  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*2));            
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius1, 1);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius2, 5);
            
		}
		else if((*triangleIt)->state == TriangleStateDrawThirdLayer){
//			ofCircle((*triangleIt)->center, (*triangleIt)->radius/5);  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*2));  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*3));             
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius1, 1);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius2, 5);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius3, 10);
		}
		else if((*triangleIt)->state == TriangleStateDrawFourthLayer){
//			ofCircle((*triangleIt)->center, (*triangleIt)->radius/5);  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*2));  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*3));  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*4));
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius1, 1);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius2, 5);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius3, 10);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius4, 13);
		}
		else if((*triangleIt)->state == TriangleStateDrawFifthLayer){
			ofCircle((*triangleIt)->center, (*triangleIt)->radius/5);  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*2));  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*3));  
//			ofCircle((*triangleIt)->center, ((*triangleIt)->radius/5*4));  
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius1, 1);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius2, 5);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius3, 10);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius4, 13);
            drawShapeWithRotation((*triangleIt)->center, 100, (*triangleIt)->radius5, 17);
		}
    }
    
    
    
    // draw all persons
    list<Person*>::iterator personIt;
    for(personIt = triangleReceiver.persons.begin(); personIt != triangleReceiver.persons.end(); personIt++){
        (*personIt)->draw();
    }
}

//--------------------------------------------------------------
ofPoint testApp::getTriangleCenter(ofPoint A, ofPoint B, ofPoint C){
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    ofPoint triangleCenter = ofPoint(((lengthOfBC * A) + (lengthOfCA * B) + (lengthOfAB * C)) / perimeter);   
    
    return(triangleCenter);
}

//--------------------------------------------------------------
float testApp::getMaximumRadiusInTriangle(ofPoint A, ofPoint B, ofPoint C){ 
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    float semiPerimeter = perimeter/2;  
    float maxRadius = sqrtf( ( (semiPerimeter - lengthOfAB) * (semiPerimeter - lengthOfBC) * (semiPerimeter - lengthOfCA) ) / semiPerimeter);
    
    return(maxRadius);
}
//--------------------------------------------------------------
float testApp::getTriangleArea(ofPoint A, ofPoint B, ofPoint C){
    float lengthOfAB = (ofDist(A.x, A.y, B.x, B.y));
    float lengthOfBC = (ofDist(B.x, B.y, C.x, C.y));
    float lengthOfCA = (ofDist(C.x, C.y, A.x, A.y));
    
    float perimeter = (lengthOfAB + lengthOfBC + lengthOfCA);
    float semiPerimeter = perimeter/2;
    float area = sqrtf( semiPerimeter * ( (semiPerimeter - lengthOfAB) * (semiPerimeter - lengthOfBC) * (semiPerimeter - lengthOfCA) ));
    
    return(area);
}

//--------------------------------------------------------------
float testApp::getMaximumTriangleArea(){ 
    float maxSideLength = 325;
    float maxSemiPerimeter = (maxSideLength*3)/2;
    float maxArea = sqrtf( maxSemiPerimeter * ( (maxSemiPerimeter - maxSideLength) * (maxSemiPerimeter - maxSideLength) * (maxSemiPerimeter - maxSideLength) ) );
    float areaThreshold = maxArea/5;
    
    return(areaThreshold);
}

//--------------------------------------------------------------
void testApp::drawShapeWithRotation(ofPoint centerPoint, int rotation, int radius, int layer){ 
    ofPushMatrix();
    ofTranslate(centerPoint.x, centerPoint.y, 0);
    ofRotateZ(rotation);
    shape1.getFrame(layer)->draw(0 -(radius)/2,0 - (radius)/2, radius*2, radius*2);    
    ofPopMatrix(); 
}
