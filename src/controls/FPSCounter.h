#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class FPSCounter : public Control {
            public:
                
                //--------------------------------------------------------------
                FPSCounter(Container *parent) : Control(parent, new Parameter("FPS")) {}
                
                //--------------------------------------------------------------
                void setup() {
                    width   = pconfig->layout.columnWidth;
                    height  = pconfig->layout.buttonHeight;
                }

                //--------------------------------------------------------------
                void draw() {
                    glPushMatrix();
                    glTranslatef(x, y, 0);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    drawText(3, 15, "FPS: " + ofToString(ofGetFrameRate()));
                    drawBorder();
                    
                    glPopMatrix();
                }
            };
            
        }
    }
}