#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioIn(float * input, int bufferSize, int nChannels);
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
    
        int     bufferCounter;
        int     drawCounter;
    
        float smoothedVol;
        float scaledVol;
    
        ofSoundStream soundStream;
        ofSoundPlayer soundplay;
    
    
        ofEasyCam cam;
        ofVec3f pos;
        ofColor Col_1;
        ofColor Col_2;
        ofColor Col_3;
        float random;
        float updown;
        float downup;
    
        float rotate_x;
        float rotate_y;
        float rotate_z;
    
        float box_size;
};
