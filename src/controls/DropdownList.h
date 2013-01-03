#pragma once

#include "ofxMSAControlFreakGui/src/ControlParameterT.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class DropdownList : public ControlParameterT<ParameterNamedIndex> {
            public:
                
                //--------------------------------------------------------------
                DropdownList(Panel *parent, Parameter *p) : ControlParameterT<ParameterNamedIndex>(parent, p) {}

                //--------------------------------------------------------------
                void setup() {
                    width   = getConfig().layout.columnWidth;
                    height  = getConfig().layout.buttonHeight;
                }

                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    if(!parameter) return;
                    int a = this->y + height;
                    int b = this->y + height + getConfig().layout.dropdownListTextHeight * parameter->getNumLabels();
                    int v = floor(ofMap(y + getConfig().layout.dropdownListTextHeight/2, a, b, 0, parameter->getNumLabels()-1, true));
                    parameter->setValue(v);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    if(!parameter) return;
                    
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    setTextColor();
                    getConfig().drawString(getName() + ": " + parameter->getSelectedLabel(), getConfig().layout.textPos.x, getConfig().layout.textPos.y);
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    ofTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isActive()) {
                        int numLabels = parameter->getNumLabels();
                        setBGColor();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        
                        ofNoFill();
                        ofSetLineWidth(1);
                        setBorderColor();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        ofFill();
                        
                        for(int i=0; i < numLabels; i++) {
                            setTextColor();
                            float curY = height + i*getConfig().layout.dropdownListTextHeight;
                            if(i == parameter->getValue()) {
                                ofRect(0, curY+3, width, getConfig().layout.dropdownListTextHeight);
                                setBGColor();
                            }
                            
                            getConfig().drawString(parameter->getLabel(i), getConfig().layout.textPos.x, curY + getConfig().layout.textPos.y);
                        }
                    }
                }
                
            };
            
        }
    }
}