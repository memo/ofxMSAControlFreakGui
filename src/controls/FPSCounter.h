#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class FPSCounter : public Control {
            public:
                
                //--------------------------------------------------------------
                FPSCounter(Container *parent) : Control(parent, ParameterPtr(new Parameter("FPS", NULL))) {}
                
                //--------------------------------------------------------------
                void setup() {
                    width   = getConfig().layout.columnWidth;
                    height  = getConfig().layout.buttonHeight;
                }

                //--------------------------------------------------------------
                void onDraw() {
                    glPushMatrix();
                    glTranslatef(x, y, 0);
                    
                    ofEnableAlphaBlending();
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setTextColor();
                    getConfig().drawString("FPS: " + ofToString(ofGetFrameRate()), 3, 15);
                    
                    glPopMatrix();
                }
            };
            
        }
    }
}