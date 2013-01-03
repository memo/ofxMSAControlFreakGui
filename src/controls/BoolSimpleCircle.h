#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolSimpleCircle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolSimpleCircle(Panel *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolSimpleCircle(Panel *parent, Parameter *p) : BoolBase(parent, p) {}
                
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