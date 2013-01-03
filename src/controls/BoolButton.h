#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolButton : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolButton(Container *parent, string s) : BoolBase(parent, s) {}

                //--------------------------------------------------------------
                BoolButton(Container *parent, ParameterPtr p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    // draw bg
                    ofFill();
                    setToggleColor(paramT->getValue());
                    ofRect(0, 0, width, height);
                    
//                    drawText(3, 15);
                    drawTextCentered();
                    drawBorder();
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}