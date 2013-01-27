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

                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                }
                
                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    onMouseMove(x, y);
//                    paramT->set(v);
                }
                
                //--------------------------------------------------------------
                void draw() {
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    drawText(pconfig->layout.textPos.x, pconfig->layout.textPos.y, getName() + ": " + paramT->getSelectedLabel());
                    drawBorder();
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    ofFill();
                    ofTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isActive()) {
                        int numLabels = paramT->size();
                        setBGColor();
                        ofFill();
                        ofRect(0, height, width, pconfig->layout.dropdownListTextHeight * (numLabels + 0.5));
                        
                        ofNoFill();
                        ofSetLineWidth(1);
                        setBorderColor();
                        ofRect(0, height, width, pconfig->layout.dropdownListTextHeight * (numLabels + 0.5));
                        ofFill();
                        
                        for(int i=0; i < numLabels; i++) {
                            setTextColor();
                            float curY = height + i*pconfig->layout.dropdownListTextHeight;
                            if(i == getParameter().value()) {
                                ofRect(0, curY+3, width, pconfig->layout.dropdownListTextHeight);
                                setBGColor();
                            }
                            
                            pconfig->drawString(paramT->getLabel(i), pconfig->layout.textPos.x, curY + pconfig->layout.textPos.y);
                        }
                    }
                }
                
            };
            
        }
    }
}