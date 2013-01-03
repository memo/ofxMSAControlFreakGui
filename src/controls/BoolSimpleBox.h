#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolSimpleBox : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolSimpleBox(Panel *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolSimpleBox(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!parameter) return;
                    
                    if(isMouseOver()) setColor(ofColor(255, 100));
                    else setColor(ofColor(0, 100));
                    ofCircle(x, y, height/2);
                    
                    drawText(0, 0);
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}