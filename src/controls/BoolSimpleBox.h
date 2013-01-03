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
                BoolSimpleBox(Container *parent, ParameterPtr p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                                        
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