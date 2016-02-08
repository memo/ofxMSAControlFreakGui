//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreakGui
//

#pragma once

#include "ofxMSAControlFreak.h"
#include "MSAControlFreakGui/controls/OptionsBase.h"

namespace msa {
    namespace controlfreak {
        namespace gui {
            
            class OptionsDropdownList : public OptionsBase {
            public:
                
                //--------------------------------------------------------------
                OptionsDropdownList(Container *parent, string s) : OptionsBase(parent, new ParameterNamedIndex(s)) {
                    lineHeight = getConfig()->layout.dropdownListTextHeight;
                    titleHeight = getConfig()->layout.buttonHeight;
                    isOpen = false;
                }
                
                //--------------------------------------------------------------
                OptionsDropdownList(Container *parent, ParameterNamedIndex* p) : OptionsBase(parent, p) {
                    lineHeight = getConfig()->layout.dropdownListTextHeight;
                    titleHeight = getConfig()->layout.buttonHeight;
                    isOpen = false;
                }

                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    isOpen ^= true;
                    update(x, y, button);
                }
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
//                    ofDrawRectangle(0, 0, width, height);
//                    
//                    drawText(getConfig()->layout.textPos.x, getConfig()->layout.textPos.y, getName() + ": " + paramT->getSelectedLabel());
//                    drawBorder();
//                    
//                    int ty = height/3;
//                    int tl = ty*1.5;
                    drawTitle();
                    ofFill();
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    
                    ofDrawTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isOpen) drawList();
                    
                    layout.height = height = titleHeight + listHeight() * isOpen;
                }
                
            protected:
                bool isOpen;
                
            };
            
        }
    }
}
