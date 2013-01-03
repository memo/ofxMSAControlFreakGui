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
                BoolToggle(Container *parent, ParameterPtr p) : BoolBase(parent, p) {}
               
                //--------------------------------------------------------------
                void onDraw() {
                                        
                    ofFill();
                    setToggleColor(paramT->getValue());
                    ofRect(0, 0, height, height);
                    
                    if(paramT->getValue()) {
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