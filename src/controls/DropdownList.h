#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class DropdownList : public Control {
            public:
                
                //--------------------------------------------------------------
                DropdownList(Container *parent, string s) : Control(parent, new ParameterNamedIndex(s, NULL), true) {
                    paramT = dynamic_cast<ParameterNamedIndex*>(&getParameter());
                }
                
                //--------------------------------------------------------------
                DropdownList(Container *parent, ParameterNamedIndex* p) : Control(parent, p) {
                    paramT = p;
                }

                //--------------------------------------------------------------
                void setMode(ParameterNamedIndex::Mode mode) {
                    paramT->setMode(mode);
                }
                
                //--------------------------------------------------------------
                void onDragOutside(int x, int y, int button) {
                    int a = this->y + height;
                    int b = this->y + height + getConfig().layout.dropdownListTextHeight * paramT->getNumLabels();
                    int v = floor(ofMap(y + getConfig().layout.dropdownListTextHeight/2, a, b, 0, paramT->getNumLabels()-1, true));
                    paramT->set(v);
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    ofFill();
                    setBGColor();
                    ofRect(0, 0, width, height);
                    
                    drawText(getConfig().layout.textPos.x, getConfig().layout.textPos.y, getName() + ": " + paramT->getSelectedLabel());
                    drawBorder();
                    
                    int ty = height/3;
                    int tl = ty*1.5;
                    ofFill();
                    ofTriangle(width - ty - tl, ty, width - ty, ty, width - ty - tl/2, height - ty);
                    
                    if(isActive()) {
                        int numLabels = paramT->getNumLabels();
                        setBGColor();
                        ofFill();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        
                        ofNoFill();
                        ofSetLineWidth(1);
                        setBorderColor();
                        ofRect(0, height, width, getConfig().layout.dropdownListTextHeight * (numLabels + 0.5));
                        ofFill();
                        
                        for(int i=0; i < numLabels; i++) {
                            setTextColor();
                            float curY = height + i*getConfig().layout.dropdownListTextHeight;
                            if(i == getParameter().value()) {
                                ofRect(0, curY+3, width, getConfig().layout.dropdownListTextHeight);
                                setBGColor();
                            }
                            
                            getConfig().drawString(paramT->getLabel(i), getConfig().layout.textPos.x, curY + getConfig().layout.textPos.y);
                        }
                    }
                }
                
            protected:
                ParameterNamedIndex *paramT;
            };
            
        }
    }
}