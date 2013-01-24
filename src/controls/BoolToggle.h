#pragma once

#include "ofxMSAControlFreakGui/src/controls/BoolBase.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class BoolToggle : public BoolBase {
            public:
                
                bool bDrawCross;
                
                //--------------------------------------------------------------
                BoolToggle(Container *parent, string s) : BoolBase(parent, s) { bDrawCross = true; }
                
                //--------------------------------------------------------------
                BoolToggle(Container *parent, ParameterBool* p) : BoolBase(parent, p) { bDrawCross = true; }
               
                //--------------------------------------------------------------
                void onDraw() {
                                        
                    ofFill();
                    setToggleColor(getParameter().value());
                    ofRect(0, 0, height, height);
                    
                    if(getParameter().value()) {
                        setTextColor();
                        if(bDrawCross) {
                            ofSetLineWidth(2);
                            ofLine(0, 0, height, height);
                            ofLine(height, 0, 0, height);
                        } else {
                            ofCircle(height/2, height/2, height/4);
                        }
                    }
                    
                    setBGColor();
                    ofRect(height, 0, width - height, height);
                    
//                    drawText(height + pconfig->layout.textPos.x, pconfig->layout.textPos.y);
                    
                    drawTextCentered();
                    drawBorder();
                    
                    BoolBase::onDraw();
                }
                
            };

            
        }
    }
}