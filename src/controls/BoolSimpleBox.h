#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolSimpleBox : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolSimpleBox(Container *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolSimpleBox(Container *parent, ParameterBool* p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(isMousePressed() || getParameter().value()) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
                    ofPushMatrix();
                    ofScale(width, height);
                    ofFill();
                    ofRect(0, 0, 1, 1);
                    if(isMouseOver()) {
                        ofNoFill();
                        setColor(ofColor(255));
                        ofRect(0, 0, 1, 1);
                    }
                    ofPopMatrix();

                    drawTextCentered();
                    drawBorder();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}