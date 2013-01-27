#pragma once

#include "ofxMSAControlFreakGui/src/Controls/OptionsBase.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class OptionsDropdownList : public OptionsBase {
            public:
                
                //--------------------------------------------------------------
                OptionsDropdownList(Container *parent, string s) : OptionsBase(parent, new ParameterNamedIndex(s, NULL)) {
                    lineHeight = pconfig->layout.dropdownListTextHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }
                
                //--------------------------------------------------------------
                OptionsDropdownList(Container *parent, ParameterNamedIndex* p) : OptionsBase(parent, p) {
                    lineHeight = pconfig->layout.dropdownListTextHeight;
                    titleHeight = pconfig->layout.buttonHeight;
                }

//                //--------------------------------------------------------------
//                void onPress(int x, int y, int button) {
//                }
//                
//                //--------------------------------------------------------------
//                void onDragOutside(int x, int y, int button) {
//                    onMouseMove(x, y);
////                    paramT->set(v);
//                    onPress(x, y, button);
//                }
//                
                //--------------------------------------------------------------
                void draw() {
//                    height = titleHeight;
//                    ofFill();
//                    setBGColor();
//                    ofRect(0, 0, width, height);
//                    
//                    drawText(pconfig->layout.textPos.x, pconfig->layout.textPos.y, getName() + ": " + paramT->getSelectedLabel());
//                    drawBorder();
//                    
//                    int ty = height/3;
//                    int tl = ty*1.5;
                    drawTitle();
                    ofFill();
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    
                    ofTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isActive()) drawList();
                    
                    layout.height = height = titleHeight + listHeight() * isActive();
                }
                
            };
            
        }
    }
}