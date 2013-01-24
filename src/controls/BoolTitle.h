#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"
#include "ofxMSAControlFreakGui/src/Renderer.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolTitle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolTitle(Container *parent, string s) : BoolBase(parent, s) { }
                
                //--------------------------------------------------------------
                BoolTitle(Container *parent, ParameterBool* p) : BoolBase(parent, p) { }
                
                
                //--------------------------------------------------------------
                void draw() {
                    // draw bg
                    ofFill();
                    setToggleColor(getParameter().value());
                    ofRect(0, 0, width, height);
                    
//                    drawText(40, 15);
                    drawTextCentered();

//                    drawBorder(pconfig->colors.text);
                    drawBorder();
                    
                    BoolBase::draw();
                }
            };
            
        }
    }
}