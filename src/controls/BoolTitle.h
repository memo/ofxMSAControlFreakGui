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
                BoolTitle(Container *parent, ParameterPtr p) : BoolBase(parent, p) { }
                
                
                //--------------------------------------------------------------
                void onDraw() {
                    // draw bg
                    ofFill();
                    setToggleColor(paramT->getValue());
                    ofRect(0, 0, width, height);
                    
//                    drawText(40, 15);
                    drawTextCentered();

                    ofSetLineWidth(2);
                    drawBorder(getConfig().colors.text);
                    
                    if(doTooltip()) {
                        string s;
                        string sverb = paramT->getValue() ? "Close": "Open";
//                        if(paramT->getValue()) s = "Click to close panel [" + getName() + "]";
//                        else s = "Click to open panel";
                        Renderer::instance().setToolTip(sverb + " " + "panel. Right-click to temporarily isolate");
                    }
                    
                    BoolBase::onDraw();
                }
            };
            
        }
    }
}