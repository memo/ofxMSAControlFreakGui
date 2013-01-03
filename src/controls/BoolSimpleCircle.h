#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolSimpleCircle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolSimpleCircle(Container *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolSimpleCircle(Container *parent, ParameterPtr p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(isMouseOver()) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
                    ofPushMatrix();
                    ofScale(width, height);
                    ofFill();
                    ofCircle(0.5, 0.5, 0.5);
                    ofPopMatrix();

                    drawTextCentered();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}