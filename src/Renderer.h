//
//  Renderer.cpp
//  ofxMSAControlFreak example
//
//  Created by Memo Akten on 28/12/2012.
//
//

#pragma once

#include "ofMain.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class Control;
            class Config;
            
            class Renderer {
            public:
                friend class Gui;
                
                ~Renderer();
                
                static Renderer &instance();
                
                void add(Control *c);
                void clearControls();
                void draw();
                
                void setToolTip(Control* control, string s, int x = -1, int y = -1);
                
            protected:
                static Renderer *renderer;
                
                vector<Control*> controls;
                
                struct {
                    string s;
                    int x;
                    int y;
                    Control* control;
                } tooltip;
                
                Renderer();
                
                void drawToolTip();
//                
//                void update();
//                void mouseMoved(ofMouseEventArgs &e);
//                void mousePressed(ofMouseEventArgs &e);
//                void mouseDragged(ofMouseEventArgs &e);
//                void mouseReleased(ofMouseEventArgs &e);
//                void keyPressed(ofKeyEventArgs &e);
//                void keyReleased(ofKeyEventArgs &e);

            };
            
        }
    }
}