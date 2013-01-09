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
                BoolSimpleCircle(Container *parent, Parameter* p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(isMousePressed() || getParameter().value()) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
                    ofPushMatrix();
                    ofScale(width, height);
                    ofFill();
                    ofCircle(0.5, 0.5, 0.5);
                    if(isMouseOver()) {
                        ofNoFill();
                        setColor(ofColor(255));
                        ofCircle(0.5, 0.5, 0.5);
                    }
                    ofPopMatrix();

                    drawTextCentered();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}