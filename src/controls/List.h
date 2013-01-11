#pragma once

#include "ofxMSAControlFreakGui/src/Control.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class List : public Control {
            public:
                
                //--------------------------------------------------------------
                List(Container *parent, string s) : Control(parent, new ParameterNamedIndex(s, NULL), true) {
                    init();
                }
                
                //--------------------------------------------------------------
                List(Container *parent, Parameter* p) : Control(parent, p) {
                    init();
                }
                
                //--------------------------------------------------------------
                void init() {
                    paramT = dynamic_cast<ParameterNamedIndex*>(&getParameter());
                    mouseOverIndex = -1;
                }
                
                //--------------------------------------------------------------
                void setMode(ParameterNamedIndex::Mode mode) {
                    paramT->setMode(mode);
                }
                
                //--------------------------------------------------------------
                void onPress(int x, int y, int button) {
                    onMouseMove(x, y);
                    paramT->set(mouseOverIndex);
                }
                
                //--------------------------------------------------------------
                void onMouseMove(int x, int y) {
                    int a = this->y;
                    int b = this->y + getConfig().layout.dropdownListTextHeight * paramT->getNumLabels();
                    mouseOverIndex = floor(ofMap(y + getConfig().layout.dropdownListTextHeight/2, a, b, 0, paramT->getNumLabels()-1, true));
                }

                //--------------------------------------------------------------
                void onDragOver(int x, int y, int button) {
                    onPress(x, y, button);
                }
                
                
                //--------------------------------------------------------------
                void onRollOut() {
                    mouseOverIndex = -1;
                }
                
                //--------------------------------------------------------------
                void onDraw() {
                    int numLabels = paramT->getNumLabels();
                    layout.height = height = getConfig().layout.dropdownListTextHeight * (numLabels + 0.5);

                    setBGColor();
                    ofFill();
                    ofRect(0, 0, width, height);
                    
                    drawBorder();
                    ofFill();
                    
                    for(int i=0; i < numLabels; i++) {
                        setTextColor();
                        float curY = i * getConfig().layout.dropdownListTextHeight;
                        if(i == mouseOverIndex) {
                            ofNoFill();
                            ofRect(0, curY+3, width, getConfig().layout.dropdownListTextHeight);
                        }
                        if(i == getParameter().value()) {
                            ofFill();
                            ofRect(0, curY+3, width, getConfig().layout.dropdownListTextHeight);
                            setBGColor();
                        }
                        
                        getConfig().drawString(paramT->getLabel(i), getConfig().layout.textPos.x, curY + getConfig().layout.textPos.y);
                    }
                }
                
            protected:
                ParameterNamedIndex *paramT;
                int mouseOverIndex;
            };
            
        }
    }
}