#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class DropdownList : public Control {
            public:
                
                //--------------------------------------------------------------
                DropdownList(Container *parent, string s) : Control(parent, new ParameterNamedIndex(s, NULL)) {
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
                    int b = this->y + height + pconfig->layout.dropdownListTextHeight * paramT->size();
                    int v = //floor(ofMap(y + pconfig->layout.dropdownListTextHeight/2, a, b, 0, paramT->size()-1, true));
                        floor(ofMap(y, a, b, 0, paramT->size(), true));
                    paramT->set(v);
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
                
            protected:
                ParameterNamedIndex *paramT;
            };
            
        }
    }
}