#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolToggle : public BoolBase {
            public:
                
                //--------------------------------------------------------------
                BoolToggle(Container *parent, string s) : BoolBase(parent, s) {}
                
                //--------------------------------------------------------------
                BoolToggle(Container *parent, ParameterBool* p) : BoolBase(parent, p) {}
               
                //--------------------------------------------------------------
                void onDraw() {
                                        
                    ofFill();
                    setToggleColor(getParameter().value());
                    ofRect(0, 0, height, height);
                    
                    if(getParameter().value()) {
                        setTextColor();
                        ofSetLineWidth(2);
                        ofLine(0, 0, height, height);
                        ofLine(height, 0, 0, height);
                    }
                    
                    setBGColor();
                    ofRect(height, 0, width - height, height);
                    
//                    drawText(height + getConfig().layout.textPos.x, getConfig().layout.textPos.y);
                    
                    drawTextCentered();
                    drawBorder();
                    
                    BoolBase::onDraw();
                }
                
            };

            
        }
    }
}