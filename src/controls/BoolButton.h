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
                BoolButton(Container *parent, Parameter* p) : BoolBase(parent, p) {}
                
                //--------------------------------------------------------------
                void onDraw() {
                    // draw bg
                    ofFill();
                    setToggleColor(getParameter().value());
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