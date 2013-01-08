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
                BoolSimpleBox(Container *parent, Parameter* p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(isMouseOver()) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
                    ofFill();
                    ofRect(0, 0, width, height);

                    drawTextCentered();
                    drawBorder();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}